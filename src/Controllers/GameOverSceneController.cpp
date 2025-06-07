#include "../../include/Controllers/GameOverSceneController.hpp"
#include "../../include/Scenes/GameOverScene.hpp"

GameOverSceneController::GameOverSceneController() : Controller() {}

GameOverSceneController::~GameOverSceneController() {
    MessageBus::Unsubscribe(MessageType::GameOver, this);
    MessageBus::Unsubscribe(MessageType::LevelRestarted, this);
}

void GameOverSceneController::Initialize() {
    MessageBus::Subscribe(MessageType::GameOver, this, 
        [this](const Message& msg) { HandleGameOver(msg); });

    MessageBus::Subscribe(MessageType::LevelRestarted, this, 
        [this](const Message& msg) { HandleLevelRestarted(msg); });
}

void GameOverSceneController::HandleGameOver(const Message& message) {
    GameOverScene* gameOverScene = GetScene<GameOverScene>();
    gameOverScene->SetActive(true);
}

void GameOverSceneController::HandleLevelRestarted(const Message& message) {
    GameOverScene* gameOverScene = GetScene<GameOverScene>();
    gameOverScene->Reset();
}

void GameOverSceneController::HandleEvent(const sf::Event& event) {
    GameOverScene* gameOverScene = GetScene<GameOverScene>();

    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                                static_cast<float>(mouseButtonPressed->position.y));
            
            if (gameOverScene->IsRestartButtonClicked(mousePos)) {
                Message message;
                message.type = MessageType::LevelRestarted;
                message.sender = this;
                MessageBus::Publish(message);
            }
            
            if (gameOverScene->IsLevelSelectorButtonClicked(mousePos)) {
                Message message;
                message.type = MessageType::ShowLevelSelector;
                message.sender = this;
                MessageBus::Publish(message);
            }
        }
    }
}