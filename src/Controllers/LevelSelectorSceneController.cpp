#include "../../include/Controllers/LevelSelectorSceneController.hpp"
#include "../../include/Scenes/LevelSelectorScene.hpp"
#include "../../include/Utils/MessageBus.hpp"

LevelSelectorSceneController::LevelSelectorSceneController() : Controller() {}

LevelSelectorSceneController::~LevelSelectorSceneController() {}

void LevelSelectorSceneController::Initialize() {}

void LevelSelectorSceneController::HandleEvent(const sf::Event& event) {
    LevelSelectorScene* levelSelectorScene = GetScene<LevelSelectorScene>();

    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                                static_cast<float>(mouseButtonPressed->position.y));
            
            int selectedLevel;
            if (levelSelectorScene->IsLevelTileClicked(mousePos, selectedLevel)) {
                Message message;
                message.type = MessageType::LevelSelected;
                message.sender = this;
                message.payload = levelSelectorScene->GetLevels()[selectedLevel].filename;
                MessageBus::Publish(message);

                levelSelectorScene->SetActive(false);
            }
            
            // if (levelSelectorScene->IsNextPageButtonClicked(mousePos) && levelSelectorScene->currentPage_ < levelSelectorScene->totalPages_ - 1) {
            //     levelSelectorScene->currentPage_++;
            //     levelSelectorScene->UpdatePageDisplay();
            // }
            
            // if (levelSelectorScene->IsPrevPageButtonClicked(mousePos) && levelSelectorScene->currentPage_ > 0) {
            //     levelSelectorScene->currentPage_--;
            //     levelSelectorScene->UpdatePageDisplay();
            // }
        }
    }
}

void LevelSelectorSceneController::HandleLevelSelected(const std::string& levelFile) {
    Message message;
    message.type = MessageType::LevelSelected;
    message.sender = this;
    message.payload = levelFile;
    MessageBus::Publish(message);
} 