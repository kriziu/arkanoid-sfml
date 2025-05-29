#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class Paddle;

class PaddleController : public Controller {
public:
    PaddleController();
    ~PaddleController() override;
    
    void Initialize() override;
    void HandleEvent(const sf::Event& event) override;
}; 