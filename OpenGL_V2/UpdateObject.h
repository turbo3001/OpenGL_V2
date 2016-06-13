#pragma once

// External Includes
#include <vector>

// Internal Includes
#include "Event.h"

using namespace std;

// An Object to be passed through Update functions containing time data etc.

class UpdateObject
{
public:
	UpdateObject(float time_since_start, float deltaTime);
	~UpdateObject();

	float getTimeSinceStart();
	float getDeltaTime();

	vector<Event> getEvents();

	void pushEvent(Event* newEvent);

private:
	float time_since_start;
	float deltaTime;

	vector<Event> m_events;

};
