#pragma once
#include "Controller.hpp"
#include "../../include/Utils/MessageBus.hpp"

class BrickTrackerController : public Controller {
public:
    BrickTrackerController();
    ~BrickTrackerController() override;
    
    void Initialize() override;
    
private:
    void HandleBrickDestroyed(const Message& message);
    void CheckWinCondition();
    int CountBreakableBricks();
}; 