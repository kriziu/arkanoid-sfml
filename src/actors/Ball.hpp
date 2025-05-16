#pragma once
#include "../core/Actor.hpp"

namespace arkanoid {

class Ball : public Actor {
public:
    Ball(Scene* scene);
    ~Ball() override = default;
    
    void setVelocity(const sf::Vector2f& velocity);
    const sf::Vector2f& getVelocity() const;
    
    void setRadius(float radius);
    float getRadius() const;

private:
    sf::Vector2f m_velocity;
    float m_radius;
};

} // namespace arkanoid 