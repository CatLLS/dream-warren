#include <ctime>
#include "raylib.h"
#include "raymath.h" // for vector math
#include "../include/Dungeon.hpp"
#include "../include/Sprite.hpp"
#include "../include/Player.hpp"

// ---------------------------------------------------------------------------
// Game state
// ---------------------------------------------------------------------------
enum class Screen { Title, Playing, GameOver };

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Dream Warren");
    SetTargetFPS(60);

    Sprite floorSpr  = LoadSprite("assets/floor.png",  Color{ 60, 50, 90, 255 });
    Sprite wallSpr   = LoadSprite("assets/wall.png",   Color{ 30, 22, 50, 255 });
    Sprite exitSpr   = LoadSprite("assets/exit.png",   Color{ 255, 220, 120, 255 });
    Sprite playerSpr = LoadSprite("assets/player.png", Color{ 200, 40, 60, 255 });

    Screen screen = Screen::Title;
    int level = 1;
    Dungeon dungeon;
    Player player;
    Camera2D camera{};
    camera.zoom = 2.0f;

    auto startLevel = [&]() {
        dungeon = GenerateDungeon(48, 32, (unsigned int)time(nullptr));
        player.pos = { dungeon.playerStart.x * TILE_SIZE + TILE_SIZE / 2.0f,
                       dungeon.playerStart.y * TILE_SIZE + TILE_SIZE / 2.0f };
        camera.target = player.pos;  // snap, so the camera doesn't swoop in from the old level
    };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // ---------------- UPDATE ----------------
        switch (screen) {
        case Screen::Title:
            if (IsKeyPressed(KEY_ENTER)) {
                level = 1;
                player.energy = 100.0f;
                startLevel();
                screen = Screen::Playing;
            }
            break;

        case Screen::Playing:
            if (IsKeyPressed(KEY_R)) startLevel();  // debug: regenerate
            UpdatePlayer(player, dungeon, dt);
            // TODO: enemies (seek player + keep distance from each other), drain energy on contact.
            // TODO: if the player stands on Tile::Exit -> level++, startLevel().
            
            (void)dt;//what does this do?

            if (player.energy <= 0.0f) screen = Screen::GameOver;
            break;

        case Screen::GameOver:
            if (IsKeyPressed(KEY_ENTER)) screen = Screen::Title;
            break;
        }

        // Camera follows the player, smoothed.
        camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
        camera.target = Vector2Lerp(camera.target, player.pos, 0.15f);

        // ---------------- DRAW ----------------
        BeginDrawing();
        ClearBackground(Color{ 18, 12, 30, 255 });

        if (screen == Screen::Title) {
            DrawText("DREAM WARREN", 80, 200, 72, RAYWHITE);
            DrawText("Press ENTER", 80, 300, 28, LIGHTGRAY);
        } else {
            BeginMode2D(camera);
            for (int y = 0; y < dungeon.height; y++) {
                for (int x = 0; x < dungeon.width; x++) {
                    Vector2 c = { x * TILE_SIZE + TILE_SIZE / 2.0f, y * TILE_SIZE + TILE_SIZE / 2.0f };
                    switch (dungeon.At(x, y)) {
                        case Tile::Wall:  DrawSprite(wallSpr,  c, TILE_SIZE); break;
                        case Tile::Floor: DrawSprite(floorSpr, c, TILE_SIZE); break;
                        case Tile::Exit:  DrawSprite(exitSpr,  c, TILE_SIZE); break;
                    }
                }
            }
            DrawSprite(playerSpr, player.pos, 24);
            EndMode2D();

            // HUD (screen space, not affected by the camera)
            DrawRectangle(20, 20, 204, 24, Color{ 0, 0, 0, 160 });
            DrawRectangle(22, 22, (int)(2.0f * player.energy), 20, Color{ 180, 200, 255, 255 });
            DrawText(TextFormat("Dream %d", level), 240, 22, 20, RAYWHITE);

            if (screen == Screen::GameOver) {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 180 });
                DrawText("You fell into a deeper sleep...", 80, 260, 40, RAYWHITE);
                DrawText(TextFormat("Reached dream %d  -  ENTER to wake up", level), 80, 320, 24, LIGHTGRAY);
            }
        }
        EndDrawing();
    }

    UnloadSprite(floorSpr);
    UnloadSprite(wallSpr);
    UnloadSprite(exitSpr);
    UnloadSprite(playerSpr);
    CloseWindow();
    return 0;
}
