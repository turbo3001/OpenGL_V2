#include "Event.h"

Event::Event(char * type) : Event(string(type))
{
}

Event::Event(string type) : Event(type, nullptr)
{
}

Event::Event(char * type, void * data) : Event(string(type), data)
{
}

Event::Event(string type, void * data) : Event(type, data, nullptr)
{
}

Event::Event(char * type, void * data, void * target) : Event(string(type), data, target)
{
}

Event::Event(string type, void * data, void * target)
{
	this->m_eventType = type;
	this->m_data = data;
	this->m_target = target;

}

Event::~Event()
{
}

string Event::getEventType()
{
	return m_eventType;
}

void * Event::eventTarget()
{
	return m_target;
}

void * Event::data()
{
	return m_data;
}
