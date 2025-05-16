#pragma once
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace arkanoid {

class Core {
public:
    Core();
    ~Core();
    
    void init(unsigned int width = 800, unsigned int height = 600, const std::string& title = "Arkanoid");
    void run();
    
    void addScene(std::shared_ptr<Scene> scene);
    void switchScene(const std::string& name);
    std::shared_ptr<Scene> getScene(const std::string& name);
    std::shared_ptr<Scene> getCurrentScene() const;
    
private:
    void processEvents();
    void update(float dt);
    void render();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    float m_deltaTime;
    
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_currentScene;
};

} // namespace arkanoid 