#pragma once
#include "Actor.hpp"
#include <SFML/Graphics.hpp>

enum class BrickType {
    Normal,
    Strong,
    Unbreakable
};

class Brick : public Actor {
public:
    Brick(BrickType type = BrickType::Normal);
    virtual ~Brick();
    
    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;
    
    void SetPosition(const sf::Vector2f& position);
    void SetSize(const sf::Vector2f& size);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSize() const;
    sf::FloatRect GetBounds() const;
    
    BrickType GetType() const;
    void SetType(BrickType type);
    
    int GetHitPoints() const;
    void TakeDamage(int damage = 1);
    bool IsDestroyed() const;
    
private:
    void UpdateVisualState();
    
    sf::RectangleShape shape_;
    BrickType type_;
    int hitPoints_;
    int maxHitPoints_;
    bool isDestroyed_;
    sf::Color baseColor_;
}; 