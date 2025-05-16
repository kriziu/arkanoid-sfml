#include "../../include/Actors/Paddle.hpp"

Paddle::Paddle() {
    sf::RectangleShape rectangle(sf::Vector2f(100, 20));
    rectangle.setFillColor(sf::Color::White);
}

Paddle::~Paddle() {}

void Paddle::Initialize() {
    shape_.setSize(sf::Vector2f(100, 20));
    shape_.setFillColor(sf::Color::White);
}

void Paddle::Draw(sf::RenderWindow& window) {
    window.draw(shape_);
}