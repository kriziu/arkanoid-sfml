#include "../../include/Controllers/LevelSelectorSceneController.hpp"
#include "../../include/Scenes/LevelSelectorScene.hpp"
#include "../../include/Utils/MessageBus.hpp"

LevelSelectorSceneController::LevelSelectorSceneController() : Controller() {}

LevelSelectorSceneController::~LevelSelectorSceneController() {
    MessageBus::Unsubscribe(MessageType::ShowLevelSelector, this);
}

void LevelSelectorSceneController::Initialize() {
    MessageBus::Subscribe(MessageType::ShowLevelSelector, this, 
        [this](const Message& msg) { HandleShowLevelSelector(msg); });
}

void LevelSelectorSceneController::HandleShowLevelSelector(const Message& message) {
    LevelSelectorScene* levelSelectorScene = GetScene<LevelSelectorScene>();
    levelSelectorScene->SetActive(true);
}

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
            
            if (levelSelectorScene->IsNextPageButtonClicked(mousePos) && levelSelectorScene->GetCurrentPage() < levelSelectorScene->GetTotalPages() - 1) {
                levelSelectorScene->SetCurrentPage(levelSelectorScene->GetCurrentPage() + 1);
            }
            
            if (levelSelectorScene->IsPrevPageButtonClicked(mousePos) && levelSelectorScene->GetCurrentPage() > 0) {
                levelSelectorScene->SetCurrentPage(levelSelectorScene->GetCurrentPage() - 1);
            }
        }
    }
}
