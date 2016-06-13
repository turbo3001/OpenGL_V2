#include "UpdateObject.h"

UpdateObject::UpdateObject(float time_since_start, float deltaTime)
{
	this->time_since_start = time_since_start;
	this->deltaTime = deltaTime;
}

UpdateObject::~UpdateObject()
{
}

float UpdateObject::getTimeSinceStart()
{
	return time_since_start;
}

float UpdateObject::getDeltaTime()
{
	return deltaTime;
}

vector<Event> UpdateObject::getEvents()
{
	return m_events;
}

void UpdateObject::pushEvent(Event * newEvent)
{
	m_events.push_back(*newEvent);
}
