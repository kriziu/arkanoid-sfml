#include "../include/Core/Core.hpp"
#include "../include/Scenes/GameplayScene.hpp"

int main() {
    Core core(800, 600, "Arkanoid SFML");
    
    GameplayScene gameplayScene;
    gameplayScene.Initialize();
    
    core.AddScene(&gameplayScene);
    core.Run();
    
    return 0;
}
