#include "../../include/Scenes/Scene.hpp"
#include "../../include/Actors/Actor.hpp"
#include "../../include/Controllers/Controller.hpp"
#include <algorithm>

Scene::Scene() {}

Scene::~Scene() {
    for (auto& actor : actors_) {
        delete actor;
    }
    actors_.clear();
    
    for (auto& controller : controllers_) {
        delete controller;
    }
    controllers_.clear();
}

void Scene::Initialize() {
    SetActive(true);

    for (auto& actor : actors_) {
        actor->Initialize();
    }
    
    for (auto& controller : controllers_) {
        controller->Initialize();
    }
}

void Scene::Reset() {
    SetActive(false);
    
    for (auto& actor : actors_) {
        delete actor;
    }
    actors_.clear();
    
    Initialize();
}

void Scene::Update(float deltaTime) {
    for (auto& actor : actors_) {
        actor->Update(deltaTime);
    }
    
    for (auto& controller : controllers_) {
        controller->Update(deltaTime);
    }
}

void Scene::Draw(sf::RenderWindow& window) {
    for (auto& actor : actors_) {
        actor->Draw(window);
    }
}

void Scene::HandleEvent(const sf::Event& event) {
    for (auto& actor : actors_) {
        actor->HandleEvent(event);
    }
    
    for (auto& controller : controllers_) {
        controller->HandleEvent(event);
    }
}

void Scene::AddActor(Actor* actor) {
    actor->SetScene(this);
    actors_.push_back(actor);
}

void Scene::RemoveActor(Actor* actor) {
    auto it = std::find_if(actors_.begin(), actors_.end(), 
        [actor](const auto& a) { return a == actor; });
    
    if (it != actors_.end()) {
        actors_.erase(it);
    }
}

void Scene::AddController(Controller* controller) {
    controller->SetScene(this);
    controllers_.push_back(controller);
}

const std::vector<Actor*>& Scene::GetActors() const {
    return actors_;
} 

bool Scene::IsActive() const {
    return active_;
}

void Scene::SetActive(bool active) {
    active_ = active;
}