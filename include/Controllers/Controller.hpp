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
    template<typename T>
    T* GetActor() const {
        if (!actor_) return nullptr;
        return dynamic_cast<T*>(actor_);
    }
    
    void SetScene(Scene* scene) { scene_ = scene; }
    template<typename T>
    T* GetScene() const {
        if (!scene_) return nullptr;
        return dynamic_cast<T*>(scene_);
    }
    
protected:
    Actor* actor_;
    Scene* scene_;
}; 