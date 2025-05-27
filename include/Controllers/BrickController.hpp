#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class Brick;

class BrickController : public Controller {
public:
    BrickController();
    virtual ~BrickController();
    
    void Initialize() override;
    void Update(float deltaTime) override;
    void HandleEvent(const sf::Event& event) override;
    
    bool CheckCollision(const sf::FloatRect& other);
    void OnHit(int damage = 1);
    
private:
    Brick* GetBrick();
}; 