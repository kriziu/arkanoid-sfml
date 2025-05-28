#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class Brick;

class BrickController : public Controller {
public:
    BrickController();
    ~BrickController() override;
    
    bool CheckCollision(const sf::FloatRect& other);
    void OnHit(int damage = 1);
}; 