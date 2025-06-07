#include "../../include/Utils/SoundManager.hpp"
#include <cstdio>

std::unordered_map<std::string, sf::SoundBuffer> SoundManager::soundBuffers_;
std::unordered_map<std::string, std::unique_ptr<sf::Sound>> SoundManager::sounds_;
sf::Music SoundManager::backgroundMusic_;

void SoundManager::Initialize() {
    LoadSound("brick_break", "assets/music/brick_brake.ogg", 20.f);
    LoadSound("game_over", "assets/music/game_over.ogg", 50.f);
    LoadSound("life_loss", "assets/music/live_loss.ogg", 20.f);
    
    PlayMusic("background", true, 10.f);
}

void SoundManager::LoadSound(const std::string& soundName, const std::string& filePath, float volume) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        return;
    }
    
    soundBuffers_[soundName] = std::move(buffer);
    sounds_[soundName] = std::make_unique<sf::Sound>(soundBuffers_[soundName]);
    sounds_[soundName]->setVolume(volume);
    
}

void SoundManager::PlaySound(const std::string& soundName) {
    auto it = sounds_.find(soundName);
    if (it != sounds_.end() && it->second) {
        it->second->play();
    } 
}

void SoundManager::PlayMusic(const std::string& musicName, bool loop, float volume) {
    std::string musicPath = "assets/music/" + musicName + ".ogg";
    if (!backgroundMusic_.openFromFile(musicPath)) {
        return;
    }
    
    backgroundMusic_.setLooping(loop);
    backgroundMusic_.setVolume(volume);
    backgroundMusic_.play();
}

void SoundManager::StopMusic() {
    backgroundMusic_.stop();
}

void SoundManager::SetSoundVolume(const std::string& soundName, float volume) {
    auto it = sounds_.find(soundName);
    if (it != sounds_.end() && it->second) {
        it->second->setVolume(volume);
    }
}

void SoundManager::SetMusicVolume(float volume) {
    backgroundMusic_.setVolume(volume);
} 