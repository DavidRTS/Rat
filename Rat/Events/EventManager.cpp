#include <RTHeader.h>
#include "EventManager.h"

std::queue<Event*> EventManager::s_EventQueue;

void EventManager::DispatchImmediate(Event& e)
{
    // Process event immediately (you can expand this)
    // Example: logging or callbacks
}

void EventManager::QueueEvent(Event* e)
{
    s_EventQueue.push(e);
}

void EventManager::ProcessEventQueue()
{
    while (!s_EventQueue.empty())
    {
        Event* e = s_EventQueue.front();
        s_EventQueue.pop();

        DispatchImmediate(*e); // or some real handler

        delete e; // Clean up
    }
}
