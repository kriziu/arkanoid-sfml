#pragma once
#include "Controller.hpp"
#include "../Utils/MessageBus.hpp"

class Core;
class GameplayScene;
class GameOverScene;

class GameplaySceneController : public Controller {
public:
    GameplaySceneController();
    ~GameplaySceneController() override;

    void Initialize() override;

private:
    void HandleGameOver(const Message& message);
    void HandleLevelRestarted(const Message& message);
}; 