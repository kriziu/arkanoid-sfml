#pragma once
#include "Controller.hpp"
#include "../Utils/MessageBus.hpp"

class Core;
class GameplayScene;
class GameOverScene;

class SceneController : public Controller {
public:
    SceneController(Core* core, GameplayScene* gameplayScene);
    ~SceneController() override;

    void Initialize() override;

private:
    void HandleBallLost(const Message& message);
    void HandleGameOver(const Message& message);
    
    Core* core_;
    GameplayScene* gameplayScene_;
    GameOverScene* gameOverScene_;
}; 