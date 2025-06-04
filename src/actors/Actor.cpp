#include "../../include/Actors/Actor.hpp"
#include "../../include/Controllers/Controller.hpp"
#include "../../include/Scenes/Scene.hpp"

Actor::Actor() : scene_(nullptr), size_(0, 0){}

Actor::~Actor() {
    for (auto& controller : controllers_) {
        delete controller;
    }
    controllers_.clear();
}

void Actor::Initialize() {
    for (auto& controller : controllers_) {
        controller->Initialize();
    }
}

void Actor::Reset() {
    Initialize();
}

void Actor::Update(float deltaTime) {
    for (auto& controller : controllers_) {
        controller->Update(deltaTime);
    }
}

void Actor::HandleEvent(const sf::Event& event) {
    for (auto& controller : controllers_) {
        controller->HandleEvent(event);
    }
}

void Actor::AddController(Controller* controller) {
    controller->SetActor(this);
    controller->SetScene(scene_);
    controllers_.push_back(controller);
}

void Actor::SetScene(Scene* scene) {
    scene_ = scene;
    for (auto& controller : controllers_) {
        controller->SetScene(scene);
    }
}

Scene* Actor::GetScene() const {
    return scene_;
}
