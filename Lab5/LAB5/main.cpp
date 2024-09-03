/**
 * ============================================================================
 *  Name        : main.cpp
 *  Part of     : Simple OpenGL graphics engine framework
 *  Description : entry point for a superduper game app
 *  Version     : 1.00
 *	Author		: Jani Immonen, <realdashdev@gmail.com>
 * ============================================================================
**/


#include "TheApp.h"

#if defined (_WINDOWS)
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int nCmdShow)
#endif
#if defined (_LINUX)
int main(int argc, char** argv)
#endif
{
	// create the app instance
	auto app = std::make_unique<TheApp>();
	if (!app->Create(1280, 720, "LAB5"))
	{
		// something went wrong in initialization, exit
		IApplication::Debug("APP START FAILED");
		return 0;
	}

	// run the app and exit when done
	app->Run();
	return 0;
}

