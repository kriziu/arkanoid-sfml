#pragma once
#include "MessageType.hpp"
#include <any>
#include <memory>

namespace arkanoid {

class Message {
public:
    Message(MessageType type, void* sender = nullptr, std::any payload = {})
        : m_type(type), m_sender(sender), m_payload(payload) {}

    MessageType getType() const { return m_type; }
    void* getSender() const { return m_sender; }
    std::any getPayload() const { return m_payload; }

private:
    MessageType m_type;
    void* m_sender;
    std::any m_payload;
};

} // namespace arkanoid 