#pragma once

#include <windows.h>
#include <string>

#include "settings.h"
#include "RustTypes.h"
#include "map.h"
#include "game_character.h"
#include "enemy.h"
#include "enemy_codes.h"

using namespace std;

class Interface {
	public:
		// interface id
		// 		1 - main menu
		// 		2 - lobby
		// 		3 - game interface
		// 		4 - battle interface
		//		5 - settings menu
		i16 id;
		COORD start_position_controlRooms;
		COORD start_array_value_controlRooms;
		// true - changing the interface
		// false - don`t changing the interface
		bool change_the_interface;
		u16 cleaning_lines_battleFieldInfo;
		u16 cleaning_lines_gameRoomInfo;
		u16 cleaning_lines_gameFieldInfo;

		Interface();
		~Interface();

// game interface

		void outputGameInterface(HANDLE,
								GameLevel*,
								GameHero*,
								Settings*,
								i16,
								i16);

		void outputGameInterfaceBorder(HANDLE,
									Settings*,
									const char*);

		void outputGameRooms(HANDLE, 
							GameLevel*,
							Settings*,
							i16, 
							i16);

		void controlGameRooms(HANDLE, 
							Settings*, 
							GameLevel*,
							i16, 
							i16);

		void outputGameRoomInfo(HANDLE, 
								GameLevel*,
								Settings*,
								COORD,
								bool = false);

		void outputGameHeroInfo(HANDLE,
								Settings*,
								GameHero*);

		void controlGameHeroInfo();

		void outputGameStatusBar();

		void controlGameStatusBar();

		void outputGameBackpack(HANDLE,
								Settings*,
								GameHero*);

		void controlGameBackpack(HANDLE,
								Settings*,
								GameHero*);

		void outputGameFieldInfo(HANDLE, 
								GameHero*,
								Settings*,
								i16,
								bool = false);

// battle interface
		void outputBattleListOfEnemy(HANDLE,
									Settings*,
									Enemy*);

		void controlBattleListOfEnemy();

		void outputBattleHeroInfo(HANDLE,
								Settings*,
								GameHero*);

		void outputBattleLog();

		void outputBattleFieldInfo(HANDLE,
									GameHero*,
									Settings*,
									i16, 
									bool = false);

		void outputBattleStackOfCard(HANDLE,
									Settings*,
									GameHero*);

		void controlBattleStackOfCard();

		void outputBattleDumpStack();

		void controlBattleDumpStack();

		void outputBattleHand(HANDLE,
							Settings*,
							GameHero*);

		void controlBattleHand(HANDLE,
							Settings*,
							GameHero*);
		
		void clearBattleCardsInteface(HANDLE, i16);

		void outputCardName(HANDLE,
							Settings*,
							i16,
							i16);

		void outputBattleTurn(HANDLE,
							Settings*,
							GameHero*);
};