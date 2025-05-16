#pragma once

namespace arkanoid {

enum class MessageType {
    BrickDestroyed,
    BallLost,
    LifeLost,
    GameOver,
    LevelComplete,
    ScoreChanged,
    CollisionOccurred,
    MenuOptionSelected,
    GamePaused,
    GameResumed
};

} // namespace arkanoid 