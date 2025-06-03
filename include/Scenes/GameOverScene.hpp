#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class GameOverScene : public Scene {
public:
    GameOverScene();
    ~GameOverScene() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;

    bool IsRestartButtonClicked(const sf::Vector2f& mousePos) const;

private:
    sf::Font font_;
    sf::Text gameOverText_;
    sf::Text restartText_;
    sf::RectangleShape restartButton_;
    sf::Text tryAgainText_;
    bool fontLoaded_;
    
    void SetupUI();
}; 