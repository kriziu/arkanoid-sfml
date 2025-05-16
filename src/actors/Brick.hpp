#pragma once
#include "../core/Actor.hpp"

namespace arkanoid {

enum class BrickType {
    Regular,
    Hard,
    Unbreakable
};

class Brick : public Actor {
public:
    Brick(Scene* scene, BrickType type = BrickType::Regular);
    ~Brick() override = default;
    
    void setType(BrickType type);
    BrickType getType() const;
    
    void hit();
    bool isDestroyed() const;

private:
    BrickType m_type;
    int m_hitPoints;
    bool m_destroyed;
};

} // namespace arkanoid 