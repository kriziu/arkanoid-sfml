#pragma once
#include "Scene.hpp"
#include "../Utils/LevelLoader.hpp"
#include <SFML/Graphics.hpp>

class Paddle;
class Ball;

class GameplayScene : public Scene {
public:
    GameplayScene();
    ~GameplayScene() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;
    bool LoadLevel(const std::string& levelFile);
    
private:
    void SetupUI();
    void DrawLivesDisplay(sf::RenderWindow& window);
    
    Paddle* paddle_;
    Ball* ball_;
    LevelData currentLevel_;
    sf::Font font_;
    sf::Text livesText_;
}; 