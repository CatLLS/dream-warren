//Everything about loading and drawing sprites is in this file. The main.cpp file is for the game loop and game logic, not for drawing.
//Sprite hpp
#pragma once
#include "raylib.h"

// ---------------------------------------------------------------------------
// Sprites: loaded from assets/ if the PNG exists, otherwise drawn as a colored
// shape. That way the game runs before any art exists, and you can drop
// sprites in one at a time.
// ---------------------------------------------------------------------------
struct Sprite {
    Texture2D tex{}; //Where the png is loaded if it exists, otherwise fallback color is drawn
    bool loaded = false;
    Color fallback = MAGENTA;
};
Sprite LoadSprite(const char* path, Color fallback);
void DrawSprite(const Sprite& s, Vector2 center, float size, float rotationDeg = 0.0f);
void UnloadSprite(Sprite& s);
