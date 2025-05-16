#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <any>

enum class MessageType {
    BrickDestroyed,
    BallLost,
    LifeLost,
    GameOver,
    LevelComplete
};

struct Message {
    MessageType type;
    void* sender;
    std::any payload;
};

class MessageBus {
public:
    using MessageHandler = std::function<void(const Message&)>;
    
    static void Subscribe(MessageType type, void* subscriber, MessageHandler handler);
    static void Unsubscribe(MessageType type, void* subscriber);
    static void Publish(const Message& message);
    
private:
    static std::unordered_map<MessageType, std::vector<std::pair<void*, MessageHandler>>> subscribers_;
}; 