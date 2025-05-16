#pragma once
#include "../core/Scene.hpp"

namespace arkanoid {

class GameplayScene : public Scene {
public:
    GameplayScene();
    ~GameplayScene() override = default;
    
    void init() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    
    void createLevel();
    void resetBall();

private:
    int m_lives;
    int m_score;
};

} // namespace arkanoid 