// implementation of Sprite.hpp, check that file for explanations
#include "../include/Sprite.hpp"

Sprite LoadSprite(const char* path, Color fallback) {
    Sprite s;
    s.fallback = fallback;
    if (FileExists(path)) {
        s.tex = LoadTexture(path);
        SetTextureFilter(s.tex, TEXTURE_FILTER_POINT);  // crisp pixel art
        s.loaded = true;
    }
    return s;
}

//NOTE: Draws the sprite centered on `center`, scaled to `size` pixels.
// TODO: For animation later: change `src` to pick a frame out of a sprite sheet.
void DrawSprite(const Sprite& s, Vector2 center, float size, float rotationDeg) { //in c++ leave defaults only in the header! Can't have them in the cpp file too, or the compiler will complain about multiple definitions.
    Rectangle dst = { center.x, center.y, size, size };
    Vector2 origin = { size / 2, size / 2 };
    if (s.loaded) {
        Rectangle src = { 0, 0, (float)s.tex.width, (float)s.tex.height };
        DrawTexturePro(s.tex, src, dst, origin, rotationDeg, WHITE);
    } else {
        DrawRectanglePro(dst, origin, rotationDeg, s.fallback);
    }
}

void UnloadSprite(Sprite& s) {
    if (s.loaded) UnloadTexture(s.tex);
}
