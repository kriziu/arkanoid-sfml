#include "Ball.hpp"
#include "../core/Scene.hpp"

namespace arkanoid {

Ball::Ball(Scene* scene)
    : Actor("Ball", scene), m_velocity(0.f, 0.f), m_radius(10.f) {
    setSize(m_radius * 2.f, m_radius * 2.f);
}

void Ball::setVelocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}

const sf::Vector2f& Ball::getVelocity() const {
    return m_velocity;
}

void Ball::setRadius(float radius) {
    m_radius = radius;
    setSize(m_radius * 2.f, m_radius * 2.f);
}

float Ball::getRadius() const {
    return m_radius;
}

} // namespace arkanoid 