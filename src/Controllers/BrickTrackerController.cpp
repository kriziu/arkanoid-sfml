#include "../../include/Controllers/BrickTrackerController.hpp"
#include "../../include/Actors/Brick.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Utils/SoundManager.hpp"

BrickTrackerController::BrickTrackerController() : Controller() {}

BrickTrackerController::~BrickTrackerController() {
    MessageBus::Unsubscribe(MessageType::BrickDestroyed, this);
}

void BrickTrackerController::Initialize() {
    MessageBus::Subscribe(MessageType::BrickDestroyed, this,
        [this](const Message& msg) { HandleBrickDestroyed(msg); });
}

void BrickTrackerController::HandleBrickDestroyed(const Message& message) {
    CheckWinCondition();
}

void BrickTrackerController::CheckWinCondition() {
    int remainingBreakableBricks = CountBreakableBricks();
    
    if (remainingBreakableBricks == 0) {
        SoundManager::PlaySound("win");
        
        Message levelCompleteMessage;
        levelCompleteMessage.type = MessageType::LevelComplete;
        levelCompleteMessage.sender = this;
        MessageBus::Publish(levelCompleteMessage);
    }
}

int BrickTrackerController::CountBreakableBricks() {
    if (!scene_) return 0;
    
    int count = 0;
    auto& actors = scene_->GetActors();
    
    for (Actor* actor : actors) {
        Brick* brick = dynamic_cast<Brick*>(actor);
        if (brick && !brick->IsDestroyed() && brick->GetType() != BrickType::Unbreakable) {
            count++;
        }
    }
    
    return count;
} 