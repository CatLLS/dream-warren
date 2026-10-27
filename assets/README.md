# Assets

Drop PNGs here with these exact names. Anything missing is drawn as a colored square, so add them one at a time.

| File | Size | Notes |
|---|---|---|
| `floor.png` | 32×32 | Must tile seamlessly |
| `wall.png` | 32×32 | Must tile seamlessly |
| `exit.png` | 32×32 | The way out of the dream |
| `player.png` | 32×32 | Drawn at 24 px; top-down or 3/4 view |
| `bunny.png` | 32×32 | Cloud bunny (add `LoadSprite` for it when you write enemies) |
| `pellet.png` | 8×8 | Optional, shotgun pellet |

Pixel art at 16×16 or 32×32 scales cleanly (the camera zooms 2×, and point filtering keeps edges crisp).

For animation, put frames side by side in one PNG (e.g. 4 frames → 128×32) and pick a frame with the `src` rectangle in `DrawSprite`.
