#include "../../include/Controllers/PauseSceneController.hpp"
#include "../../include/Scenes/PauseScene.hpp"
#include "../../include/Utils/MessageBus.hpp"
#include <any>
#include <iostream>

PauseSceneController::PauseSceneController() : Controller() {}

PauseSceneController::~PauseSceneController() {
    MessageBus::Unsubscribe(MessageType::GamePaused, this);
}

void PauseSceneController::Initialize() {
    MessageBus::Subscribe(MessageType::GamePaused, this,
        [this](const Message& msg) { HandleGamePaused(msg); });
}

void PauseSceneController::HandleGamePaused(const Message& message) {
    PauseScene* pauseScene = GetScene<PauseScene>();
    pauseScene->SetActive(true);
}

void PauseSceneController::HandleEvent(const sf::Event& event) {
    PauseScene* pauseScene = GetScene<PauseScene>();
    
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x), 
                                                 static_cast<float>(mouseButtonPressed->position.y));
            
            if (pauseScene->IsResumeButtonClicked(mousePos)) {
                Message resumeMessage;
                resumeMessage.type = MessageType::GameResumed;
                resumeMessage.sender = this;
                MessageBus::Publish(resumeMessage);
                
                pauseScene->SetActive(false);
            }
            
            if (pauseScene->IsMenuButtonClicked(mousePos)) {
                Message levelSelectorMessage;
                levelSelectorMessage.type = MessageType::ShowLevelSelector;
                levelSelectorMessage.sender = this;
                MessageBus::Publish(levelSelectorMessage);
                
                pauseScene->SetActive(false);
            }
        }
    }
} 