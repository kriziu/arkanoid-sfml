#include "../../include/Controllers/GameplaySceneController.hpp"
#include "../../include/Scenes/GameplayScene.hpp"

GameplaySceneController::GameplaySceneController() : Controller() {}

GameplaySceneController::~GameplaySceneController() {
    MessageBus::Unsubscribe(MessageType::BallLost, this);
    MessageBus::Unsubscribe(MessageType::LevelRestarted, this);
}

void GameplaySceneController::Initialize() {
    MessageBus::Subscribe(MessageType::BallLost, this, 
        [this](const Message& msg) { HandleBallLost(msg); });

    MessageBus::Subscribe(MessageType::LevelRestarted, this, 
        [this](const Message& msg) { HandleLevelRestarted(msg); });
}

void GameplaySceneController::HandleBallLost(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetActive(false);
}

void GameplaySceneController::HandleLevelRestarted(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->RestartLevel();
} 