#include "../include/Core/Core.hpp"
#include "../include/Scenes/GameplayScene.hpp"
#include "../include/Scenes/GameOverScene.hpp"
#include "../include/Scenes/WinScene.hpp"
#include "../include/Scenes/LevelSelectorScene.hpp"
#include "../include/Controllers/GameplaySceneController.hpp"
#include "../include/Controllers/GameOverSceneController.hpp"
#include "../include/Controllers/WinSceneController.hpp"
#include "../include/Controllers/LevelSelectorSceneController.hpp"
#include "../include/Controllers/LevelTrackerController.hpp"
#include "../include/Utils/Constants.hpp"

int main() {
    Core core(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Arkanoid SFML");
    
    LevelSelectorScene* levelSelectorScene = new LevelSelectorScene();
    levelSelectorScene->AddController(new LevelSelectorSceneController());
    
    GameplayScene* gameplayScene = new GameplayScene();
    gameplayScene->AddController(new GameplaySceneController());
    gameplayScene->AddController(new LevelTrackerController());

    GameOverScene* gameOverScene = new GameOverScene();
    gameOverScene->AddController(new GameOverSceneController());

    WinScene* winScene = new WinScene();
    winScene->AddController(new WinSceneController());

    core.AddScene(levelSelectorScene);
    core.AddScene(gameplayScene);
    core.AddScene(gameOverScene);
    core.AddScene(winScene);

    core.Run();
    
    return 0;
}
