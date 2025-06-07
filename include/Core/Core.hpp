#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Scene;

class Core {
public:
    Core(unsigned int windowWidth, unsigned int windowHeight, const std::string& title);
    ~Core();

    void Run();
    void AddScene(Scene* scene);
    void RemoveScene(Scene* sceneToRemove);
    
    static void PlayBrickBreakSound();

private:
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void InitializeMusic();
    void InitializeSounds();

    sf::RenderWindow window_;
    sf::Clock clock_;
    std::vector<Scene*> scenes_;
    sf::Music backgroundMusic_;
    
    static sf::SoundBuffer brickBreakSoundBuffer_;
    static std::unique_ptr<sf::Sound> brickBreakSound_;
}; 