#define CONSOLE_COLUMS 200 // colums
#define CONSOLE_LINES 70   // lines
#define WINDOW_WIDTH 1500  // window width
#define WINDOW_HEIGHT 1000  // window height

#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <stdio.h>
#include <string>

#include "../include/interface.h"
#include "../include/map.h"
#include "../include/RustTypes.h"
#include "../include/settings.h"
#include "../include/cross_platforming.h"
#include "../include/game_character.h"

using namespace std;

void Start();
void Loop(HANDLE, Settings*);
void Game(HANDLE, GameHero*, Settings*, i16);

void Game(HANDLE handle, GameHero *hero, Settings *settings, i16 game_level) {
	// game level
	GameLevel gameLevel(game_level);
	gameLevel.generateLevel();	

	// general user level interface moduls
	Interface IF;
	IF.id = 3;

	// output interface
	IF.outputGameInterface(handle, &gameLevel, hero, settings, CONSOLE_COLUMS, CONSOLE_LINES);
}

void Start() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// settings
	Settings settings;

	Loop(handle, &settings);
}

void Loop(HANDLE handle, Settings *settings) {
	GameHero hero(1);
	Game(handle, &hero, settings, 1);
}


int main() {
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

		// console buffer
		COORD bufferSize = { CONSOLE_COLUMS, CONSOLE_LINES }; 

		// title
		SetConsoleTitle(L"AltumNET");

		// set buffer size
		SetConsoleScreenBufferSize(handle, bufferSize);

		// console cursor
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(handle, &CursorInfo);
		CursorInfo.bVisible = false;
		SetConsoleCursorInfo(handle, &CursorInfo);

		// window
		HWND hWinConsole = GetConsoleWindow();

		MoveWindow(hWinConsole, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
	}
	srand(time(NULL));

	Start();
	
	return 0;
}