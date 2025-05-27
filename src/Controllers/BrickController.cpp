#include "../../include/Controllers/BrickController.hpp"
#include "../../include/Actors/Brick.hpp"

BrickController::BrickController() : Controller() {}

BrickController::~BrickController() {}

void BrickController::Initialize() {
    Controller::Initialize();
}

void BrickController::Update(float deltaTime) {
    Controller::Update(deltaTime);
}

void BrickController::HandleEvent(const sf::Event& event) {
    Controller::HandleEvent(event);
}

bool BrickController::CheckCollision(const sf::FloatRect& other) {
    Brick* brick = GetBrick();
    if (!brick || brick->IsDestroyed()) {
        return false;
    }
    
    return brick->GetBounds().findIntersection(other).has_value();
}

void BrickController::OnHit(int damage) {
    Brick* brick = GetBrick();
    if (brick && !brick->IsDestroyed()) {
        brick->TakeDamage(damage);
    }
}

Brick* BrickController::GetBrick() {
    return dynamic_cast<Brick*>(actor_);
} 