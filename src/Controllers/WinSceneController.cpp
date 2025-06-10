#include "../../include/Controllers/WinSceneController.hpp"
#include "../../include/Scenes/WinScene.hpp"
#include "../../include/Utils/MessageBus.hpp"

WinSceneController::WinSceneController() : Controller() {}

WinSceneController::~WinSceneController() {
    MessageBus::Unsubscribe(MessageType::LevelComplete, this);
}

void WinSceneController::Initialize() {
    MessageBus::Subscribe(MessageType::LevelComplete, this,
        [this](const Message& msg) { HandleLevelComplete(msg); });
}

void WinSceneController::HandleLevelComplete(const Message& message) {
    WinScene* winScene = GetScene<WinScene>();
    winScene->SetActive(true);
}

void WinSceneController::HandleEvent(const sf::Event& event) {
    WinScene* winScene = GetScene<WinScene>();
    
    if (!winScene->IsActive()) return;
    
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(mouseButtonPressed->position.x), 
                                                 static_cast<float>(mouseButtonPressed->position.y));
            
            if (winScene->IsLevelRestartButtonClicked(mousePos)) {
                Message restartMessage;
                restartMessage.type = MessageType::LevelRestarted;
                restartMessage.sender = this;
                MessageBus::Publish(restartMessage);
                
                winScene->SetActive(false);
            }
            
            if (winScene->IsLevelSelectorButtonClicked(mousePos)) {
                Message levelSelectorMessage;
                levelSelectorMessage.type = MessageType::ShowLevelSelector;
                levelSelectorMessage.sender = this;
                MessageBus::Publish(levelSelectorMessage);
                
                winScene->SetActive(false);
            }
        }
    }
} 