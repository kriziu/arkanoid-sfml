#pragma once
#include "../core/Actor.hpp"

namespace arkanoid {

class Paddle : public Actor {
public:
    Paddle(Scene* scene);
    ~Paddle() override = default;
    
    void setSpeed(float speed);
    float getSpeed() const;

private:
    float m_speed;
};

} // namespace arkanoid 