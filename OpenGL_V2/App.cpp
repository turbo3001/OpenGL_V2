#include "App.h"

App::App()
{
	m_SDLContext = Context();
}

App::~App()
{
}

void App::start()
{
	t_start = std::chrono::high_resolution_clock::now();
	init();
	startLoop();
}

void App::init()
{
	m_SDLContext.init();
}

void App::handleInput(UpdateObject forUpdate)
{
	m_SDLContext.handleInput(forUpdate);
}

void App::update(UpdateObject update)
{
	m_SDLContext.update(update);
}

void App::draw()
{
	m_SDLContext.draw();
}

void App::cleanUp()
{
	m_SDLContext.cleanUp();
}

void App::startLoop()
{
	float previousTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - t_start).count();

	if (ExitCode == PROGRAM_START)
	{
		ExitCode = PROGRAM_RUNNING;
	}

	while (ExitCode == PROGRAM_RUNNING)
	{

		// Calculate deltaTime
		auto t_frame = std::chrono::high_resolution_clock::now();
		float time_since_start = std::chrono::duration_cast<std::chrono::duration<float>>(t_frame - t_start).count();
		float deltaTime = time_since_start - previousTime;
		previousTime = time_since_start;

		UpdateObject updateObject = UpdateObject(time_since_start, deltaTime);
		handleInput(updateObject);
		update(updateObject);

		draw();

	}

	cleanUp();
}
