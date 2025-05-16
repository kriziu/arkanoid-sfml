#include "Paddle.hpp"

namespace arkanoid {

Paddle::Paddle(Scene* scene)
    : Actor("Paddle", scene), m_speed(400.f) {
    setSize(100.f, 20.f);
}

void Paddle::setSpeed(float speed) {
    m_speed = speed;
}

float Paddle::getSpeed() const {
    return m_speed;
}

} // namespace arkanoid 