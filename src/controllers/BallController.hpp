#pragma once
#include "../core/Controller.hpp"

namespace arkanoid {

class Ball;

class BallController : public Controller {
public:
    BallController();
    ~BallController() override = default;
    
    void update(float dt) override;
    void onAttach() override;
    void handleMessage(const Message& message) override;

private:
    void checkCollisions();
    void checkWallCollisions();
    void checkPaddleCollision();
    void checkBrickCollisions();
    
    Ball* m_ball;
};

} // namespace arkanoid 