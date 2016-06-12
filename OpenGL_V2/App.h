#pragma once
// External Includes
// Chrono (Used for time related purposes)
#include <chrono>
// Internal Includes
#include "Constants.h"
#include "Globals.h"
#include "Context.h"

class  App
{
public:
	 App();
	~ App();

	void start();
	void init();
	void update(UpdateObject update);
	void draw();
	void cleanUp();

private:
	void startLoop();

	std::chrono::time_point<std::chrono::steady_clock> t_start;

	Context m_SDLContext;
};