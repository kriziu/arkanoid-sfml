#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Controllers/PaddleController.hpp"

GameplayScene::GameplayScene() : paddle_(nullptr) {}

GameplayScene::~GameplayScene() {}

void GameplayScene::Initialize() {
    Paddle* paddle = new Paddle();
    paddle_ = paddle;
    paddle->Initialize();
    AddActor(paddle);
    
    PaddleController* paddleController = new PaddleController(paddle);
    paddleController->Initialize();
    paddle->AddController(paddleController);
    
    Scene::Initialize();
} 