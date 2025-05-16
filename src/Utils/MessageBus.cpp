#include "../../include/Utils/MessageBus.hpp"
#include <algorithm>

std::unordered_map<MessageType, std::vector<std::pair<void*, MessageBus::MessageHandler>>> MessageBus::subscribers_;

void MessageBus::Subscribe(MessageType type, void* subscriber, MessageHandler handler) {
    subscribers_[type].push_back(std::make_pair(subscriber, handler));
}

void MessageBus::Unsubscribe(MessageType type, void* subscriber) {
    auto& subscribers = subscribers_[type];
    subscribers.erase(
        std::remove_if(subscribers.begin(), subscribers.end(),
            [subscriber](const auto& pair) { return pair.first == subscriber; }),
        subscribers.end()
    );
}

void MessageBus::Publish(const Message& message) {
    if (subscribers_.find(message.type) == subscribers_.end()) {
        return;
    }
    
    for (const auto& [subscriber, handler] : subscribers_[message.type]) {
        handler(message);
    }
} 