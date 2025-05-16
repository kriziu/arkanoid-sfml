#include "core/Core.hpp"
#include "scenes/GameplayScene.hpp"
#include <memory>
#include <iostream>

int main() {
    try {
        arkanoid::Core game;
        game.init(800, 600, "Arkanoid");
        
        auto gameplayScene = std::make_shared<arkanoid::GameplayScene>();
        game.addScene(gameplayScene);
        
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
