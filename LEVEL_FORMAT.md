# Level File Format

This document describes the level file format used in the Arkanoid game for creating custom brick layouts.

## File Format

Level files use the `.level` extension and follow a simple text-based format.

### Header Line

The first line contains 5 space-separated values:

```
<width> <height> <spacing> <padding_x> <padding_y>
```

- `width`: Number of columns in the grid
- `height`: Number of rows in the grid
- `spacing`: Space between bricks in pixels
- `padding_x`: X coordinate of the x padding
- `padding_y`: Y coordinate of the y padding

### Grid Data

Following the header, each line represents a row of bricks in the grid.

#### Brick Types

- `1` - Normal brick (red, 1 hit point)
- `2` - Strong brick (blue, 2 hit points)
- `X` - Unbreakable brick (gray, cannot be destroyed)
- `.` - Empty space (no brick)

## Example Level

```
13 8 5.0 20.0 20.0
1111111111111
1.1.1.1.1.1.1
2.2.2.2.2.2.2
2222222222222
XX...XXX...XX
..111...111..
```

This creates:

- A 13x8 grid
- 5 pixels spacing between bricks
- Padding of 20px in x and y dimensions
- Mixed layout with normal, strong, and unbreakable bricks

## Creating Custom Levels

1. Create a new `.level` file in the `levels/` directory
2. Define the header with your desired grid size and brick properties
3. Design your brick layout using the character codes
4. Test your level in the game
5. Make sure levels directowy is in the same directory as binary file, otherwise levels won't load

## Level Loading

Levels are loaded automatically by the `LevelLoader` class:

- `LoadLevel()` parses the file format
- `LoadBricksIntoScene()` creates Brick actors and adds them to the scene
- Each brick gets a `BrickController` for collision detection and destruction
