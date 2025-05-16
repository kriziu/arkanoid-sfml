#include "Actor.hpp"
#include "Scene.hpp"
#include <algorithm>

namespace arkanoid {

Actor::Actor(std::string name, Scene* scene)
    : m_name(std::move(name)), m_scene(scene), m_position(0.f, 0.f), m_size(0.f, 0.f) {
}

Actor::~Actor() = default;

void Actor::update(float dt) {
    for (auto& controller : m_controllers) {
        controller->update(dt);
    }
}

void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Actor::addController(std::shared_ptr<Controller> controller) {
    controller->setOwnerActor(this);
    controller->onAttach();
    m_controllers.push_back(controller);
}

void Actor::removeController(const std::string& name) {
    auto it = std::find_if(m_controllers.begin(), m_controllers.end(),
        [&name](const auto& controller) {
            return controller->getName() == name;
        });
        
    if (it != m_controllers.end()) {
        (*it)->onDetach();
        m_controllers.erase(it);
    }
}

std::shared_ptr<Controller> Actor::getController(const std::string& name) {
    auto it = std::find_if(m_controllers.begin(), m_controllers.end(),
        [&name](const auto& controller) {
            return controller->getName() == name;
        });
        
    if (it != m_controllers.end()) {
        return *it;
    }
    
    return nullptr;
}

void Actor::setPosition(float x, float y) {
    m_position = sf::Vector2f(x, y);
    m_sprite.setPosition(m_position);
}

void Actor::setPosition(const sf::Vector2f& position) {
    m_position = position;
    m_sprite.setPosition(m_position);
}

const sf::Vector2f& Actor::getPosition() const {
    return m_position;
}

void Actor::setSize(float width, float height) {
    m_size = sf::Vector2f(width, height);
    
    if (m_sprite.getTexture()) {
        sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
        m_sprite.setScale(
            m_size.x / textureSize.x,
            m_size.y / textureSize.y
        );
    }
}

void Actor::setSize(const sf::Vector2f& size) {
    setSize(size.x, size.y);
}

const sf::Vector2f& Actor::getSize() const {
    return m_size;
}

sf::FloatRect Actor::getBounds() const {
    return sf::FloatRect(m_position, m_size);
}

} // namespace arkanoid 