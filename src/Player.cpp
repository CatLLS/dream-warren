//Player cpp
#include "../include/Player.hpp"
#include "raylib.h"
#include "../include/Dungeon.hpp" //some functions in Player.cpp need to know about the dungeon, so we include it here.
#include "../include/Sprite.hpp" //sprites too so player can be drawn

void UpdatePlayer(Player& player, const Dungeon& dungeon, float dt){
    Vector2 currentPos = player.pos;
    if (IsKeyDown(KEY_W) && dungeon.IsWalkable(player.pos.x/TILE_SIZE, (currentPos.y - 150.0f*dt)/TILE_SIZE)) player.pos.y -= 150.0f*dt;         
    if (IsKeyDown(KEY_A) && dungeon.IsWalkable((currentPos.x - 150.0F*dt)/TILE_SIZE, (player.pos.y)/TILE_SIZE)) player.pos.x -= 150.0f*dt;         
    if (IsKeyDown(KEY_S) && dungeon.IsWalkable(player.pos.x/TILE_SIZE, (currentPos.y + 150.0f*dt)/TILE_SIZE)) player.pos.y += 150.0f*dt;         
    if (IsKeyDown(KEY_D) && dungeon.IsWalkable((currentPos.x + 150.0F*dt)/TILE_SIZE, (player.pos.y)/TILE_SIZE)) player.pos.x += 150.0f*dt;         

    // TODO(you): aim at mouse (GetScreenToWorld2D(GetMousePosition(), camera)),
            //   left click = shotgun blast (N pellets, random spread, costs energy).  
}
