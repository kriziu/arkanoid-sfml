#include <iostream>
#include <string>
#include "../../include/Scenes/PauseScene.hpp"
#include "../../include/Utils/Constants.hpp"

PauseScene::PauseScene() :
    pauseText_(sf::Text(font_)),
    resumeText_(sf::Text(font_)),
    menuText_(sf::Text(font_)),
    resumeButton_(sf::RectangleShape()),
    menuButton_(sf::RectangleShape()) {}

PauseScene::~PauseScene() {}

void PauseScene::Initialize() {
    Scene::Initialize();

    SetActive(false);
    SetupUI();
}

void PauseScene::SetupUI() {
    if (!font_.openFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    
    pauseText_.setFont(font_);
    pauseText_.setString("PAUSE");
    pauseText_.setCharacterSize(72);
    pauseText_.setFillColor(sf::Color::White);
    
    sf::FloatRect pauseBounds = pauseText_.getLocalBounds();
    pauseText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - pauseBounds.size.x) / 2,
        Constants::WINDOW_HEIGHT / 2 - 100
    ));
    
    resumeButton_.setSize(sf::Vector2f(200, 60));
    resumeButton_.setFillColor(sf::Color(34, 139, 34));
    resumeButton_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - 200) / 2,
        Constants::WINDOW_HEIGHT / 2 + 20
    ));
    
    resumeText_.setFont(font_);
    resumeText_.setString("RETURN TO GAME");
    resumeText_.setCharacterSize(20);
    resumeText_.setFillColor(sf::Color::White);
    
    sf::FloatRect resumeBounds = resumeText_.getLocalBounds();
    sf::Vector2f resumeButtonPos = resumeButton_.getPosition();
    sf::Vector2f resumeButtonSize = resumeButton_.getSize();
    resumeText_.setPosition(sf::Vector2f(
        resumeButtonPos.x + (resumeButtonSize.x - resumeBounds.size.x) / 2 - resumeBounds.position.x,
        resumeButtonPos.y + (resumeButtonSize.y - resumeBounds.size.y) / 2 - resumeBounds.position.y
    ));
    
    menuButton_.setSize(sf::Vector2f(200, 60));
    menuButton_.setFillColor(sf::Color(180, 70, 130));
    menuButton_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - 200) / 2,
        Constants::WINDOW_HEIGHT / 2 + 100
    ));
    
    menuText_.setFont(font_);
    menuText_.setString("GO TO MENU");
    menuText_.setCharacterSize(24);
    menuText_.setFillColor(sf::Color::White);
    
    sf::FloatRect menuBounds = menuText_.getLocalBounds();
    sf::Vector2f menuButtonPos = menuButton_.getPosition();
    sf::Vector2f menuButtonSize = menuButton_.getSize();
    menuText_.setPosition(sf::Vector2f(
        menuButtonPos.x + (menuButtonSize.x - menuBounds.size.x) / 2 - menuBounds.position.x,
        menuButtonPos.y + (menuButtonSize.y - menuBounds.size.y) / 2 - menuBounds.position.y
    ));
}

void PauseScene::Draw(sf::RenderWindow& window) {
    sf::RectangleShape overlay(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));
    window.draw(overlay);
    
    window.draw(pauseText_);
    window.draw(resumeButton_);
    window.draw(resumeText_);
    window.draw(menuButton_);
    window.draw(menuText_);
    
    Scene::Draw(window);
}

bool PauseScene::IsResumeButtonClicked(const sf::Vector2f& mousePos) const {
    return resumeButton_.getGlobalBounds().contains(mousePos);
}

bool PauseScene::IsMenuButtonClicked(const sf::Vector2f& mousePos) const {
    return menuButton_.getGlobalBounds().contains(mousePos);
} 