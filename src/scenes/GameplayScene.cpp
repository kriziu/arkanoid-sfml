#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Actors/Ball.hpp"
#include "../../include/Controllers/PaddleController.hpp"
#include "../../include/Controllers/BallController.hpp"
#include <iostream>

GameplayScene::GameplayScene() {}

GameplayScene::~GameplayScene() {}

void GameplayScene::Initialize() {
    Paddle* paddle = new Paddle();
    paddle->AddController(new PaddleController());

    Ball* ball = new Ball();
    ball->AddController(new BallController());

    AddActor(paddle);
    AddActor(ball);
    
    // TODO: Add some way to select level
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

void GameplayScene::RestartLevel() {
    ClearActors();
    
    Paddle* paddle = new Paddle();
    paddle->AddController(new PaddleController());
    paddle->SetScene(this);

    Ball* ball = new Ball();
    ball->AddController(new BallController());
    ball->SetScene(this);

    AddActor(paddle);
    AddActor(ball);
    
    if (!LoadLevel("levels/level1.level")) {
        std::cerr << "Failed to load default level" << std::endl;
    }
    
    for (auto& actor : actors_) {
        actor->Initialize();
    }
    
    SetActive(true);
}
