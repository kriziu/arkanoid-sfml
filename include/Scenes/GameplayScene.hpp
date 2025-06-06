#pragma once
#include "Scene.hpp"
#include "../Utils/LevelLoader.hpp"
#include <SFML/Graphics.hpp>

class Paddle;

class GameplayScene : public Scene {
public:
    GameplayScene();
    ~GameplayScene() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;
    bool LoadLevel(const std::string& levelFilename);
    void SetLevelFilename(const std::string& levelFilename);
    
private:
    void SetupUI();
    void DrawLivesDisplay(sf::RenderWindow& window);
    
    Paddle* paddle_;
    LevelData currentLevel_;
    sf::Font iconsFont_;
    sf::Text livesText_;
    std::string selectedLevelFilename_;
}; 