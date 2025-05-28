#include "../../include/Core/Core.hpp"
#include "../../include/Scenes/Scene.hpp"

Core::Core(unsigned int windowWidth, unsigned int windowHeight, std::string title) {
    window_.create(sf::VideoMode({windowWidth, windowHeight}), title, sf::Style::Titlebar | sf::Style::Close);
}

Core::~Core() {}

void Core::Run() {
    while (window_.isOpen()) {
        ProcessEvents();
        
        float deltaTime = clock_.restart().asSeconds();
        Update(deltaTime);
        
        Render();
    }
}

void Core::ProcessEvents() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }

        for (auto& scene : scenes_) {
            scene->HandleEvent(*event);
        }
    }
}

void Core::Update(float deltaTime) {
    for (auto& scene : scenes_) {
        scene->Update(deltaTime);
    }
}

void Core::Render() {
    window_.clear(sf::Color::Black);
    
    for (auto& scene : scenes_) {
        scene->Draw(window_);
    }
    
    window_.display();
}

void Core::AddScene(Scene* scene) {
    scenes_.push_back(scene);
}

void Core::RemoveScene(Scene* sceneToRemove) {
    for (auto it = scenes_.begin(); it != scenes_.end(); ++it) {
        if (*it == sceneToRemove) {
            scenes_.erase(it);
            break;
        }
    }
} 