

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

#include <Minigin.h>

#include "BurgerTime.h"

int main(int, char* []) {
	BurgerTime engine;
	engine.Run();
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
