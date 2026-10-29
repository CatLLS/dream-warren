// Player hpp
#pragma once
#include "raylib.h"
#include "../include/Dungeon.hpp"

struct Player {
    Vector2 pos{};          // world pixels (center)
    float energy = 100.0f;  // health AND ammo
};

void UpdatePlayer(Player& player, const Dungeon& dungeon, float dt);