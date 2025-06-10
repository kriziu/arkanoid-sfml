#include "../../include/Controllers/LevelTrackerController.hpp"
#include "../../include/Actors/Brick.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Utils/SoundManager.hpp"

LevelTrackerController::LevelTrackerController() : Controller(), timingStarted_(false), isPaused_(false), totalPausedTime_(0) {}

LevelTrackerController::~LevelTrackerController() {
    MessageBus::Unsubscribe(MessageType::BrickDestroyed, this);
    MessageBus::Unsubscribe(MessageType::BallLaunched, this);
    MessageBus::Unsubscribe(MessageType::GamePaused, this);
    MessageBus::Unsubscribe(MessageType::GameResumed, this);
}

void LevelTrackerController::Initialize() {
    timingStarted_ = false;
    isPaused_ = false;
    totalPausedTime_ = std::chrono::duration<float>(0);
    MessageBus::Subscribe(MessageType::BrickDestroyed, this,
        [this](const Message& msg) { HandleBrickDestroyed(msg); });
    MessageBus::Subscribe(MessageType::BallLaunched, this,
        [this](const Message& msg) { HandleBallLaunched(msg); });
    MessageBus::Subscribe(MessageType::GamePaused, this,
        [this](const Message& msg) { HandleGamePaused(msg); });
    MessageBus::Subscribe(MessageType::GameResumed, this,
        [this](const Message& msg) { HandleGameResumed(msg); });
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

void LevelTrackerController::HandleGamePaused(const Message& message) {
    if (timingStarted_ && !isPaused_) {
        pauseStartTime_ = std::chrono::steady_clock::now();
        isPaused_ = true;
    }
}

void LevelTrackerController::HandleGameResumed(const Message& message) {
    if (timingStarted_ && isPaused_) {
        auto pauseDuration = std::chrono::steady_clock::now() - pauseStartTime_;
        totalPausedTime_ += pauseDuration;
        isPaused_ = false;
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
    auto totalDuration = currentTime - levelStartTime_;
    
    auto pausedTime = totalPausedTime_;
    if (isPaused_) {
        auto currentPauseDuration = currentTime - pauseStartTime_;
        pausedTime += currentPauseDuration;
    }
    
    auto playTime = totalDuration - pausedTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(playTime).count() / 1000.0f;
}