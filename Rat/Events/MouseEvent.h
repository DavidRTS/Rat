#pragma once
#include "Event.h"
#include <sstream>

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_MouseX(x), m_MouseY(y) {
    }

    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: (" << m_MouseX << ", " << m_MouseY << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        Event* Clone() const override { return new MouseMovedEvent(*this); }

private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {
    }

    float GetXOffset() const { return m_XOffset; }
    float GetYOffset() const { return m_YOffset; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: (" << m_XOffset << ", " << m_YOffset << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

        Event* Clone() const override { return new MouseScrolledEvent(*this); }

private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
public:
    int GetMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

protected:
    MouseButtonEvent(int button)
        : m_Button(button) {
    }

    int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button) {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
        Event* Clone() const override { return new MouseButtonPressedEvent(*this); }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button) {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
        Event* Clone() const override { return new MouseButtonReleasedEvent(*this); }
};

class MouseButtonHoldEvent : public MouseButtonEvent
{
public:
    MouseButtonHoldEvent(int button)
        : MouseButtonEvent(button) {
    }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonHoldEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseHold)
        Event* Clone() const override { return new MouseButtonHoldEvent(*this); }
};
