# Arkanoid SFML

A simple Arkanoid game implementation using SFML 3.0.1.

## Project Structure

- `include/`: Header files

  - `Core/`: Core game management classes
  - `Actors/`: Game objects like Paddle, Ball, Brick
  - `Controllers/`: Logic components attached to actors
  - `Scenes/`: Game scenes like menu, gameplay
  - `Utils/`: Utility classes like MessageBus

- `src/`: Implementation files with the same structure as include

## Building the Project

### Requirements

- CMake 3.16 or higher
- C++17 compatible compiler

### Build steps

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Architecture

The project follows an entity-component pattern:

- **Core**: Main game controller managing the game loop and scenes
- **Scene**: Container for actors and scene-specific controllers
- **Actor**: Game entity with position, size and visual representation
- **Controller**: Behavior logic attached to actors or scenes
- **MessageBus**: Communication system between components
