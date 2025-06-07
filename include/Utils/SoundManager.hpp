#pragma once
#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>
#include <string>

class SoundManager {
public:
    static void Initialize();
    static void PlaySound(const std::string& soundName);
    static void PlayMusic(const std::string& musicName, bool loop = true, float volume = 10.f);
    static void StopMusic();
    static void SetSoundVolume(const std::string& soundName, float volume);
    static void SetMusicVolume(float volume);

private:
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers_;
    static std::unordered_map<std::string, std::unique_ptr<sf::Sound>> sounds_;
    static sf::Music backgroundMusic_;
    
    static void LoadSound(const std::string& soundName, const std::string& filePath, float volume = 50.f);
}; 