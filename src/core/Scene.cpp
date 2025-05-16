#include "Scene.hpp"
#include "Actor.hpp"
#include <algorithm>

namespace arkanoid {

Scene::Scene(std::string name)
    : m_name(std::move(name)) {
}

Scene::~Scene() = default;

void Scene::update(float dt) {
    // Update scene-level controllers
    for (auto& controller : m_controllers) {
        controller->update(dt);
    }
    
    // Update all actors
    for (auto& actor : m_actors) {
        actor->update(dt);
    }
}

void Scene::render(sf::RenderWindow& window) {
    for (const auto& actor : m_actors) {
        window.draw(*actor);
    }
}

void Scene::addActor(std::shared_ptr<Actor> actor) {
    m_actors.push_back(actor);
}

void Scene::removeActor(const std::string& name) {
    auto it = std::find_if(m_actors.begin(), m_actors.end(),
        [&name](const auto& actor) {
            return actor->getName() == name;
        });
        
    if (it != m_actors.end()) {
        m_actors.erase(it);
    }
}

std::shared_ptr<Actor> Scene::getActor(const std::string& name) {
    auto it = std::find_if(m_actors.begin(), m_actors.end(),
        [&name](const auto& actor) {
            return actor->getName() == name;
        });
        
    if (it != m_actors.end()) {
        return *it;
    }
    
    return nullptr;
}

void Scene::addController(std::shared_ptr<Controller> controller) {
    controller->setOwnerScene(this);
    controller->onAttach();
    m_controllers.push_back(controller);
}

void Scene::removeController(const std::string& name) {
    auto it = std::find_if(m_controllers.begin(), m_controllers.end(),
        [&name](const auto& controller) {
            return controller->getName() == name;
        });
        
    if (it != m_controllers.end()) {
        (*it)->onDetach();
        m_controllers.erase(it);
    }
}

std::shared_ptr<Controller> Scene::getController(const std::string& name) {
    auto it = std::find_if(m_controllers.begin(), m_controllers.end(),
        [&name](const auto& controller) {
            return controller->getName() == name;
        });
        
    if (it != m_controllers.end()) {
        return *it;
    }
    
    return nullptr;
}

} // namespace arkanoid 