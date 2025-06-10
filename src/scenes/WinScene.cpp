#include <iostream>
#include <string>
#include "../../include/Scenes/WinScene.hpp"
#include "../../include/Utils/Constants.hpp"

WinScene::WinScene() :
    winText_(sf::Text(font_)),
    congratulationsText_(sf::Text(font_)),
    timeText_(sf::Text(font_)),
    levelRestartText_(sf::Text(font_)),
    levelSelectorText_(sf::Text(font_)),
    levelRestartButton_(sf::RectangleShape()),
    levelSelectorButton_(sf::RectangleShape()) {}

WinScene::~WinScene() {}

void WinScene::Initialize() {
    Scene::Initialize();

    SetActive(false);
    SetupUI();
}

void WinScene::SetupUI() {
    if (!font_.openFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    winText_.setFont(font_);
    winText_.setString("LEVEL COMPLETE!");
    winText_.setCharacterSize(72);
    winText_.setFillColor(sf::Color::Green);
    
    sf::FloatRect winBounds = winText_.getLocalBounds();
    winText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - winBounds.size.x) / 2,
        Constants::WINDOW_HEIGHT / 2 - 100
    ));
    
    congratulationsText_.setFont(font_);
    congratulationsText_.setString("CONGRATULATIONS!");
    congratulationsText_.setCharacterSize(36);
    congratulationsText_.setFillColor(sf::Color::White);
    
    sf::FloatRect congratsBounds = congratulationsText_.getLocalBounds();
    congratulationsText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - congratsBounds.size.x) / 2 - congratsBounds.position.x,
        Constants::WINDOW_HEIGHT / 2 - 20
    ));
    
    timeText_.setFont(font_);
    timeText_.setString("Time: 0.00s");
    timeText_.setCharacterSize(28);
    timeText_.setFillColor(sf::Color::Yellow);
    
    sf::FloatRect timeBounds = timeText_.getLocalBounds();
    timeText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - timeBounds.size.x) / 2 - timeBounds.position.x,
        Constants::WINDOW_HEIGHT / 2 + 20
    ));
    
    levelRestartButton_.setSize(sf::Vector2f(200, 60));
    levelRestartButton_.setFillColor(sf::Color(34, 139, 34));
    levelRestartButton_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - 200) / 2,
        Constants::WINDOW_HEIGHT / 2 + 60
    ));
    
    levelRestartText_.setFont(font_);
    levelRestartText_.setString("PLAY AGAIN");
    levelRestartText_.setCharacterSize(24);
    levelRestartText_.setFillColor(sf::Color::White);
    
    sf::FloatRect restartBounds = levelRestartText_.getLocalBounds();
    sf::Vector2f buttonPos = levelRestartButton_.getPosition();
    sf::Vector2f buttonSize = levelRestartButton_.getSize();
    levelRestartText_.setPosition(sf::Vector2f(
        buttonPos.x + (buttonSize.x - restartBounds.size.x) / 2 - restartBounds.position.x,
        buttonPos.y + (buttonSize.y - restartBounds.size.y) / 2 - restartBounds.position.y
    ));
    
    levelSelectorButton_.setSize(sf::Vector2f(200, 60));
    levelSelectorButton_.setFillColor(sf::Color(180, 70, 130));
    levelSelectorButton_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - 200) / 2,
        Constants::WINDOW_HEIGHT / 2 + 140
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

void WinScene::Draw(sf::RenderWindow& window) {
    window.draw(winText_);
    window.draw(congratulationsText_);
    window.draw(timeText_);
    window.draw(levelRestartButton_);
    window.draw(levelRestartText_);
    window.draw(levelSelectorButton_);
    window.draw(levelSelectorText_);
    
    Scene::Draw(window);
}

void WinScene::SetCompletionTime(float timeInSeconds) {
    int minutes = static_cast<int>(timeInSeconds) / 60;
    float seconds = timeInSeconds - (minutes * 60);
    
    std::string timeString;
    if (minutes > 0) {
        timeString = "Time: " + std::to_string(minutes) + ":" + std::to_string(static_cast<int>(seconds)) + "." + std::to_string(static_cast<int>((seconds - static_cast<int>(seconds)) * 100)) + "s";
    } else {
        timeString = "Time: " + std::to_string(static_cast<int>(seconds)) + "." + std::to_string(static_cast<int>((seconds - static_cast<int>(seconds)) * 100)) + "s";
    }
    
    timeText_.setString(timeString);
    
    sf::FloatRect timeBounds = timeText_.getLocalBounds();
    timeText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - timeBounds.size.x) / 2 - timeBounds.position.x,
        Constants::WINDOW_HEIGHT / 2 + 20
    ));
}

bool WinScene::IsLevelRestartButtonClicked(const sf::Vector2f& mousePos) const {
    return levelRestartButton_.getGlobalBounds().contains(mousePos);
}

bool WinScene::IsLevelSelectorButtonClicked(const sf::Vector2f& mousePos) const {
    return levelSelectorButton_.getGlobalBounds().contains(mousePos);
} 