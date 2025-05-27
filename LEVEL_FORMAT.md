# Level File Format

This document describes the level file format used in the Arkanoid game for creating custom brick layouts.

## File Format

Level files use the `.level` extension and follow a simple text-based format.

### Header Line

The first line contains 7 space-separated values:

```
<width> <height> <brick_width> <brick_height> <spacing> <start_x> <start_y>
```

- `width`: Number of columns in the grid
- `height`: Number of rows in the grid
- `brick_width`: Width of each brick in pixels
- `brick_height`: Height of each brick in pixels
- `spacing`: Space between bricks in pixels
- `start_x`: X coordinate of the top-left brick position
- `start_y`: Y coordinate of the top-left brick position

### Grid Data

Following the header, each line represents a row of bricks in the grid.

#### Brick Types

- `1` - Normal brick (red, 1 hit point)
- `2` - Strong brick (blue, 2 hit points)
- `X` - Unbreakable brick (gray, cannot be destroyed)
- `.` or ` ` (space) - Empty space (no brick)

## Example Level

```
12 8 60.0 20.0 2.0 50.0 50.0
111111111111
222222222222
111111111111
2.1.X.X.1.2
2.1.X.X.1.2
111111111111
222222222222
111111111111
```

This creates:

- A 12x8 grid
- Bricks that are 60x20 pixels
- 2 pixels spacing between bricks
- Starting position at (50, 50)
- Mixed layout with normal, strong, and unbreakable bricks

## Creating Custom Levels

1. Create a new `.level` file in the `levels/` directory
2. Define the header with your desired grid size and brick properties
3. Design your brick layout using the character codes
4. Test your level in the game

## Level Loading

Levels are loaded automatically by the `LevelLoader` class:

- `LoadLevel()` parses the file format
- `LoadBricksIntoScene()` creates Brick actors and adds them to the scene
- Each brick gets a `BrickController` for collision detection and destruction

## Tips for Level Design

- Use a mix of brick types for interesting gameplay
- Leave strategic gaps for ball movement
- Consider the paddle position when designing lower rows
- Test your levels to ensure they're fun and balanced
