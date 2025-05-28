#include "../../include/Controllers/BrickController.hpp"
#include "../../include/Actors/Brick.hpp"

BrickController::BrickController() : Controller() {}

BrickController::~BrickController() {}

bool BrickController::CheckCollision(const sf::FloatRect& other) {
    Brick* brick = GetActor<Brick>();
    if (!brick || brick->IsDestroyed()) {
        return false;
    }
    
    return brick->GetBounds().findIntersection(other).has_value();
}

void BrickController::OnHit(int damage) {
    Brick* brick = GetActor<Brick>();
    if (brick && !brick->IsDestroyed()) {
        brick->TakeDamage(damage);
    }
}