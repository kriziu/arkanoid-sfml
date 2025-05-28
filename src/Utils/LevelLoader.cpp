#include "../../include/Utils/LevelLoader.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Controllers/BrickController.hpp"
#include <fstream>
#include <iostream>

bool LevelLoader::LoadLevel(std::string filename, LevelData& levelData) {
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
            if (brickChar != '.') {
                BrickData brickData;
                brickData.position = {col, currentRow};
                brickData.type = GetBrickType(brickChar);
                
                levelData.bricks.push_back(brickData);
            }
        }
        currentRow++;
    }
    
    file.close();
    return true;
}

bool LevelLoader::LoadBricksIntoScene(const LevelData& levelData, Scene* scene) {
    for (const auto& brickData : levelData.bricks) {
        Brick* brick = new Brick(brickData.type);
        sf::Vector2f worldPos = GridToWorldPosition(brickData.position, levelData);
        
        brick->SetPosition(worldPos);
        brick->SetSize(sf::Vector2f(levelData.brickWidth, levelData.brickHeight));
        brick->AddController(new BrickController());
        
        scene->AddActor(brick);
    }
    
    return true;
}

sf::Vector2f LevelLoader::GridToWorldPosition(const GridPosition& gridPos, const LevelData& levelData) {
    float x = levelData.startPosition.x + gridPos.x * (levelData.brickWidth + levelData.spacing);
    float y = levelData.startPosition.y + gridPos.y * (levelData.brickHeight + levelData.spacing);
    return sf::Vector2f(x, y);
}

BrickType LevelLoader::GetBrickType(char brickChar) {
    switch (brickChar) {
        case '1': return BrickType::Normal;
        case '2': return BrickType::Strong;
        case 'X': return BrickType::Unbreakable;
        default: return BrickType::Normal;
    }
}