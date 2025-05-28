#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Controller;
class Scene;

class Actor {
public:
    Actor();
    virtual ~Actor();
    
    virtual void Initialize();
    virtual void Update(float deltaTime);
    virtual void HandleEvent(const sf::Event& event);
    virtual void Draw(sf::RenderWindow& window) {}
    
    void AddController(Controller* controller);
    void SetScene(Scene* scene);
    Scene* GetScene() const;
    
    template<typename T>
    T* GetController() {
        for (auto& controller : controllers_) {
            T* result = dynamic_cast<T*>(controller);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }
    
protected:
    std::vector<Controller*> controllers_;
    Scene* scene_;
    sf::Vector2f position_;
    sf::Vector2f size_;
}; 