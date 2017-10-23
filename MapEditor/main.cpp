#include <crtdbg.h>
#include <CotEngine.h>
#include "MapEditor.h"

int WINAPI WinMain(HINSTANCE hInsetance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//		_CrtSetBreakAlloc(7526);
#pragma warning(disable : 4996)
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
#endif
	Cot::Application app;
	if (app.Init(hInsetance, "EditMap", RESOLUTION_X, RESOLUTION_Y, false))
	{
		app.RunWithScene(new MapEditor());
	}
	app.Destroy();

	return 0;
}