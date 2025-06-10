#include "../../include/Controllers/GameplaySceneController.hpp"
#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Ball.hpp"

GameplaySceneController::GameplaySceneController() : Controller() {}

GameplaySceneController::~GameplaySceneController() {
    MessageBus::Unsubscribe(MessageType::GameOver, this);
    MessageBus::Unsubscribe(MessageType::LevelRestarted, this);
    MessageBus::Unsubscribe(MessageType::LevelSelected, this);
    MessageBus::Unsubscribe(MessageType::LevelComplete, this);
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
