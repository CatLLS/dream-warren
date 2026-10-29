//dungeon code 
#include "../include/Dungeon.hpp"

Tile Dungeon::At(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) return Tile::Wall;
    return tiles[y * width + x];
}

bool Dungeon::IsWalkable(int x, int y) const {
    return At(x, y) != Tile::Wall;
}

// PLACEHOLDER so the project runs on day one: one big empty room with an exit.
// Delete this body and write your generator here.
Dungeon GenerateDungeon(int width, int height, unsigned int /*seed*/) {
    Dungeon d;
    d.width = width;
    d.height = height;
    d.tiles.assign(width * height, Tile::Wall);

    for (int y = 1; y < height - 1; y++)
        for (int x = 1; x < width - 1; x++)
            d.tiles[y * width + x] = Tile::Floor;

    d.tiles[(height - 2) * width + (width - 2)] = Tile::Exit;
    d.playerStart = { 2, 2 };
    return d;
}
