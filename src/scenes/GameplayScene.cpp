#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Controllers/PaddleController.hpp"
#include <iostream>

GameplayScene::GameplayScene() : paddle_(nullptr) {}

GameplayScene::~GameplayScene() {}

void GameplayScene::Initialize() {
    paddle_ = new Paddle();
    paddle_->Initialize();
    AddActor(paddle_);
    
    PaddleController* paddleController = new PaddleController(paddle_);
    paddleController->Initialize();
    paddle_->AddController(paddleController);
    
    if (!LoadLevel("levels/level1.level")) {
        std::cerr << "Failed to load default level" << std::endl;
    }
    
    Scene::Initialize();
}

bool GameplayScene::LoadLevel(const std::string& levelFile) {
    if (!LevelLoader::LoadLevel(levelFile, currentLevel_)) {
        return false;
    }
    
    if (!LevelLoader::LoadBricksIntoScene(currentLevel_, this)) {
        return false;
    }
    
    return true;
} 