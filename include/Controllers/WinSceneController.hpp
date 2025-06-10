#pragma once
#include "Controller.hpp"
#include "../../include/Utils/MessageBus.hpp"

class WinSceneController : public Controller {
public:
    WinSceneController();
    ~WinSceneController() override;
    
    void Initialize() override;
    void HandleEvent(const sf::Event& event) override;
    
private:
    void HandleLevelComplete(const Message& message);
}; 