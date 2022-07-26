//#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <thread>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#pragma warning(disable:26495)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#define USE_SDLMIXER2

//#define USE_STEAMAPI