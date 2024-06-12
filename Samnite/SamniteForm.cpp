#include "SamniteForm.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <winsock.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace Samnite; // Название проекта

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SamniteForm^ f = gcnew SamniteForm();
	Application::Run(f);
}

