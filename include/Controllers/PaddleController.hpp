#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class Paddle;

class PaddleController : public Controller {
public:
    PaddleController(Paddle* paddle);
    ~PaddleController() override;
    
    void Initialize() override;
    void Update(float deltaTime) override;
    void HandleEvent(const sf::Event& event) override;
    
private:
    Paddle* paddle_;
}; 