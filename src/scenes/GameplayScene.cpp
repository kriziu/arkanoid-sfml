#include "../../include/Scenes/GameplayScene.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Actors/Ball.hpp"
#include "../../include/Controllers/PaddleController.hpp"
#include "../../include/Controllers/BallController.hpp"
#include "../../include/Utils/Constants.hpp"
#include <iostream>

GameplayScene::GameplayScene(): livesText_(sf::Text(iconsFont_)) {}

GameplayScene::~GameplayScene() {}

void GameplayScene::Initialize() {
    Paddle* paddle = new Paddle();
    paddle->AddController(new PaddleController());

    Ball* ball = new Ball();
    ball->AddController(new BallController());

    AddActor(paddle);
    AddActor(ball);
    
    if (!selectedLevelFilename_.empty() && !LoadLevel(selectedLevelFilename_)) {
        std::cerr << "Failed to load level: " << selectedLevelFilename_ << std::endl;
    }
    
    SetupUI();
    Scene::Initialize();
    SetActive(false);
}

void GameplayScene::SetupUI() {
    if (!iconsFont_.openFromFile("assets/fonts/icons.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
        livesText_.setFont(iconsFont_);
        livesText_.setCharacterSize(24);
        livesText_.setFillColor(sf::Color::Red);
        livesText_.setPosition({Constants::WINDOW_WIDTH - 40, 
        Constants::WINDOW_HEIGHT / 2 + 36 });
}

void GameplayScene::Draw(sf::RenderWindow& window) {
    Scene::Draw(window);
    DrawLivesDisplay(window);
}

void GameplayScene::DrawLivesDisplay(sf::RenderWindow& window) {
    Ball* ball = GetActor<Ball>();
    if (!ball) return;
    
    int lives = ball->GetLives();
    sf::String heartsText = "";
    for (int i = 0; i < lives; i++) {
        heartsText += static_cast<char32_t>(0xF02D1);
        if (i < lives - 1) heartsText += "\n";
    }
    livesText_.setString(heartsText);
    window.draw(livesText_);
}

bool GameplayScene::LoadLevel(const std::string& levelFilename) {
    if (!LevelLoader::LoadLevel(levelFilename, currentLevel_)) {
        return false;
    }
    
    if (!LevelLoader::LoadBricksIntoScene(currentLevel_, this)) {
        return false;
    }
    
    return true;
}

void GameplayScene::SetLevelFilename(const std::string& levelFilename) {
    selectedLevelFilename_ = levelFilename;
}
