#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Actor;
class Controller;

class Scene {
public:
    Scene();
    virtual ~Scene();
    
    virtual void Initialize();
    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow& window);
    virtual void HandleEvent(const sf::Event& event);
    
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void AddController(Controller* controller);
    
    template<typename T>
    T* GetActor();
    
protected:
    std::vector<Actor*> actors_;
    std::vector<Controller*> controllers_;
}; 