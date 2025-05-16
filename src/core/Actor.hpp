#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace arkanoid {

class Scene;

class Actor : public sf::Drawable {
public:
    Actor(std::string name, Scene* scene);
    virtual ~Actor();

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void addController(std::shared_ptr<Controller> controller);
    void removeController(const std::string& name);
    std::shared_ptr<Controller> getController(const std::string& name);
    
    const std::string& getName() const { return m_name; }
    Scene* getScene() const { return m_scene; }
    
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;
    
    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);
    const sf::Vector2f& getSize() const;
    
    sf::FloatRect getBounds() const;

protected:
    std::string m_name;
    Scene* m_scene;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Sprite m_sprite;
    
    std::vector<std::shared_ptr<Controller>> m_controllers;
};

} // namespace arkanoid 