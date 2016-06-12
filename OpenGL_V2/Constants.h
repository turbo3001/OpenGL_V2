#pragma once

static const int MAIN_RETURN = -3; // The code should never return from main dirctly if it does something has gone a little wrong!
static const int PROGRAM_RUNNING = -2; // This keeps the Game loop runnning
static const int PROGRAM_START = -1; // This is the default value for ExitCode
static const int NORMAL_EXIT = 0; // Regular Exit from the Program
static const int VERTEX_SHADER_COMPILE_ERROR = 1; // Vertex Shader has compiled incorrectly.
static const int FRAGMENT_SHADER_COMPILE_ERROR = 2; // Fragment Shader has compiled incorrectly.
