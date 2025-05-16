#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace arkanoid {

class Actor;

class Scene {
public:
    Scene(std::string name);
    virtual ~Scene();
    
    virtual void init() = 0;
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window);
    
    void addActor(std::shared_ptr<Actor> actor);
    void removeActor(const std::string& name);
    std::shared_ptr<Actor> getActor(const std::string& name);
    
    void addController(std::shared_ptr<Controller> controller);
    void removeController(const std::string& name);
    std::shared_ptr<Controller> getController(const std::string& name);
    
    const std::string& getName() const { return m_name; }

protected:
    std::string m_name;
    std::vector<std::shared_ptr<Actor>> m_actors;
    std::vector<std::shared_ptr<Controller>> m_controllers;
};

} // namespace arkanoid 