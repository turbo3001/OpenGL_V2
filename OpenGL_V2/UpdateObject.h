#pragma once

// An Object to be passed through Update functions containing time data etc.

class UpdateObject
{
public:
	UpdateObject(float time_since_start, float deltaTime);
	~UpdateObject();

	float getTimeSinceStart();
	float getDeltaTime();

private:
	float time_since_start;
	float deltaTime;

};
