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
    T* GetController();
    
    void SetPosition(float x, float y) { position_ = {x, y}; }
    const sf::Vector2f& GetPosition() const { return position_; }
    void SetSize(float width, float height) { size_ = {width, height}; }
    const sf::Vector2f& GetSize() const { return size_; }
    
protected:
    std::vector<Controller*> controllers_;
    Scene* scene_;
    sf::Vector2f position_;
    sf::Vector2f size_;
}; 