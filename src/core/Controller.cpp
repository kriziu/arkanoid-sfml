#include "Controller.hpp"
#include "Actor.hpp"
#include "Scene.hpp"

namespace arkanoid {

Controller::Controller(std::string name) 
    : m_name(std::move(name)), m_ownerActor(nullptr), m_ownerScene(nullptr) {
}

Controller::~Controller() {
    for (const auto& [type, id] : m_subscriptions) {
        MessageBus::getInstance().unsubscribe(type, id);
    }
}

void Controller::subscribeToMessage(MessageType type) {
    auto id = MessageBus::getInstance().subscribe(type, [this](const Message& msg) {
        this->handleMessage(msg);
    });
    m_subscriptions.emplace_back(type, id);
}

void Controller::setOwnerActor(Actor* actor) {
    m_ownerActor = actor;
    m_ownerScene = nullptr;
}

void Controller::setOwnerScene(Scene* scene) {
    m_ownerScene = scene;
    m_ownerActor = nullptr;
}

Actor* Controller::getOwnerActor() const {
    return m_ownerActor;
}

Scene* Controller::getOwnerScene() const {
    return m_ownerScene;
}

void Controller::publish(const Message& message) {
    MessageBus::getInstance().publish(message);
}

void Controller::publish(MessageType type, std::any payload) {
    void* sender = m_ownerActor ? static_cast<void*>(m_ownerActor) : 
                  (m_ownerScene ? static_cast<void*>(m_ownerScene) : nullptr);
    MessageBus::getInstance().publish(Message(type, sender, payload));
}

} // namespace arkanoid 