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
    handler->AddEventSource(this);
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

void event::EventHandler::RemoveEventHandler(EventHandler* handler)
{
    eventHandlers_.erase(std::remove(eventHandlers_.begin(), eventHandlers_.end(), handler), eventHandlers_.end());
    handler->RemoveEventSource(this);
}

void event::EventHandler::RemoveEventSource(EventHandler* source)
{
  eventSources_.erase(std::remove(eventSources_.begin(), eventSources_.end(), source), eventSources_.end());
}