#pragma once
#include "Controller.hpp"
#include "../../include/Utils/MessageBus.hpp"

class PauseSceneController : public Controller {
public:
    PauseSceneController();
    ~PauseSceneController() override;
    
    void Initialize() override;
    void HandleEvent(const sf::Event& event) override;
    
private:
    void HandleGamePaused(const Message& message);
}; 