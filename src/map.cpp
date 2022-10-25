#include <iostream>
#include <ctime>
#include <windows.h>
#include <sstream>
#include <string>

#include "../include/map.h"
#include "../include/RustTypes.h"

using namespace std;

GameLevel::GameLevel(i16 game_level) {
	this -> level = game_level;

	switch(this -> level) {
		case 1:
			this -> size = 4;
			break;
		case 2:
			this -> size = 5;
			break;
		case 3:
			this -> size = 5;
			break;
		case 4:
			this -> size = 6;
			break;
		case 5:
			this -> size = 6;
			break;
		case 6:
			this -> size = 7;
			break;
		case 7:
			this -> size = 7;
			break;
		case 8:
			this -> size = 8;
			break;
		case 9:
			this -> size = 8;
			break;
		case 10:
			this -> size = 9;
			break;
		default:
			this -> size = 9;
			break;
	}
	this -> map = new i16*[this -> size];

	for (i16 i = 0; i < this -> size; i++) {
		this -> map[i] = new i16[this -> size];
	}
	for (i16 i = 0; i < this -> size; i++) {
		for (i16 j = 0; j < this -> size; j++) {
			this -> map[i][j] = -3;
		}
	}

	this -> map_masc = new string*[this -> size];

	for (i16 i = 0; i < this -> size; i++) {
		this -> map_masc[i] = new string[this -> size];
	}
}

GameLevel::~GameLevel() {
	for (i16 i = 0; i < this -> size; i++) {
		delete [] this -> map_masc[i];
	}

	delete [] this -> map_masc;
	
	for (i16 i = 0; i < this -> size; i++) {
		delete [] this -> map[i];
	}
	
	delete [] this -> map;
}

void GameLevel::generateLevel() {
	// 0 - start room

	COORD start_room;

	start_room.X = (1 + rand() % this -> size) - 1;
	start_room.Y = (1 + rand() % this -> size) - 1;

	this -> map[start_room.Y][start_room.X] = 0;

	if (this -> size - 1 - start_room.Y == start_room.Y
		&& this -> size - 1 - start_room.X == start_room.X) 
	{
		this -> map[this -> size - start_room.Y - 2]
					[this -> size - start_room.X - 2] = 2;
	}
	else {
		this -> map[this -> size - 1 - start_room.Y]
					[this -> size - 1 - start_room.X] = 2;
	}

	// 1 - battle room

	for(i16 i = 0; i < this -> size; i++) {
		for (i16 j = 0; j < this -> size; j++) {
			if(this -> map[i][j] == 0
			 || this -> map[i][j] == 2) {
				continue;
			}
			this -> map[i][j] = 1;
		}
	}

	for(i16 i = 0; i < this -> size; i++) {
		for (i16 j = 0; j < this -> size; j++) {
			if (this -> map[i][j] == 0) {
				this -> map_masc[i][j] = " [START~] ";
			}
			else if (this -> map[i][j] == 2) {
				this -> map_masc[i][j] = " <GUARD~> ";
			}
			else {
				string level_determinant;

				switch(this -> level) {
					case 1:
						level_determinant = "#I-";
						break;
					case 2:
						level_determinant = "#II";
						break;
					case 3:
						level_determinant = "#Oo";
						break;
					case 4:
						level_determinant = "#Rs";
						break;
					case 5:
						level_determinant = "#Ex";
						break;
					case 6:
						level_determinant = "#pl";
						break;
					case 7:
						level_determinant = "#ss";
						break;
					case 8:
						level_determinant = "#U8";
						break;
					case 9:
						level_determinant = "#A-";
						break;
					case 10:
						level_determinant = "#0x";
						break;
					default:
						level_determinant = "#De";
						break;
				}
				
				stringstream tmp;
				tmp << level_determinant << hex << uppercase << 4369 + rand() % 65535 << dec << "#";
				tmp >> this -> map_masc[i][j];
				this -> map_masc[i][j] = ' ' + this -> map_masc[i][j] + ' ';
			}
		}
	}
}
