#pragma once
#include "Event.h"
#include <sstream>

class KeyEvent : public Event
{
public:
    int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), m_RepeatCount(repeatCount) {
    }

    inline int GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        Event* Clone() const override { return new KeyPressedEvent(*this); }

private:
    int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keycode)
        : KeyEvent(keycode) {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
        Event* Clone() const override { return new KeyReleasedEvent(*this); }
};

class KeyHoldEvent : public KeyEvent
{
public:
    KeyHoldEvent(int keycode)
        : KeyEvent(keycode) {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyHoldEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyHold)
        Event* Clone() const override { return new KeyHoldEvent(*this); }
};