#include "../../include/Core/Core.hpp"
#include "../../include/Scenes/Scene.hpp"

sf::SoundBuffer Core::meowSoundBuffer_;
std::unique_ptr<sf::Sound> Core::meowSound_;

Core::Core(unsigned int windowWidth, unsigned int windowHeight, const std::string& title) {
    window_.create(sf::VideoMode({windowWidth, windowHeight}), title, sf::Style::Titlebar | sf::Style::Close);
    InitializeMusic();
    InitializeSounds();
}

Core::~Core() {}

void Core::InitializeMusic() {
    if (!backgroundMusic_.openFromFile("assets/music/background.mp3")) {
        return;
    }
    
    backgroundMusic_.setLooping(true);
    backgroundMusic_.setVolume(5.f);
    backgroundMusic_.play();
}

void Core::InitializeSounds() {
    if (!meowSoundBuffer_.loadFromFile("assets/music/meow.mp3")) {
        return;
    }
    
    meowSound_ = std::make_unique<sf::Sound>(meowSoundBuffer_);
    meowSound_->setVolume(20.f);
}

void Core::PlayMeowSound() {
    if (meowSound_) {
        meowSound_->play();
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