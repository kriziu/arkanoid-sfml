#include "GameplayScene.hpp"
#include "../actors/Ball.hpp"
#include "../actors/Paddle.hpp"
#include "../actors/Brick.hpp"
#include "../controllers/BallController.hpp"
#include "../controllers/PaddleController.hpp"
#include "../core/MessageBus.hpp"
#include <memory>

namespace arkanoid {

GameplayScene::GameplayScene()
    : Scene("GameplayScene"), m_lives(3), m_score(0) {
}

void GameplayScene::init() {
    // Create paddle
    auto paddle = std::make_shared<Paddle>(this);
    paddle->setPosition(350.f, 550.f);
    addActor(paddle);
    
    // Add controller to paddle
    auto paddleController = std::make_shared<PaddleController>();
    paddle->addController(paddleController);
    
    // Create ball
    resetBall();
    
    // Create level layout
    createLevel();
    
    // Subscribe to messages
    auto messageBus = &MessageBus::getInstance();
    messageBus->subscribe(MessageType::BallLost, [this](const Message& message) {
        m_lives--;
        
        if (m_lives <= 0) {
            // Game over
            MessageBus::getInstance().publish(Message(MessageType::GameOver));
        } else {
            resetBall();
        }
    });
    
    messageBus->subscribe(MessageType::BrickDestroyed, [this](const Message& message) {
        m_score += 100;
        
        // Check if level is completed
        bool levelCompleted = true;
        for (const auto& actor : m_actors) {
            if (dynamic_cast<Brick*>(actor.get()) && 
                !dynamic_cast<Brick*>(actor.get())->isDestroyed()) {
                levelCompleted = false;
                break;
            }
        }
        
        if (levelCompleted) {
            MessageBus::getInstance().publish(Message(MessageType::LevelComplete));
        }
    });
}

void GameplayScene::update(float dt) {
    // Call parent update to update all actors and controllers
    Scene::update(dt);
}

void GameplayScene::render(sf::RenderWindow& window) {
    // Call parent render to render all actors
    Scene::render(window);
    
    // Render UI elements (score, lives, etc.)
    // This would be implemented with proper UI components in a full game
}

void GameplayScene::resetBall() {
    // Remove existing ball if any
    removeActor("Ball");
    
    // Create a new ball
    auto ball = std::make_shared<Ball>(this);
    ball->setPosition(400.f, 500.f);
    ball->setVelocity(sf::Vector2f(200.f, -200.f)); // Initial velocity
    addActor(ball);
    
    // Add controller to ball
    auto ballController = std::make_shared<BallController>();
    ball->addController(ballController);
}

void GameplayScene::createLevel() {
    // Clear existing bricks
    for (auto it = m_actors.begin(); it != m_actors.end();) {
        if (dynamic_cast<Brick*>(it->get())) {
            it = m_actors.erase(it);
        } else {
            ++it;
        }
    }
    
    // Create a simple grid of bricks
    const int rows = 5;
    const int cols = 10;
    const float brickWidth = 70.f;
    const float brickHeight = 30.f;
    const float startX = 65.f;
    const float startY = 50.f;
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            auto brick = std::make_shared<Brick>(
                this, 
                row == 0 ? BrickType::Hard :
                (row == rows - 1 && col == cols / 2) ? BrickType::Unbreakable :
                BrickType::Regular
            );
            
            brick->setSize(brickWidth, brickHeight);
            brick->setPosition(
                startX + col * (brickWidth + 10.f),
                startY + row * (brickHeight + 10.f)
            );
            
            // Give each brick a unique name
            std::string name = "Brick_" + std::to_string(row) + "_" + std::to_string(col);
            
            addActor(brick);
        }
    }
}

} // namespace arkanoid 