#include <iostream>
#include "../../include/Scenes/GameOverScene.hpp"
#include "../../include/Utils/Constants.hpp"

GameOverScene::GameOverScene() :
    gameOverText_(sf::Text(font_)),
    restartText_(sf::Text(font_)),
    tryAgainText_(sf::Text(font_)),
    levelSelectorText_(sf::Text(font_)),
    restartButton_(sf::RectangleShape()),
    levelSelectorButton_(sf::RectangleShape()) {}

GameOverScene::~GameOverScene() {}

void GameOverScene::Initialize() {
    Scene::Initialize();

    SetActive(false);
    SetupUI();
}

void GameOverScene::SetupUI() {
    if (!font_.openFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    gameOverText_.setFont(font_);
    gameOverText_.setString("GAME OVER");
    gameOverText_.setCharacterSize(72);
    gameOverText_.setFillColor(sf::Color::Red);
    
    sf::FloatRect gameOverBounds = gameOverText_.getLocalBounds();
    gameOverText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - gameOverBounds.size.x) / 2,
        Constants::WINDOW_HEIGHT / 2 - 100
    ));
    
    tryAgainText_.setFont(font_);
    tryAgainText_.setString("TRY AGAIN");
    tryAgainText_.setCharacterSize(36);
    tryAgainText_.setFillColor(sf::Color::White);
    
    sf::FloatRect tryAgainBounds = tryAgainText_.getLocalBounds();
    tryAgainText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - tryAgainBounds.size.x) / 2 - tryAgainBounds.position.x,
        Constants::WINDOW_HEIGHT / 2 - 10
    ));
    
    restartButton_.setSize(sf::Vector2f(200, 60));
    restartButton_.setFillColor(sf::Color(70, 130, 180));
    restartButton_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - 200) / 2,
        Constants::WINDOW_HEIGHT / 2 + 30
    ));
    
    restartText_.setFont(font_);
    restartText_.setString("RESTART");
    restartText_.setCharacterSize(24);
    restartText_.setFillColor(sf::Color::White);
    
    sf::FloatRect restartBounds = restartText_.getLocalBounds();
    sf::Vector2f buttonPos = restartButton_.getPosition();
    sf::Vector2f buttonSize = restartButton_.getSize();
    restartText_.setPosition(sf::Vector2f(
        buttonPos.x + (buttonSize.x - restartBounds.size.x) / 2 - restartBounds.position.x,
        buttonPos.y + (buttonSize.y - restartBounds.size.y) / 2 - restartBounds.position.y
    ));
    
    levelSelectorButton_.setSize(sf::Vector2f(200, 60));
    levelSelectorButton_.setFillColor(sf::Color(180, 70, 130));
    levelSelectorButton_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - 200) / 2,
        Constants::WINDOW_HEIGHT / 2 + 110
    ));
    
    levelSelectorText_.setFont(font_);
    levelSelectorText_.setString("SELECT LEVEL");
    levelSelectorText_.setCharacterSize(24);
    levelSelectorText_.setFillColor(sf::Color::White);
    
    sf::FloatRect levelSelectorBounds = levelSelectorText_.getLocalBounds();
    sf::Vector2f levelSelectorButtonPos = levelSelectorButton_.getPosition();
    sf::Vector2f levelSelectorButtonSize = levelSelectorButton_.getSize();
    levelSelectorText_.setPosition(sf::Vector2f(
        levelSelectorButtonPos.x + (levelSelectorButtonSize.x - levelSelectorBounds.size.x) / 2 - levelSelectorBounds.position.x,
        levelSelectorButtonPos.y + (levelSelectorButtonSize.y - levelSelectorBounds.size.y) / 2 - levelSelectorBounds.position.y
    ));
}

void GameOverScene::Draw(sf::RenderWindow& window) {
    window.draw(gameOverText_);
    window.draw(tryAgainText_);
    window.draw(restartButton_);
    window.draw(restartText_);
    window.draw(levelSelectorButton_);
    window.draw(levelSelectorText_);
    
    Scene::Draw(window);
}

bool GameOverScene::IsRestartButtonClicked(const sf::Vector2f& mousePos) const {
    return restartButton_.getGlobalBounds().contains(mousePos);
}

bool GameOverScene::IsLevelSelectorButtonClicked(const sf::Vector2f& mousePos) const {
    return levelSelectorButton_.getGlobalBounds().contains(mousePos);
}
