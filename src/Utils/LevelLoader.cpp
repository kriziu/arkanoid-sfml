#include "../../include/Utils/LevelLoader.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Controllers/BrickController.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

bool LevelLoader::LoadLevel(const std::string& filename, LevelData& levelData) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open level file: " << filename << std::endl;
        return false;
    }
    
    levelData.bricks.clear();
    
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Failed to read level header" << std::endl;
        return false;
    }
    
    if (sscanf(line.c_str(), "%d %d %f %f %f %f %f", 
               &levelData.width, &levelData.height,
               &levelData.brickWidth, &levelData.brickHeight, &levelData.spacing,
               &levelData.startPosition.x, &levelData.startPosition.y) != 7) {
        std::cerr << "Invalid level header format" << std::endl;
        return false;
    }
    
    int currentRow = 0;
    while (std::getline(file, line) && currentRow < levelData.height) {
        for (int col = 0; col < (int)line.length() && col < levelData.width; ++col) {
            char brickChar = line[col];
            if (brickChar != ' ' && brickChar != '.') {
                BrickData brickData;
                brickData.position = {col, currentRow};
                
                switch (brickChar) {
                    case '1':
                        brickData.type = BrickType::Normal;
                        break;
                    case '2':
                        brickData.type = BrickType::Strong;
                        break;
                    case 'X':
                        brickData.type = BrickType::Unbreakable;
                        break;
                    default:
                        continue;
                }
                
                levelData.bricks.push_back(brickData);
            }
        }
        currentRow++;
    }
    
    file.close();
    return true;
}

bool LevelLoader::LoadBricksIntoScene(const LevelData& levelData, Scene* scene) {
    if (!scene) {
        return false;
    }
    
    for (const auto& brickData : levelData.bricks) {
        Brick* brick = new Brick(brickData.type);
        sf::Vector2f worldPos = GridToWorldPosition(brickData.position, levelData);
        
        brick->SetPosition(worldPos);
        brick->SetSize(sf::Vector2f(levelData.brickWidth, levelData.brickHeight));
        
        BrickController* controller = new BrickController();
        brick->AddController(controller);
        
        scene->AddActor(brick);
    }
    
    return true;
}

std::vector<std::string> LevelLoader::GetAvailableLevels(const std::string& levelsDirectory) {
    std::vector<std::string> levelFiles;
    
    if (!std::filesystem::exists(levelsDirectory)) {
        std::cerr << "Levels directory does not exist: " << levelsDirectory << std::endl;
        return levelFiles;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(levelsDirectory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".level") {
            levelFiles.push_back(entry.path().string());
        }
    }
    
    return levelFiles;
}

sf::Vector2f LevelLoader::GridToWorldPosition(const GridPosition& gridPos, const LevelData& levelData) {
    float x = levelData.startPosition.x + gridPos.x * (levelData.brickWidth + levelData.spacing);
    float y = levelData.startPosition.y + gridPos.y * (levelData.brickHeight + levelData.spacing);
    return sf::Vector2f(x, y);
}

BrickType LevelLoader::StringToBrickType(const std::string& typeStr) {
    if (typeStr == "normal") return BrickType::Normal;
    if (typeStr == "strong") return BrickType::Strong;
    if (typeStr == "unbreakable") return BrickType::Unbreakable;
    return BrickType::Normal;
} 