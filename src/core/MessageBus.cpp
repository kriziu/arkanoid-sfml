#include "MessageBus.hpp"

namespace arkanoid {

MessageBus& MessageBus::getInstance() {
    static MessageBus instance;
    return instance;
}

MessageBus::HandlerId MessageBus::subscribe(MessageType type, MessageHandler handler) {
    HandlerId id = m_nextHandlerId++;
    m_handlers[type][id] = handler;
    return id;
}

void MessageBus::unsubscribe(MessageType type, HandlerId id) {
    if (m_handlers.count(type)) {
        m_handlers[type].erase(id);
    }
}

void MessageBus::publish(const Message& message) {
    MessageType type = message.getType();
    if (m_handlers.count(type)) {
        for (const auto& [id, handler] : m_handlers[type]) {
            handler(message);
        }
    }
}

} // namespace arkanoid 