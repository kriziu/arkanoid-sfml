#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Scene;

class Core {
public:
    Core(unsigned int windowWidth, unsigned int windowHeight, std::string title);
    ~Core();

    void Run();
    void AddScene(Scene* scene);
    void RemoveScene(Scene* sceneToRemove);

private:
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();

    sf::RenderWindow window_;
    sf::Clock clock_;
    std::vector<Scene*> scenes_;
}; 