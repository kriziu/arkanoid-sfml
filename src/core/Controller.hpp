#pragma once
#include "MessageBus.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace arkanoid {

class Actor;
class Scene;

class Controller {
public:
    Controller(std::string name);
    virtual ~Controller();

    virtual void update(float dt) = 0;
    virtual void onAttach() {}
    virtual void onDetach() {}
    
    void subscribeToMessage(MessageType type);
    virtual void handleMessage(const Message& message) {}

    const std::string& getName() const { return m_name; }
    
    void setOwnerActor(Actor* actor);
    void setOwnerScene(Scene* scene);
    Actor* getOwnerActor() const;
    Scene* getOwnerScene() const;

protected:
    void publish(const Message& message);
    void publish(MessageType type, std::any payload = {});

    std::string m_name;
    Actor* m_ownerActor;
    Scene* m_ownerScene;
    
private:
    std::vector<std::pair<MessageType, MessageBus::HandlerId>> m_subscriptions;
};

} // namespace arkanoid 