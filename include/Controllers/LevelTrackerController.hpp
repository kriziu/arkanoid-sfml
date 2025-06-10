#pragma once
#include "Controller.hpp"
#include "../../include/Utils/MessageBus.hpp"
#include <chrono>

class LevelTrackerController : public Controller {
public:
    LevelTrackerController();
    ~LevelTrackerController() override;
    
    void Initialize() override;
    
private:
    void HandleBrickDestroyed(const Message& message);
    void HandleBallLaunched(const Message& message);
    void CheckWinCondition();
    int CountBreakableBricks();
    
    std::chrono::steady_clock::time_point levelStartTime_;
    bool timingStarted_;
    float GetElapsedTime() const;
}; 