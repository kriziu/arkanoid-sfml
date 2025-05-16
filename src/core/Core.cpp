#include "Core.hpp"
#include <iostream>

namespace arkanoid {

Core::Core() : m_deltaTime(0.f) {
}

Core::~Core() {
    if (m_window.isOpen()) {
        m_window.close();
    }
}

void Core::init(unsigned int width, unsigned int height, const std::string& title) {
    m_window.create(sf::VideoMode(width, height), title);
    m_window.setFramerateLimit(60);
}

void Core::run() {
    if (!m_currentScene) {
        std::cerr << "No active scene to run!" << std::endl;
        return;
    }

    m_clock.restart();
    
    while (m_window.isOpen()) {
        m_deltaTime = m_clock.restart().asSeconds();
        
        processEvents();
        update(m_deltaTime);
        render();
    }
}

void Core::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void Core::update(float dt) {
    if (m_currentScene) {
        m_currentScene->update(dt);
    }
}

void Core::render() {
    m_window.clear(sf::Color::Black);
    
    if (m_currentScene) {
        m_currentScene->render(m_window);
    }
    
    m_window.display();
}

void Core::addScene(std::shared_ptr<Scene> scene) {
    m_scenes[scene->getName()] = scene;
    
    if (!m_currentScene) {
        m_currentScene = scene;
        m_currentScene->init();
    }
}

void Core::switchScene(const std::string& name) {
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
        m_currentScene = it->second;
        m_currentScene->init();
    }
}

std::shared_ptr<Scene> Core::getScene(const std::string& name) {
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
        return it->second;
    }
    
    return nullptr;
}

std::shared_ptr<Scene> Core::getCurrentScene() const {
    return m_currentScene;
}

} // namespace arkanoid 