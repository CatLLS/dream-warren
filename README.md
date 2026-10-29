# Dream Warren

<!-- Replace with a GIF of gameplay: it's the first thing a reviewer looks at. -->

A top-down shooter in C++ and raylib. A girl in a red hood is trapped in a dream-maze (a *warren*) that rebuilds itself every level, while bunnies made of cloud swarm her and drain her energy.

This is a quick little project I'm making for halloween to learn c++, though it is connected to other games of mine!

## Build

Requires CMake 3.25+ and a C++17 compiler. raylib is downloaded automatically.

```bash
cmake -B build
cmake --build build
```
To run, after building, come to this folder's terminal and type the following code or press the run button if in visual studio through cmake (I'm using vscode to develop this one)
```bash
.\build\dream_warren.exe
```

Run `build/dream_warren` (on Windows with Visual Studio: `build\Debug\dream_warren.exe`).

## Controls

| Key | Action |
|---|---|
| WASD | Move |
| Mouse | Aim |
| Left click | Shotgun |
| R | Regenerate level (debug) |

## How it works

<!-- Write this section yourself, in your own words: how the generator works,
     how the enemies decide where to move, and one problem you had to solve. -->
