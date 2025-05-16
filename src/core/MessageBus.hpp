#pragma once
#include "Message.hpp"
#include <functional>
#include <map>
#include <vector>

namespace arkanoid {

class MessageBus {
public:
    using MessageHandler = std::function<void(const Message&)>;
    using HandlerId = unsigned int;

    static MessageBus& getInstance();
    HandlerId subscribe(MessageType type, MessageHandler handler);
    void unsubscribe(MessageType type, HandlerId id);
    void publish(const Message& message);

private:
    MessageBus() = default;
    MessageBus(const MessageBus&) = delete;
    MessageBus& operator=(const MessageBus&) = delete;
    
    std::map<MessageType, std::map<HandlerId, MessageHandler>> m_handlers;
    HandlerId m_nextHandlerId = 0;
};

} // namespace arkanoid 