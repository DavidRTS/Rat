#pragma once
#include "Event.h"
#include <sstream>

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height) {
    }

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << "x" << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)

        Event* Clone() const override { return new WindowResizeEvent(*this); }

private:
    unsigned int m_Width, m_Height;
};

class WindowMoveEvent : public Event
{
public:
    WindowMoveEvent(int x, int y)
        : m_X(x), m_Y(y) {
    }

    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowMoveEvent: (" << m_X << ", " << m_Y << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)

        Event* Clone() const override { return new WindowMoveEvent(*this); }

private:
    int m_X, m_Y;
};

class WindowFocusEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
        Event* Clone() const override { return new WindowFocusEvent(*this); }
};

class WindowLostFocusEvent : public Event
{
public:
    EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryWindow)
        Event* Clone() const override { return new WindowLostFocusEvent(*this); }
};
