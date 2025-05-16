#pragma once
#include "Scene.hpp"

class Paddle;

class GameplayScene : public Scene {
public:
    GameplayScene();
    ~GameplayScene() override;
    
    void Initialize() override;
    
private:
    Paddle* paddle_;
}; 