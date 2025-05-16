#pragma once
#include <SFML/Graphics.hpp>

class Actor;
class Scene;

class Controller {
public:
    Controller() : actor_(nullptr), scene_(nullptr) {}
    virtual ~Controller() {}
    
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    virtual void HandleEvent(const sf::Event& event) {}
    
    void SetActor(Actor* actor) { actor_ = actor; }
    Actor* GetActor() const { return actor_; }
    
    void SetScene(Scene* scene) { scene_ = scene; }
    Scene* GetScene() const { return scene_; }
    
protected:
    Actor* actor_;
    Scene* scene_;
}; 