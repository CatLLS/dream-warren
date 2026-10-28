//dungeon header
//-> maze generations and tile queries

/*ps: this is a C++ learning project, so there will be lots of comments on 
new functions I didn't know, please ignore them, I'll leave a "TODO" or "NOTE"
on important explanations.
*/

#pragma once //guarantees that the file is read by the compiler only once.(similar to #ifndef/#define/#endif in c)
#include <vector>
#include "raylib.h" //since this is to learn c++ specifically, not an engine, I'm using this.


enum class Tile { Wall, Floor, Exit };//tiles, like in the engine

constexpr int TILE_SIZE = 32;   //NOTE: pixels per tile on screen (sprites are drawn at this size)

struct Dungeon {
    //why a struct and not a class? because I don't need to hide anything and this is just a buch of configuration data, so a struct is more appropriate.
    //in c++ the :: basically means "belongs to" or "is a member of", so Dungeon::At means the At function belongs to the Dungeon struct.
    int width = 0;               // in tiles
    int height = 0;              // in tiles
    std::vector<Tile> tiles;     // row-major: index = y * width + x -> less cache miss!(basically a 1D array instead of a 2D array, which is more efficient)
    Vector2 playerStart{};       // in tiles
    std::vector<Vector2> enemySpawns;  // in tiles

    Tile At(int x, int y) const; //const assures that the function doesn't modify the object, also allowing the compiler to optimize the code better.
    bool IsWalkable(int x, int y) const;
};

// TODO(you): replace the placeholder body in Dungeon.cpp with your own generator
// (random walk, BSP rooms + corridors, cellular automata...).
// Same seed must give the same dungeon: makes bugs reproducible and is a nice README detail.
Dungeon GenerateDungeon(int width, int height, unsigned int seed);
