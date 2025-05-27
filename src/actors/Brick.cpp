#include "../../include/Actors/Brick.hpp"
#include "../../include/Utils/MessageBus.hpp"

Brick::Brick(BrickType type) : Actor(), type_(type), isDestroyed_(false) {
    switch (type_) {
        case BrickType::Normal:
            maxHitPoints_ = 1;
            baseColor_ = sf::Color(255, 95, 31);
            break;
        case BrickType::Strong:
            maxHitPoints_ = 2;
            baseColor_ = sf::Color(52, 152, 219);
            break;
        case BrickType::Unbreakable:
            maxHitPoints_ = -1;
            baseColor_ = sf::Color(149, 165, 166);
            break;
    }
    hitPoints_ = maxHitPoints_;
    
    shape_.setSize(sf::Vector2f(60.0f, 25.0f));
    shape_.setOutlineThickness(2.0f);
    shape_.setOutlineColor(sf::Color(44, 62, 80));
    UpdateVisualState();
}

Brick::~Brick() {}

void Brick::Initialize() {
    Actor::Initialize();
}

void Brick::Draw(sf::RenderWindow& window) {
    if (!isDestroyed_) {
        window.draw(shape_);
    }
}

void Brick::SetPosition(const sf::Vector2f& position) {
    position_ = position;
    shape_.setPosition(position);
}

void Brick::SetSize(const sf::Vector2f& size) {
    size_ = size;
    shape_.setSize(size);
}

sf::Vector2f Brick::GetPosition() const {
    return position_;
}

sf::Vector2f Brick::GetSize() const {
    return size_;
}

sf::FloatRect Brick::GetBounds() const {
    return shape_.getGlobalBounds();
}

BrickType Brick::GetType() const {
    return type_;
}

void Brick::SetType(BrickType type) {
    type_ = type;
    switch (type_) {
        case BrickType::Normal:
            maxHitPoints_ = 1;
            baseColor_ = sf::Color(255, 95, 31);
            break;
        case BrickType::Strong:
            maxHitPoints_ = 2;
            baseColor_ = sf::Color(52, 152, 219);
            break;
        case BrickType::Unbreakable:
            maxHitPoints_ = -1;
            baseColor_ = sf::Color(149, 165, 166);
            break;
    }
    hitPoints_ = maxHitPoints_;
    UpdateVisualState();
}

int Brick::GetHitPoints() const {
    return hitPoints_;
}

void Brick::TakeDamage(int damage) {
    if (type_ == BrickType::Unbreakable || isDestroyed_) {
        return;
    }
    
    hitPoints_ -= damage;
    
    if (hitPoints_ <= 0) {
        isDestroyed_ = true;
        Message message;
        message.type = MessageType::BrickDestroyed;
        message.sender = this;
        message.payload = static_cast<int>(type_);
        MessageBus::Publish(message);
    }
    
    UpdateVisualState();
}

bool Brick::IsDestroyed() const {
    return isDestroyed_;
}

void Brick::UpdateVisualState() {
    if (isDestroyed_) {
        shape_.setFillColor(sf::Color::Transparent);
        shape_.setOutlineColor(sf::Color::Transparent);
        return;
    }
    
    sf::Color currentColor = baseColor_;
    
    if (type_ == BrickType::Strong && hitPoints_ == 1) {
        currentColor.r = static_cast<uint8_t>(currentColor.r * 0.7f);
        currentColor.g = static_cast<uint8_t>(currentColor.g * 0.7f);
        currentColor.b = static_cast<uint8_t>(currentColor.b * 0.7f);
        
        sf::Color outlineColor = sf::Color(44, 62, 80);
        outlineColor.a = 180;
        shape_.setOutlineColor(outlineColor);
    } else {
        shape_.setOutlineColor(sf::Color(44, 62, 80));
    }
    
    sf::Color brightColor = currentColor;
    brightColor.r = std::min(255, (int)(brightColor.r * 1.1f));
    brightColor.g = std::min(255, (int)(brightColor.g * 1.1f));
    brightColor.b = std::min(255, (int)(brightColor.b * 1.1f));
    
    shape_.setFillColor(brightColor);
} 