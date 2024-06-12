#include "ServerForm.h"
#include <Windows.h>
#include <iostream>
#include <winsock.h>
#include <vector>
#include <thread>
#include <time.h>
#include <string>
#include <mutex>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace oslab6; // Название проекта

int WINAPI WinMain(HINSTANCE a, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ServerForm^ f = gcnew ServerForm();
	Application::Run(f);

}
