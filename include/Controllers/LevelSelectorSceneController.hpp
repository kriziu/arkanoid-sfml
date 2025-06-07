#pragma once
#include "Controller.hpp"
#include "../Utils/MessageBus.hpp"

class LevelSelectorScene;

class LevelSelectorSceneController : public Controller {
public:
    LevelSelectorSceneController();
    ~LevelSelectorSceneController() override;

    void Initialize() override;
    void HandleEvent(const sf::Event& event) override;

private:
    void HandleLevelSelected(const std::string& levelFile);
}; 