#pragma once
#include <string>
#include <vector>
#include "../Actors/Brick.hpp"

class Scene;

struct GridPosition {
    int x, y;
};

struct BrickData {
    GridPosition position;
    BrickType type;
};

struct LevelData {
    int width;
    int height;
    float spacing;
    sf::Vector2f padding;
    std::vector<BrickData> bricks;
};

class LevelLoader {
public:
    static bool LoadLevel(const std::string& filename, LevelData& levelData);
    static bool LoadBricksIntoScene(const LevelData& levelData, Scene* scene);
    
private:
    static sf::Vector2f GridToWorldPosition(const GridPosition& gridPos, const LevelData& levelData);
    static BrickType GetBrickType(char brickChar);
    static sf::Vector2f GetBrickSize(const LevelData& levelData);
}; 