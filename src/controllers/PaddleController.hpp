#pragma once
#include "../core/Controller.hpp"

namespace arkanoid {

class Paddle;

class PaddleController : public Controller {
public:
    PaddleController();
    ~PaddleController() override = default;
    
    void update(float dt) override;
    void onAttach() override;

private:
    Paddle* m_paddle;
};

} // namespace arkanoid 