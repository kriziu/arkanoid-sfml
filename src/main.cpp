#include "../include/Core/Core.hpp"
#include "../include/Scenes/GameplayScene.hpp"
#include "../include/Controllers/SceneController.hpp"
#include "../include/Utils/Constants.hpp"

int main() {
    Core core(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Arkanoid SFML");
    
    GameplayScene* gameplayScene = new GameplayScene();
    gameplayScene->Initialize();
    
    SceneController sceneController(&core, gameplayScene);
    sceneController.Initialize();
    
    core.AddScene(gameplayScene);
    core.Run();
    
    return 0;
}
