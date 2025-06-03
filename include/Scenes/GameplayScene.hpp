#pragma once
#include "Scene.hpp"
#include "../Utils/LevelLoader.hpp"

class Paddle;

class GameplayScene : public Scene {
public:
    GameplayScene();
    ~GameplayScene() override;

    void Initialize() override;
    bool LoadLevel(const std::string& levelFile);
    void RestartLevel();
    
private:
    Paddle* paddle_;
    LevelData currentLevel_;
}; 