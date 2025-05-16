#include "Brick.hpp"
#include "../core/MessageBus.hpp"

namespace arkanoid {

Brick::Brick(Scene* scene, BrickType type)
    : Actor("Brick", scene), m_type(type), m_hitPoints(0), m_destroyed(false) {
    setSize(60.f, 20.f);
    setType(type);
}

void Brick::setType(BrickType type) {
    m_type = type;
    
    switch (m_type) {
        case BrickType::Regular:
            m_hitPoints = 1;
            break;
        case BrickType::Hard:
            m_hitPoints = 2;
            break;
        case BrickType::Unbreakable:
            m_hitPoints = -1;
            break;
    }
}

BrickType Brick::getType() const {
    return m_type;
}

void Brick::hit() {
    if (m_type == BrickType::Unbreakable || m_destroyed) {
        return;
    }
    
    m_hitPoints--;
    
    if (m_hitPoints <= 0) {
        m_destroyed = true;
        MessageBus::getInstance().publish(Message(MessageType::BrickDestroyed, this));
    }
}

bool Brick::isDestroyed() const {
    return m_destroyed;
}

} // namespace arkanoid 