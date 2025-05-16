#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Paddle.hpp"

GameplayScene::GameplayScene() : paddle_(nullptr) {}

GameplayScene::~GameplayScene() {}

void GameplayScene::Initialize() {
    Paddle* paddle = new Paddle();
    paddle_ = paddle;
    // paddle_->SetPosition(350, 550);
    AddActor(paddle);
    
    Scene::Initialize();
} 