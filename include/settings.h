#pragma once

#include "RustTypes.h"

using namespace std;

class Settings {
	public:
		Settings();
		~Settings();

		// color settings (CS)
			// light-red
			i16 CS_FIRST_COLOR; 
			// light-blue
			i16 CS_SECOND_COLOR; 
			// white
			i16 CS_COMMON_RARITY_COLOR;
			// light-green
			i16 CS_RARE_RARITY_COLOR;
			// light-pirple
			i16 CS_EPIC_RARITY_COLOR;
			// light-yellow
			i16 CS_LEGENDARY_RARITY_COLOR;
			// light-dark-blue
			i16 CS_MYTHICAL_RARITY_COLOR;
		enum : char {
			// W
			CONTROL_KEY_UP = 'w',
			// A
			CONTROL_KEY_DOWN = 's',
			// S
			CONTROL_KEY_LEFT = 'a',
			// D
			CONTROL_KEY_RIGHT = 'd',
			// TAB
			CONTROL_KEY_MODULE_IF_ROOMSCON = '	',
			// E
			CONTROL_KEY_MODULE_IF_BACKPACK = 'e',
			// E
			CONTROL_KEY_MODULE_IF_CARD_HAND = 'e', 
			// ESC
			CONTROL_KEY_EXIT = 27,
			// F
			CONTROL_KEY_ENTER_ROOM = 'f',
			// Q
			CONTROL_KEY_EXIT_ROOM = 'q',
			// SPACE
			CONTROL_KEY_NEXT_TURN = ' ' 
		};
};