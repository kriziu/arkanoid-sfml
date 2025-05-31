#include "../../include/Controllers/SceneController.hpp"
#include "../../include/Core/Core.hpp"
#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Scenes/GameOverScene.hpp"

SceneController::SceneController(Core* core, GameplayScene* gameplayScene) 
    : Controller(), core_(core), gameplayScene_(gameplayScene), gameOverScene_(nullptr) {}

SceneController::~SceneController() {
    MessageBus::Unsubscribe(MessageType::BallLost, this);
    MessageBus::Unsubscribe(MessageType::GameOver, this);
    delete gameOverScene_;
}

void SceneController::Initialize() {
    MessageBus::Subscribe(MessageType::BallLost, this, 
        [this](const Message& msg) { HandleBallLost(msg); });
    
    MessageBus::Subscribe(MessageType::GameOver, this,
        [this](const Message& msg) { HandleGameOver(msg); });
    
    gameOverScene_ = new GameOverScene();
    gameOverScene_->Initialize();
}

void SceneController::HandleBallLost(const Message& message) {
    core_->RemoveScene(gameplayScene_);
    core_->AddScene(gameOverScene_);
}

void SceneController::HandleGameOver(const Message& message) {
    std::string action = std::any_cast<std::string>(message.payload);
    if (action == "restart") {
        core_->RemoveScene(gameOverScene_);
        core_->RemoveScene(gameplayScene_);
            
        delete gameplayScene_;
        gameplayScene_ = new GameplayScene();
        gameplayScene_->Initialize();
            
        core_->AddScene(gameplayScene_);
    }
} 