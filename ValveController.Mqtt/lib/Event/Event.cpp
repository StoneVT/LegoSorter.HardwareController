#include "Event.h"

#include <Arduino.h>

#include <algorithm>


event::EventHandler::~EventHandler()
{
    for (auto& eventSource : eventSources_)
    {
        eventSource->RemoveEventHandler(this);
    }
}

void event::EventHandler::AddEventHandler(EventHandler* handler) 
{
    eventHandlers_.push_back(handler);
}

void event::EventHandler::AddEventSource(EventHandler* source)
{
    eventSources_.push_back(source);
}

void event::EventHandler::HandleEvent(Event* e)
{
    Serial.println("I am handling the event!");
}


void event::EventHandler::Notify() 
{
    for (auto& eventHandler : eventHandlers_)
    {
        Event e;
        eventHandler->HandleEvent(&e);
    }
}

void event::EventHandler::RemoveEventHandler(EventHandler* source) 
{
    eventHandlers_.erase(std::remove(eventHandlers_.begin(), eventHandlers_.end(), source), eventHandlers_.end()); 
}