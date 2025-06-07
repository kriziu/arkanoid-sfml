#include "../../include/Controllers/GameplaySceneController.hpp"
#include "../../include/Scenes/GameplayScene.hpp"

GameplaySceneController::GameplaySceneController() : Controller() {}

GameplaySceneController::~GameplaySceneController() {
    MessageBus::Unsubscribe(MessageType::GameOver, this);
    MessageBus::Unsubscribe(MessageType::LevelRestarted, this);
    MessageBus::Unsubscribe(MessageType::LevelSelected, this);
}

void GameplaySceneController::Initialize() {
    MessageBus::Subscribe(MessageType::GameOver, this, 
        [this](const Message& msg) { HandleGameOver(msg); });

    MessageBus::Subscribe(MessageType::LevelRestarted, this, 
        [this](const Message& msg) { HandleLevelRestarted(msg); });

    MessageBus::Subscribe(MessageType::LevelSelected, this, 
        [this](const Message& msg) { HandleLevelSelected(msg); });
}

void GameplaySceneController::HandleGameOver(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetActive(false);
}

void GameplaySceneController::HandleLevelRestarted(const Message& message) {
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->Reset();
    gameplayScene->SetActive(true);
}

void GameplaySceneController::HandleLevelSelected(const Message& message) {
    std::string levelFilename = std::any_cast<std::string>(message.payload);
    GameplayScene* gameplayScene = GetScene<GameplayScene>();
    gameplayScene->SetLevelFilename(levelFilename);
    gameplayScene->Reset();
    gameplayScene->SetActive(true);
}
