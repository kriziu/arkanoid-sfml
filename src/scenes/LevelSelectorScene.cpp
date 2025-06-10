#include "../../include/Scenes/LevelSelectorScene.hpp"
#include "../../include/Utils/Constants.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>

LevelSelectorScene::LevelSelectorScene() : currentPage_(0), totalPages_(0),
    titleText_(sf::Text(font_)), pageText_(sf::Text(font_)), 
    nextPageText_(sf::Text(font_)), prevPageText_(sf::Text(font_)),
    creditsText_(sf::Text(font_)) {}

LevelSelectorScene::~LevelSelectorScene() {}

void LevelSelectorScene::Initialize() {
    Scene::Initialize();
    LoadLevelFiles();
    SetupUI();
    UpdatePageDisplay();
}

std::vector<LevelInfo> LevelSelectorScene::GetLevels() const {
    return levels_;
}

int LevelSelectorScene::GetCurrentPage() const {
    return currentPage_;
}

int LevelSelectorScene::GetTotalPages() const {
    return totalPages_;
}

void LevelSelectorScene::SetCurrentPage(int page) {
    currentPage_ = page;
    UpdatePageDisplay();
}

void LevelSelectorScene::LoadLevelFiles() {
    levels_.clear();
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator("levels")) {
            if (entry.path().extension() == ".level") {
                LevelInfo levelInfo;
                levelInfo.filename = entry.path().string();
                levelInfo.displayName = entry.path().stem().string();
                
                if (LevelLoader::LoadLevel(levelInfo.filename, levelInfo.levelData)) {
                    levels_.push_back(levelInfo);
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error loading level files: " << e.what() << std::endl;
    }
    
    std::sort(levels_.begin(), levels_.end(), 
        [](const LevelInfo& a, const LevelInfo& b) {
            int numA = std::stoi(a.displayName.substr(a.displayName.find(' ') + 1));
            int numB = std::stoi(b.displayName.substr(b.displayName.find(' ') + 1));
            return numA < numB;
        });
    
    totalPages_ = (levels_.size() + GetLevelsPerPage() - 1) / GetLevelsPerPage();
}

void LevelSelectorScene::SetupUI() {
    if (!font_.openFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    
    titleText_.setFont(font_);
    titleText_.setString("SELECT LEVEL");
    titleText_.setCharacterSize(48);
    titleText_.setFillColor(sf::Color::White);
    
    sf::FloatRect titleBounds = titleText_.getLocalBounds();
    titleText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - titleBounds.size.x) / 2,
        50
    ));
    
    pageText_.setFont(font_);
    pageText_.setCharacterSize(24);
    pageText_.setFillColor(sf::Color::White);
    
    nextPageButton_.setSize(sf::Vector2f(100, 40));
    nextPageButton_.setFillColor(sf::Color(70, 130, 180));
    nextPageButton_.setPosition(sf::Vector2f(
        Constants::WINDOW_WIDTH - 120,
        Constants::WINDOW_HEIGHT - 60
    ));
    
    prevPageButton_.setSize(sf::Vector2f(100, 40));
    prevPageButton_.setFillColor(sf::Color(70, 130, 180));
    prevPageButton_.setPosition(sf::Vector2f(
        20,
        Constants::WINDOW_HEIGHT - 60
    ));
    
    nextPageText_.setFont(font_);
    nextPageText_.setString("NEXT");
    nextPageText_.setCharacterSize(18);
    nextPageText_.setFillColor(sf::Color::White);
    
    prevPageText_.setFont(font_);
    prevPageText_.setString("PREV");
    prevPageText_.setCharacterSize(18);
    prevPageText_.setFillColor(sf::Color::White);
    
    sf::FloatRect nextBounds = nextPageText_.getLocalBounds();
    sf::Vector2f nextButtonPos = nextPageButton_.getPosition();
    sf::Vector2f nextButtonSize = nextPageButton_.getSize();
    nextPageText_.setPosition(sf::Vector2f(
        nextButtonPos.x + (nextButtonSize.x - nextBounds.size.x) / 2 - nextBounds.position.x,
        nextButtonPos.y + (nextButtonSize.y - nextBounds.size.y) / 2 - nextBounds.position.y
    ));
    
    sf::FloatRect prevBounds = prevPageText_.getLocalBounds();
    sf::Vector2f prevButtonPos = prevPageButton_.getPosition();
    sf::Vector2f prevButtonSize = prevPageButton_.getSize();
    prevPageText_.setPosition(sf::Vector2f(
        prevButtonPos.x + (prevButtonSize.x - prevBounds.size.x) / 2 - prevBounds.position.x,
        prevButtonPos.y + (prevButtonSize.y - prevBounds.size.y) / 2 - prevBounds.position.y
    ));
    
    creditsText_.setFont(font_);
    creditsText_.setString("Created by Kacper Wojak and Bruno Dziecielski");
    creditsText_.setCharacterSize(12);
    creditsText_.setFillColor(sf::Color(200, 200, 200));
    
    sf::FloatRect creditsBounds = creditsText_.getLocalBounds();
    creditsText_.setPosition(sf::Vector2f(
        8,
        Constants::WINDOW_HEIGHT - creditsBounds.size.y - 8
    ));
}

void LevelSelectorScene::UpdatePageDisplay() {
    std::string pageStr = "Page " + std::to_string(currentPage_ + 1) + " / " + std::to_string(totalPages_);
    pageText_.setString(pageStr);
    
    sf::FloatRect pageBounds = pageText_.getLocalBounds();
    pageText_.setPosition(sf::Vector2f(
        (Constants::WINDOW_WIDTH - pageBounds.size.x) / 2,
        Constants::WINDOW_HEIGHT - 55
    ));
}

int LevelSelectorScene::GetLevelsPerPage() const {
    return GRID_COLS * GRID_ROWS;
}

void LevelSelectorScene::Draw(sf::RenderWindow& window) {
    window.draw(titleText_);
    window.draw(pageText_);
    
    if (currentPage_ > 0) {
        window.draw(prevPageButton_);
        window.draw(prevPageText_);
    }
    
    if (currentPage_ < totalPages_ - 1) {
        window.draw(nextPageButton_);
        window.draw(nextPageText_);
    }
    
    int startIndex = currentPage_ * GetLevelsPerPage();
    int endIndex = std::min(startIndex + GetLevelsPerPage(), static_cast<int>(levels_.size()));
    
    float startX = (Constants::WINDOW_WIDTH - (GRID_COLS * TILE_SIZE + (GRID_COLS - 1) * TILE_SPACING)) / 2;
    float startY = 150;
    
    for (int i = startIndex; i < endIndex; i++) {
        int gridIndex = i - startIndex;
        int col = gridIndex % GRID_COLS;
        int row = gridIndex / GRID_COLS;
        
        float x = startX + col * (TILE_SIZE + TILE_SPACING);
        float y = startY + row * (TILE_SIZE + TILE_SPACING);
        
        sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        tile.setPosition(sf::Vector2f(x, y));
        tile.setFillColor(sf::Color(50, 50, 50));
        tile.setOutlineThickness(2);
        tile.setOutlineColor(sf::Color::White);
        
        window.draw(tile);
        
        sf::Text levelNameText(font_);
        levelNameText.setFont(font_);
        levelNameText.setString(levels_[i].displayName);
        levelNameText.setCharacterSize(24);
        levelNameText.setFillColor(sf::Color::White);
        
        sf::FloatRect textBounds = levelNameText.getLocalBounds();
        levelNameText.setPosition(sf::Vector2f(
            x + (TILE_SIZE - textBounds.size.x) / 2 - textBounds.position.x,
            y + (TILE_SIZE - textBounds.size.y) / 2 - textBounds.position.y
        ));
        
        window.draw(levelNameText);
        
        sf::Text brickCountText(font_);
        brickCountText.setFont(font_);
        brickCountText.setString(std::to_string(levels_[i].levelData.bricks.size()) + " bricks");
        brickCountText.setCharacterSize(14);
        brickCountText.setFillColor(sf::Color(200, 200, 200));
        
        sf::FloatRect brickCountBounds = brickCountText.getLocalBounds();
        brickCountText.setPosition(sf::Vector2f(
            x + (TILE_SIZE - brickCountBounds.size.x) / 2 - brickCountBounds.position.x,
            y + TILE_SIZE - 30
        ));
        
        window.draw(brickCountText);
    }
    
    window.draw(creditsText_);
    
    Scene::Draw(window);
}

bool LevelSelectorScene::IsLevelTileClicked(const sf::Vector2f& mousePos, int& selectedLevel) const {
    int startIndex = currentPage_ * GetLevelsPerPage();
    int endIndex = std::min(startIndex + GetLevelsPerPage(), static_cast<int>(levels_.size()));
    
    float startX = (Constants::WINDOW_WIDTH - (GRID_COLS * TILE_SIZE + (GRID_COLS - 1) * TILE_SPACING)) / 2;
    float startY = 150;
    
    for (int i = startIndex; i < endIndex; i++) {
        int gridIndex = i - startIndex;
        int col = gridIndex % GRID_COLS;
        int row = gridIndex / GRID_COLS;
        
        float x = startX + col * (TILE_SIZE + TILE_SPACING);
        float y = startY + row * (TILE_SIZE + TILE_SPACING);
        
        sf::FloatRect tileRect(sf::Vector2f(x, y), sf::Vector2f(TILE_SIZE, TILE_SIZE));
        if (tileRect.contains(mousePos)) {
            selectedLevel = i;
            return true;
        }
    }
    
    return false;
}

bool LevelSelectorScene::IsNextPageButtonClicked(const sf::Vector2f& mousePos) const {
    if (currentPage_ >= totalPages_ - 1) return false;
    return nextPageButton_.getGlobalBounds().contains(mousePos);
}

bool LevelSelectorScene::IsPrevPageButtonClicked(const sf::Vector2f& mousePos) const {
    if (currentPage_ <= 0) return false;
    return prevPageButton_.getGlobalBounds().contains(mousePos);
}
