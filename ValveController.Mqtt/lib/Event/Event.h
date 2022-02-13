#ifndef Event_h
#define Event_h

#include <vector>

namespace event {

    enum class Type {
        base,
        pressureCritical
    };

    class Event 
    {
        public:
            Event(Type type = Type::base) : type_(type){}
            void SetType(Type type) { type_ = type;}
            Type GetType() {return type_;}
        protected:
            Type type_{Type::base};
    };

    class PressureCriticalEvent : public Event {
    public:
        PressureCriticalEvent() = delete;
        PressureCriticalEvent(float threshold, float pressure_bar) : Event(Type::pressureCritical), threshold_(threshold), pressure_bar_(pressure_bar) {}

        float Threshold() const { return threshold_; }
        float Pressure_bar() const { return pressure_bar_; }

    private:
        const float threshold_;
        const float pressure_bar_;
    };
    
    class EventHandler {
        public:
            EventHandler() = default;
            ~EventHandler();
            
            void AddEventHandler(EventHandler* handler);
            void RemoveEventHandler(EventHandler* handler);

            void AddEventSource(EventHandler* source);
            
            virtual void HandleEvent(Event* e);

        protected:
            virtual void Notify();

        protected:
            std::vector<EventHandler*> eventHandlers_;
            std::vector<EventHandler*> eventSources_;
    };
}

#endif