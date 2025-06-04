#pragma once
#include "Controller.hpp"
#include "../Utils/MessageBus.hpp"

class Core;
class GameplayScene;
class GameOverScene;

class GameOverSceneController : public Controller {
public:
    GameOverSceneController();
    ~GameOverSceneController() override;

    void Initialize() override;
    void HandleEvent(const sf::Event& event) override;

private:
    void HandleBallLost(const Message& message);
    void HandleLevelRestarted(const Message& message);
}; 