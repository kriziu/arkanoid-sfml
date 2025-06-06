#include "../../include/Utils/LevelLoader.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Controllers/BrickController.hpp"
#include "../../include/Utils/Constants.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

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
    
    std::istringstream headerStream(line);
    if (!(headerStream >> levelData.width >> levelData.height >> levelData.spacing >> levelData.padding.x >> levelData.padding.y)) {
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
    sf::Vector2f brickSize = GetBrickSize(levelData);
    
    for (const auto& brickData : levelData.bricks) {
        Brick* brick = new Brick(brickData.type);
        sf::Vector2f worldPos = GridToWorldPosition(brickData.position, levelData);
        
        brick->SetPosition(worldPos);
        brick->SetSize(brickSize);
        brick->AddController(new BrickController());
        
        scene->AddActor(brick);
    }
    
    return true;
}

sf::Vector2f LevelLoader::GridToWorldPosition(const GridPosition& gridPos, const LevelData& levelData) {
    sf::Vector2f brickSize = GetBrickSize(levelData);
    float x = levelData.padding.x + gridPos.x * (brickSize.x + levelData.spacing);
    float y = levelData.padding.y + gridPos.y * (brickSize.y + levelData.spacing);
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

sf::Vector2f LevelLoader::GetBrickSize(const LevelData& levelData) {
    float availableWidth = Constants::WINDOW_WIDTH - (2 * levelData.padding.x);
    float totalSpacing = (levelData.width - 1) * levelData.spacing;
    float brickWidth = (availableWidth - totalSpacing) / levelData.width;
    
    float playAreaHeight = (2.0f / 3.0f) * Constants::WINDOW_HEIGHT;
    float availableHeight = playAreaHeight - (2 * levelData.padding.y);
    float totalVerticalSpacing = (levelData.height - 1) * levelData.spacing;
    float brickHeight = (availableHeight - totalVerticalSpacing) / levelData.height;
    
    return sf::Vector2f(brickWidth, brickHeight);
}