#include "../../include/Controllers/GameplaySceneController.hpp"
#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Ball.hpp"

GameplaySceneController::GameplaySceneController() : Controller() {}

GameplaySceneController::~GameplaySceneController() {
    MessageBus::Unsubscribe(MessageType::GameOver, this);
    MessageBus::Unsubscribe(MessageType::LevelRestarted, this);
    MessageBus::Unsubscribe(MessageType::LevelSelected, this);
    MessageBus::Unsubscribe(MessageType::LevelComplete, this);
    MessageBus::Unsubscribe(MessageType::GameResumed, this);
}

void GameplaySceneController::Initialize() {
    MessageBus::Subscribe(MessageType::GameOver, this, 
        [this](const Message& msg) { HandleGameOver(msg); });

    MessageBus::Subscribe(MessageType::LevelRestarted, this, 
        [this](const Message& msg) { HandleLevelRestarted(msg); });

    MessageBus::Subscribe(MessageType::LevelSelected, this, 
        [this](const Message& msg) { HandleLevelSelected(msg); });

    MessageBus::Subscribe(MessageType::LevelComplete, this,
        [this](const Message& msg) { HandleLevelComplete(msg); });
        
    MessageBus::Subscribe(MessageType::GameResumed, this,
        [this](const Message& msg) { HandleGameResumed(msg); });
}

void GameplaySceneController::HandleEvent(const sf::Event& event) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            Message pauseMessage;
            pauseMessage.type = MessageType::GamePaused;
            pauseMessage.sender = this;
            MessageBus::Publish(pauseMessage);

            gameplayScene->SetActive(false);
        }
    }
}

void GameplaySceneController::HandleGameOver(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetActive(false);
}

void GameplaySceneController::HandleLevelRestarted(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->Reset();
    
    Ball* ball = gameplayScene->GetActor<Ball>();
    if (ball) {
        ball->SetInitialLaunchBlocked(false);
    }
    
    gameplayScene->SetActive(true);
}

void GameplaySceneController::HandleLevelSelected(const Message& message) {
    std::string levelFilename = std::any_cast<std::string>(message.payload);
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetLevelFilename(levelFilename);
    gameplayScene->Reset();
    gameplayScene->SetActive(true);
}

void GameplaySceneController::HandleLevelComplete(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetActive(false);
}

void GameplaySceneController::HandleGameResumed(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetActive(true);
}
