#include "MyDef.h"
#include "../game/Applegate.h"
#include "../classes/MApplication.h"
#define WIN32_LEAN_AND_MEAN  

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Applegate ap;	
	ap.mSetTitle("HelloWorld");
	ap.mRun(hInstance, nCmdShow);
	return 0;
}