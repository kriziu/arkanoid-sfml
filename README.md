# Arkanoid SFML

A simple Arkanoid game implementation using SFML 3.

## Architecture

The game is built using a component-based architecture with the following main concepts:

1. **Core** - Main game entry point that manages the game loop and scenes
2. **Scene** - Represents a game screen (e.g., Menu, Gameplay)
3. **Actor** - Game objects like Ball, Paddle, and Bricks
4. **Controller** - Components that define behavior for Actors or Scenes
5. **MessageBus** - Communication system between components

## Building the Project

### Prerequisites

- C++17 compatible compiler
- CMake 3.14 or higher
- SFML 3.x

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

## Game Controls

- Left Arrow: Move paddle left
- Right Arrow: Move paddle right
- Escape: Pause game

## Project Structure

```
src/
├── core/           # Core architecture components
│   ├── Actor.hpp
│   ├── Controller.hpp
│   ├── Core.hpp
│   ├── Message.hpp
│   ├── MessageBus.hpp
│   ├── MessageType.hpp
│   └── Scene.hpp
├── actors/         # Game objects
│   ├── Ball.hpp
│   ├── Brick.hpp
│   └── Paddle.hpp
├── controllers/    # Behavior components
│   ├── BallController.hpp
│   └── PaddleController.hpp
└── scenes/         # Game screens
    └── GameplayScene.hpp
```

## Future Improvements

- Add menu scene
- Implement power-ups
- Add sound effects and music
- Create level editor
- Add high score system
