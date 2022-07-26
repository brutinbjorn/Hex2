#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(disable:26819)

#include "SDL.h"
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable:4996)
#include <steam_api.h>
//#include "steam_api.h"
#pragma warning(pop)

#include "Minigin.h"


int main(int, char*[])
{
#ifdef USE_STEAMAPI
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
	}
#endif

	dae::Minigin engine;
	engine.Run();
    return 0;
}