#include <ctime>
#include "raylib.h"
#include "raymath.h"
#include "Dungeon.hpp"

// ---------------------------------------------------------------------------
// Sprites: loaded from assets/ if the PNG exists, otherwise drawn as a colored
// shape. That way the game runs before any art exists, and you can drop
// sprites in one at a time.
// ---------------------------------------------------------------------------
struct Sprite {
    Texture2D tex{};
    bool loaded = false;
    Color fallback = MAGENTA;
};

static Sprite LoadSprite(const char* path, Color fallback) {
    Sprite s;
    s.fallback = fallback;
    if (FileExists(path)) {
        s.tex = LoadTexture(path);
        SetTextureFilter(s.tex, TEXTURE_FILTER_POINT);  // crisp pixel art
        s.loaded = true;
    }
    return s;
}

// Draws the sprite centered on `center`, scaled to `size` pixels.
// For animation later: change `src` to pick a frame out of a sprite sheet.
static void DrawSprite(const Sprite& s, Vector2 center, float size, float rotationDeg = 0.0f) {
    Rectangle dst = { center.x, center.y, size, size };
    Vector2 origin = { size / 2, size / 2 };
    if (s.loaded) {
        Rectangle src = { 0, 0, (float)s.tex.width, (float)s.tex.height };
        DrawTexturePro(s.tex, src, dst, origin, rotationDeg, WHITE);
    } else {
        DrawRectanglePro(dst, origin, rotationDeg, s.fallback);
    }
}

static void UnloadSprite(Sprite& s) {
    if (s.loaded) UnloadTexture(s.tex);
}

// ---------------------------------------------------------------------------
// Game state
// ---------------------------------------------------------------------------
enum class Screen { Title, Playing, GameOver };

struct Player {
    Vector2 pos{};          // world pixels (center)
    float energy = 100.0f;  // health AND ammo
};

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

            // TODO(you): WASD movement + wall collision against dungeon.IsWalkable().
            //   Tip: move X and Y separately and undo the axis that hits a wall,
            //   so the player slides along walls instead of sticking.
            // TODO(you): aim at mouse (GetScreenToWorld2D(GetMousePosition(), camera)),
            //   left click = shotgun blast (N pellets, random spread, costs energy).
            // TODO: enemies (seek player + keep distance from each other), drain energy on contact.
            // TODO: if the player stands on Tile::Exit -> level++, startLevel().
            (void)dt;

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
