#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class PauseScene : public Scene {
public:
    PauseScene();
    ~PauseScene() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;

    bool IsResumeButtonClicked(const sf::Vector2f& mousePos) const;
    bool IsMenuButtonClicked(const sf::Vector2f& mousePos) const;

private:
    void SetupUI();

    sf::Font font_;
    sf::Text pauseText_;
    sf::Text resumeText_;
    sf::RectangleShape resumeButton_;
    sf::Text menuText_;
    sf::RectangleShape menuButton_;
}; 