#pragma once
#include "Scene.hpp"
#include "../Utils/LevelLoader.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct LevelInfo {
    std::string filename;
    std::string displayName;
    LevelData levelData;
};

class LevelSelectorScene : public Scene {
public:
    LevelSelectorScene();
    ~LevelSelectorScene() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;

    std::vector<LevelInfo> GetLevels() const;
    int GetCurrentPage() const;
    int GetTotalPages() const;
    void SetCurrentPage(int page);

    bool IsLevelTileClicked(const sf::Vector2f& mousePos, int& selectedLevel) const;
    bool IsNextPageButtonClicked(const sf::Vector2f& mousePos) const;
    bool IsPrevPageButtonClicked(const sf::Vector2f& mousePos) const;

private:
    void LoadLevelFiles();
    void SetupUI();
    void UpdatePageDisplay();
    int GetLevelsPerPage() const;
    
    std::vector<LevelInfo> levels_;
    sf::Font font_;
    sf::Text titleText_;
    sf::Text pageText_;
    
    sf::RectangleShape nextPageButton_;
    sf::RectangleShape prevPageButton_;
    sf::Text nextPageText_;
    sf::Text prevPageText_;
    sf::Text creditsText_;
    
    static const int GRID_COLS = 3;
    static const int GRID_ROWS = 2;
    static constexpr float TILE_SIZE = 150.0f;
    static constexpr float TILE_SPACING = 20.0f;
    
    int currentPage_;
    int totalPages_;
}; 