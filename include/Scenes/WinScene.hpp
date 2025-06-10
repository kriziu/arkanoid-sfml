#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class WinScene : public Scene {
public:
    WinScene();
    ~WinScene() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;

    bool IsLevelRestartButtonClicked(const sf::Vector2f& mousePos) const;
    bool IsLevelSelectorButtonClicked(const sf::Vector2f& mousePos) const;

private:
    sf::Font font_;
    sf::Text winText_;
    sf::Text congratulationsText_;
    sf::Text levelRestartText_;
    sf::RectangleShape levelRestartButton_;
    sf::Text levelSelectorText_;
    sf::RectangleShape levelSelectorButton_;
    bool fontLoaded_;
    
    void SetupUI();
}; 