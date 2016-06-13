#pragma once
#include <string>

using namespace std;

class Event
{
public:
	Event(string type);
	Event(char* type);

	Event(string type, void* data);
	Event(char* type, void* data);

	Event(string type, void* data, void* target);
	Event(char* type, void* data, void* target);

	~Event();

	string getEventType();

	void* eventTarget();

	void* data();


private:
	string m_eventType;
	void* m_data;
	void* m_target;

};