#pragma once

#include "Event.h"
#include <queue>

class EventManager
{
public:
    static void DispatchImmediate(Event& e);
    static void QueueEvent(Event* e); // takes ownership
    static void ProcessEventQueue();

private:
    static std::queue<Event*> s_EventQueue;
};
