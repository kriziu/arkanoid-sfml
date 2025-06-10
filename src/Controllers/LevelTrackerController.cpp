#include "../../include/Controllers/LevelTrackerController.hpp"
#include "../../include/Actors/Brick.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Utils/SoundManager.hpp"

LevelTrackerController::LevelTrackerController() : Controller(), timingStarted_(false) {}

LevelTrackerController::~LevelTrackerController() {
    MessageBus::Unsubscribe(MessageType::BrickDestroyed, this);
    MessageBus::Unsubscribe(MessageType::BallLaunched, this);
}

void LevelTrackerController::Initialize() {
    timingStarted_ = false;
    MessageBus::Subscribe(MessageType::BrickDestroyed, this,
        [this](const Message& msg) { HandleBrickDestroyed(msg); });
    MessageBus::Subscribe(MessageType::BallLaunched, this,
        [this](const Message& msg) { HandleBallLaunched(msg); });
}

void LevelTrackerController::HandleBrickDestroyed(const Message& message) {
    CheckWinCondition();
}

void LevelTrackerController::HandleBallLaunched(const Message& message) {
    if (!timingStarted_) {
        levelStartTime_ = std::chrono::steady_clock::now();
        timingStarted_ = true;
    }
}

void LevelTrackerController::CheckWinCondition() {
    int remainingBreakableBricks = CountBreakableBricks();
    
    if (remainingBreakableBricks == 0) {
        SoundManager::PlaySound("win");
        
        float elapsedTime = timingStarted_ ? GetElapsedTime() : 0.0f;
        
        Message levelCompleteMessage;
        levelCompleteMessage.type = MessageType::LevelComplete;
        levelCompleteMessage.sender = this;
        levelCompleteMessage.payload = elapsedTime;
        MessageBus::Publish(levelCompleteMessage);
    }
}

int LevelTrackerController::CountBreakableBricks() {
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

float LevelTrackerController::GetElapsedTime() const {
    if (!timingStarted_) return 0.0f;
    
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - levelStartTime_);
    return duration.count() / 1000.0f;
}