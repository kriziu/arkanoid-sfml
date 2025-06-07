#include "../../include/Core/Core.hpp"
#include "../../include/Scenes/Scene.hpp"

sf::SoundBuffer Core::brickBreakSoundBuffer_;
std::unique_ptr<sf::Sound> Core::brickBreakSound_;

Core::Core(unsigned int windowWidth, unsigned int windowHeight, const std::string& title) {
    window_.create(sf::VideoMode({windowWidth, windowHeight}), title, sf::Style::Titlebar | sf::Style::Close);
    InitializeMusic();
    InitializeSounds();
}

Core::~Core() {
    for (auto& scene : scenes_) {
        delete scene;
    }
    scenes_.clear();
}

void Core::InitializeMusic() {
    if (!backgroundMusic_.openFromFile("assets/music/background.ogg")) {
        return;
    }
    
    backgroundMusic_.setLooping(true);
    backgroundMusic_.setVolume(10.f);
    backgroundMusic_.play();
}

void Core::InitializeSounds() {
    if (!brickBreakSoundBuffer_.loadFromFile("assets/music/brick_brake.ogg")) {
        return;
    }
    
    brickBreakSound_ = std::make_unique<sf::Sound>(brickBreakSoundBuffer_);
    brickBreakSound_->setVolume(20.f);
}

void Core::PlayBrickBreakSound() {
    if (brickBreakSound_) {
        brickBreakSound_->play();
    }
}

void Core::Run() {
    for (auto& scene : scenes_) {
        scene->Initialize();
    }
    
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
            if (scene->IsActive()) {
                scene->HandleEvent(*event);
            }
        }
    }
}

void Core::Update(float deltaTime) {
    for (auto& scene : scenes_) {
        if (scene->IsActive()) {
            scene->Update(deltaTime);
        }
    }
}

void Core::Render() {
    window_.clear(sf::Color::Black);
    
    for (auto& scene : scenes_) {
        if (scene->IsActive()) {
            scene->Draw(window_);
        }
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