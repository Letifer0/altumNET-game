#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <string>

#include "../include/interface.h"
#include "../include/map.h"
#include "../include/RustTypes.h"
#include "../include/settings.h"
#include "../include/cross_platforming.h"
#include "../include/game_character.h"
#include "../include/enemy.h"
#include "../include/enemy_codes.h"
#include "../include/card_codes.h"

using namespace std;

Interface::Interface() {
	// interface id
	// 		1 - main menu
	// 		2 - lobby
	// 		3 - game interface
	// 		4 - battle interface
	// 		5 - game settings menu
	this -> id = 1;
	this -> start_position_controlRooms.X = -1;
	this -> start_position_controlRooms.Y = -1;
	this -> start_array_value_controlRooms.X = -1;
	this -> start_array_value_controlRooms.Y = -1;
	this -> change_the_interface = false;
	this -> cleaning_lines_gameRoomInfo = 0;
	this -> cleaning_lines_gameFieldInfo = 0;
	this -> cleaning_lines_battleFieldInfo = 0;
}

Interface::~Interface() {

}

// game interface modules

	// game interface node

	void Interface::outputGameInterface(HANDLE handle, 
										GameLevel *gameLevel,
										GameHero *hero,
										Settings *settings,
										i16 console_columns, 
										i16 console_lines) 
	{
		i16 room_pattern = 0;
		switch(this -> id) {
			case 3:

				clearConsole();
				
				//this -> outputGameInterfaceBorder(handle, "rooms");
				//this -> outputGameInterfaceBorder(handle, "roomsInfo");
				//this -> outputGameInterfaceBorder(handle, "characterInfo");
				//this -> outputGameInterfaceBorder(handle, "statusBar");
				//this -> outputGameInterfaceBorder(handle, "fieldInfo");
				//this -> outputGameInterfaceBorder(handle, "backpack");

				this -> outputGameHeroInfo(handle, settings, hero);
				
				this -> outputGameRooms(handle, 
										gameLevel,
										settings,
										console_columns, 
										console_lines);
				this -> outputGameBackpack(handle, settings, hero);

				while(true) {
					switch(_getch()) {
						case (i16)settings -> CONTROL_KEY_MODULE_IF_ROOMSCON:
							this -> controlGameRooms(handle, 
													settings,
													gameLevel,
													console_columns, 
													console_lines);
							if(this -> change_the_interface == true) {
								this -> change_the_interface = false;
								return this -> outputGameInterface(handle, 
																gameLevel,
																hero,
																settings, 
																console_columns, 
																console_lines);
							}
							break;

						case (i16)settings -> CONTROL_KEY_MODULE_IF_BACKPACK:
							this -> controlGameBackpack(handle,
														settings,
														hero);
							break;
						case (i16)settings -> CONTROL_KEY_EXIT:
							return;

						default:
							break;
					}
				}

				break;
			case 4:

				clearConsole();

				switch(gameLevel -> map[start_array_value_controlRooms.Y]
										[start_array_value_controlRooms.X]) 
				{
					case 1: 
					{
						room_pattern = 1 + rand() % 5;
						Enemy enemy(gameLevel -> level, room_pattern, ENEMY_COMMON);

						hero -> shufflingDeckOfCards(false);

						this -> outputBattleListOfEnemy(handle,
														settings,
														&enemy);
						this -> outputBattleHeroInfo(handle,
													settings,
													hero);
						hero -> gettingsCardsFromTheDeck(false);

						this -> outputBattleTurn(handle,
												settings,
												hero);

						this -> outputBattleHand(handle,
												settings,
												hero);
						while (true) {

							switch (_getch()) {
								case (i16)settings -> CONTROL_KEY_NEXT_TURN:
									this -> clearBattleCardsInteface(handle, hero -> card_hand.size());
									hero -> resetCardsIntoTheDumpStack(false);
									hero -> gettingsCardsFromTheDeck(false);
									
									hero -> turn_number += 1;
									if (hero -> turn_number > 50000) {
										hero -> turn_number = 0;
									}

									this -> outputBattleTurn(handle,
															settings,
															hero);
									
									this -> outputBattleHand(handle,
															settings,
															hero);
									continue;
								case (i16)settings -> CONTROL_KEY_MODULE_IF_CARD_HAND:
									this -> controlBattleHand(handle, 
															settings,
															hero);

									break;
								case (i16)settings -> CONTROL_KEY_EXIT_ROOM:
									hero -> dump_stack.resize(0);
									hero -> card_stack.resize(0);
									hero -> turn_number = 0;

									this -> id = 3;

									gameLevel -> map[this -> start_array_value_controlRooms.Y]
													[this -> start_array_value_controlRooms.X] = -1;
									gameLevel -> map_masc[this -> start_array_value_controlRooms.Y]
														[this -> start_array_value_controlRooms.X] = " [EMPTY~] ";
									return this -> outputGameInterface(handle,
																		gameLevel,
																		hero,
																		settings,
																		console_columns,
																		console_lines);
							}
						}
					}
						break;
					case 2:
					{
						room_pattern = 1;
						Enemy enemy(gameLevel -> level, room_pattern, ENEMY_BOSS);

						hero -> shufflingDeckOfCards(false);

						this -> outputBattleListOfEnemy(handle,
														settings,
														&enemy);
						this -> outputBattleHeroInfo(handle,
													settings,
													hero);
						hero -> gettingsCardsFromTheDeck(false);

						this -> outputBattleTurn(handle,
												settings,
												hero);

						this -> outputBattleHand(handle,
												settings,
												hero);

						while (true) {
							switch (_getch()) {
								case (i16)settings -> CONTROL_KEY_NEXT_TURN:
									this -> clearBattleCardsInteface(handle, hero -> card_hand.size());
									hero -> resetCardsIntoTheDumpStack(false);
									hero -> gettingsCardsFromTheDeck(false);

									hero -> turn_number += 1;
									if (hero -> turn_number > 50000) {
										hero -> turn_number = 0;
									}

									this -> outputBattleTurn(handle,
															settings,
															hero);

									this -> outputBattleHand(handle,
															settings,
															hero);
									continue;
								case (i16)settings -> CONTROL_KEY_EXIT_ROOM:
									hero -> dump_stack.resize(0);
									hero -> card_stack.resize(0);
									hero -> turn_number = 0;

									this -> id = 3;

									gameLevel -> map[this -> start_array_value_controlRooms.Y]
													[this -> start_array_value_controlRooms.X] = 3;
									gameLevel -> map_masc[this -> start_array_value_controlRooms.Y]
														[this -> start_array_value_controlRooms.X] = " [POINT~] ";
									return this -> outputGameInterface(handle,
																	gameLevel,
																	hero,
																	settings,
																	console_columns,
																	console_lines);
							}
						}
					}
				}
				break;
			case 5:
				break;
			default:
				break;
		}
	}

	// border module interface

	void Interface::outputGameInterfaceBorder(HANDLE handle, Settings* settings, const char *module_border) {
		COORD position;

		// module size
		i16 moduleColums = 0;
		i16 moduleLines = 0;
		
		if (module_border == "rooms") {
			moduleColums = 98;
			moduleLines = 37;

			position.X = 50;
			position.Y = 14;
		}
		else if (module_border == "roomsInfo") {
			moduleColums = 98;
			moduleLines = 15;

			position.X = 50;
			position.Y = 0;
		}
		else if (module_border == "characterInfo") {
			moduleColums = 51;
			moduleLines = 51;

			position.X = 0;
			position.Y = 0;
		}
		else if (module_border == "statusBar") {
			moduleColums = 51;
			moduleLines = 20;

			position.X = 0;
			position.Y = 50;
		}
		else if (module_border == "fieldInfo") {
			moduleColums = 98;
			moduleLines = 20;

			position.X = 50;
			position.Y = 50;
		}		
		else if (module_border == "backpack") {
			moduleColums = 52;
			moduleLines = 70;

			position.X = 147;
			position.Y = 0;
		}		


		i16 tmp_X_buffer = position.X;

		for (i16 i = 0; i < moduleLines; i++) {
			for (i16 j = 0; j < moduleColums; j++) {
				if (position.Y == 0 || position.Y == 69) {
					SetConsoleCursorPosition(handle, position);
					SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
					cout << "-";
				}
				else {
					if(j == 0 || j == moduleColums - 1) {
						SetConsoleCursorPosition(handle, position);
						SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
						cout << "|";
					}
					else if (i == 0 || i == moduleLines - 1) {
						SetConsoleCursorPosition(handle, position);
						SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
						cout << "-";
					}
				}

				position.X += 1;
			}

			position.X = tmp_X_buffer;
			position.Y += 1;
		}
	}

	// choosing rooms output module

	void Interface::outputGameRooms(HANDLE handle, 
									GameLevel *gameLevel, 
									Settings *settings,
									i16 console_columns, 
									i16 console_lines) 
	{
		COORD position;

		position.X = (console_columns / 2) - (gameLevel -> size * 5) - 1;
		position.Y = (console_lines / 2) - (gameLevel -> size * 2) - 1;
		
		for(i16 i = 0; i < gameLevel -> size; i++) {
			SetConsoleCursorPosition(handle, position);
			SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);

			for (i16 j = 0; j < gameLevel -> size; j++) {
					cout << gameLevel -> map_masc[i][j];
			}

			position.Y += 4;
		}
	}

	// choosing rooms control module

	void Interface::controlGameRooms(HANDLE handle, 
									Settings *settings, 
									GameLevel* gameLevel, 
									i16 console_columns, 
									i16 console_lines) 
	{
		COORD null_position;

		null_position.X = (console_columns / 2) - (gameLevel -> size * 5) - 1;
		null_position.Y = (console_lines / 2) - (gameLevel -> size * 2) - 1;

		if (this -> start_position_controlRooms.X == -1 
			|| this -> start_position_controlRooms.Y == -1 
			|| this -> start_array_value_controlRooms.X == -1 
			|| this -> start_array_value_controlRooms.Y == -1) 
		{
			for (i16 i = 0; i < gameLevel -> size; i++) {
				for (i16 j = 0; j < gameLevel -> size; j++) {
					if (gameLevel -> map[i][j] == 0) {
						this -> start_position_controlRooms.X = j * 10;
						this -> start_position_controlRooms.Y = i * 4;
					
						this -> start_array_value_controlRooms.X = j;
						this -> start_array_value_controlRooms.Y = i;

						break;
					}
				}
			}

			this -> start_position_controlRooms.X += null_position.X;
			this -> start_position_controlRooms.Y += null_position.Y;
		}

		this -> outputGameRoomInfo(handle, gameLevel, settings, this -> start_array_value_controlRooms);

		SetConsoleCursorPosition(handle, this -> start_position_controlRooms);
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << gameLevel -> map_masc[this -> start_array_value_controlRooms.Y]
									[this -> start_array_value_controlRooms.X];

		COORD second_array_value;

		second_array_value.X = 0;
		second_array_value.Y = 0;

		COORD second_position;

		second_position.X = this -> start_position_controlRooms.X;
		second_position.Y = this -> start_position_controlRooms.Y;


		while(true) {
			switch(_getch()) {
				case (i16)settings -> CONTROL_KEY_UP:
					second_position.X = this -> start_position_controlRooms.X;
					second_position.Y = this -> start_position_controlRooms.Y;
					second_array_value.X = this -> start_array_value_controlRooms.X;
					second_array_value.Y = this -> start_array_value_controlRooms.Y;

					if (this -> start_array_value_controlRooms.Y == 0) {
						this -> start_position_controlRooms.Y = null_position.Y + ((gameLevel -> size - 1) * 4);
						this -> start_array_value_controlRooms.Y = gameLevel -> size - 1;
					}
					else {
						this -> start_position_controlRooms.Y -= 4;
						this -> start_array_value_controlRooms.Y--;
					}
					
					this -> outputGameRoomInfo(handle, gameLevel, settings, this -> start_array_value_controlRooms);
					break;

				case (i16)settings -> CONTROL_KEY_DOWN:
					second_position.X = this -> start_position_controlRooms.X;
					second_position.Y = this -> start_position_controlRooms.Y;
					second_array_value.X = this -> start_array_value_controlRooms.X;
					second_array_value.Y = this -> start_array_value_controlRooms.Y;

					if (this -> start_array_value_controlRooms.Y == gameLevel -> size - 1) {
						this -> start_position_controlRooms.Y = null_position.Y;
						this -> start_array_value_controlRooms.Y = 0;
					}
					else {
						this -> start_position_controlRooms.Y += 4;
						this -> start_array_value_controlRooms.Y++;
					}

					this -> outputGameRoomInfo(handle, gameLevel, settings, this -> start_array_value_controlRooms);
					break;

				case (i16)settings -> CONTROL_KEY_LEFT:
					second_position.X = this -> start_position_controlRooms.X;
					second_position.Y = this -> start_position_controlRooms.Y;
					second_array_value.X = this -> start_array_value_controlRooms.X;
					second_array_value.Y = this -> start_array_value_controlRooms.Y;

					if (this -> start_array_value_controlRooms.X == 0) {
						this -> start_position_controlRooms.X = null_position.X + ((gameLevel -> size - 1) * 10);
						this -> start_array_value_controlRooms.X = gameLevel -> size - 1;
					}
					else {
						this -> start_position_controlRooms.X -= 10;
						this -> start_array_value_controlRooms.X--;
					}

					this -> outputGameRoomInfo(handle, gameLevel, settings, this -> start_array_value_controlRooms);
					break;

				case (i16)settings -> CONTROL_KEY_RIGHT:
					second_position.X = this -> start_position_controlRooms.X;
					second_position.Y = this -> start_position_controlRooms.Y;
					second_array_value.X = this -> start_array_value_controlRooms.X;
					second_array_value.Y = this -> start_array_value_controlRooms.Y;

					if (this -> start_array_value_controlRooms.X == gameLevel -> size - 1) {
						this -> start_position_controlRooms.X = null_position.X;
						this -> start_array_value_controlRooms.X = 0;
					}
					else {
						this -> start_position_controlRooms.X += 10;
						this -> start_array_value_controlRooms.X++;
					}

					this -> outputGameRoomInfo(handle, gameLevel, settings, this -> start_array_value_controlRooms);
					break;

				case (i16)settings -> CONTROL_KEY_MODULE_IF_ROOMSCON:
					SetConsoleCursorPosition(handle, this -> start_position_controlRooms);
					SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
					cout << gameLevel -> map_masc[this -> start_array_value_controlRooms.Y]
										[this -> start_array_value_controlRooms.X];
					this -> outputGameRoomInfo(handle, gameLevel, settings, this -> start_array_value_controlRooms, true);
					return;

				case (i16)settings -> CONTROL_KEY_ENTER_ROOM:

					if((this -> start_array_value_controlRooms.Y != gameLevel -> size - 1
						&& gameLevel -> map_masc[this -> start_array_value_controlRooms.Y + 1][this -> start_array_value_controlRooms.X][1] == '[')
						|| (this -> start_array_value_controlRooms.Y != 0
						&& gameLevel -> map_masc[this -> start_array_value_controlRooms.Y - 1][this -> start_array_value_controlRooms.X][1] == '[')
						|| (this -> start_array_value_controlRooms.X  != gameLevel -> size - 1
						&& gameLevel -> map_masc[this -> start_array_value_controlRooms.Y][this -> start_array_value_controlRooms.X + 1][1] == '[')
						|| (this -> start_array_value_controlRooms.X != 0
						&& gameLevel -> map_masc[this -> start_array_value_controlRooms.Y][this -> start_array_value_controlRooms.X - 1][1] == '['))
					{
						switch(gameLevel -> map[this -> start_array_value_controlRooms.Y][this -> start_array_value_controlRooms.X]) {
							// battle room id 
							case 1: 
								// battle interface id
								SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
								this -> id = 4;
								this -> change_the_interface = true;
								return;
							// boss fight room id
							case 2:
								// battle interface id
								SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
								this -> id = 4;
								this -> change_the_interface = true;
								return;
							default:
								break;
						}
					}
					break;
			}

			SetConsoleCursorPosition(handle, second_position);
			SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
			cout << gameLevel -> map_masc[second_array_value.Y]
								[second_array_value.X];

			SetConsoleCursorPosition(handle, this -> start_position_controlRooms);
			SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
			cout << gameLevel -> map_masc[this -> start_array_value_controlRooms.Y]
								[this -> start_array_value_controlRooms.X];
		}
	}

	void Interface::outputGameRoomInfo(HANDLE handle, 
									GameLevel *gameLevel,
									Settings *settings,
									COORD array_value, 
									bool field_clearing_mode) 
	{
		COORD position;

		const i16 moduleColums = 98;
		const i16 moduleLines = 15;

		position.X = 51;
		position.Y = 1;

		for (i16 i = 1; i < moduleLines - 1; i++) {
			if(i > this -> cleaning_lines_gameRoomInfo) {
				break;
			}
			SetConsoleCursorPosition(handle, position);
			cout << "                                "; // 32 spaces
			cout << "                                "; // 32 spaces
			cout << "                                "; // 32 spaces
			position.Y += 1;
		}

		this -> cleaning_lines_gameRoomInfo = 0;

		if(field_clearing_mode == true) {
			return;
		}

		position.X = 51;
		position.Y = 1;

		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);

		cout << gameLevel -> map_masc[array_value.Y][array_value.X];

		this -> cleaning_lines_gameRoomInfo += 2;

		position.X = 52;
		position.Y = 3;

		SetConsoleCursorPosition(handle, position);

		if(gameLevel -> map_masc[array_value.Y][array_value.X][1] == '#') {
			cout << "~CORRUPTED DATA:";
			position.Y += 2;
			this -> cleaning_lines_gameRoomInfo += 2;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					SetConsoleCursorPosition(handle, position);
					cout << hex << 4369 + rand() % 65535 << dec;
					position.X += 5;
				}
				position.X = 52;
				position.Y += 2;
				this -> cleaning_lines_gameRoomInfo += 2;
			}
		}
		else {
			switch(gameLevel -> map[array_value.Y][array_value.X]) {
				case -1:
					cout << "~ Empty data";

					this -> cleaning_lines_gameRoomInfo += 1;
					
					break;

				case 0:
					cout << "~ The entry point to the wormhole level";
					
					this -> cleaning_lines_gameRoomInfo += 1;
					
					break;

				case 1:
					cout << "~ A battle for this data is expected";
					
					this -> cleaning_lines_gameRoomInfo += 1;
					
					break;

				case 2:
					cout << "~ This data is seriously protected";

					position.Y += 1;
					SetConsoleCursorPosition(handle, position);
					cout << "~ A battle is expected for data and an entry point to the next level of immersion";
					
					position.Y += 1;
					SetConsoleCursorPosition(handle, position);
					cout << "~ Expected GUARD";

					this -> cleaning_lines_gameRoomInfo += 3;
					
					break;

				case 3:
					cout << "~ The entry point to the next level of immersion";

					this -> cleaning_lines_gameRoomInfo += 1;

					break;

				default:
					break;
			}
		}
	}

	// character information output module
	void Interface::outputGameHeroInfo(HANDLE handle, 
										Settings *settings, 
										GameHero *hero) 
	{
		COORD position;

		// const i16 moduleColums = 51;
		// const i16 moduleLines = 51;

		position.X = 1;
		position.Y = 1;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << "	" << hero -> name;

		position.Y = 3;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << "& Health points: ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << hero -> health_points;

		position.Y = 4;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << "& Memory: ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << hero -> memory_points;
	}

	// character information control module
	void Interface::controlGameHeroInfo() {}

	// status bar output module
	void Interface::outputGameStatusBar() {
		COORD position;

		// const i16 moduleColums = 51;
		// const i16 moduleLines = 20;

		position.X = 0;
		position.Y = 50;	
	}

	// status bar controle module
	void Interface::controlGameStatusBar() {}

	// backpack output module
	void Interface::outputGameBackpack(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;	

		// const i16 moduleColums = 52;
		// const i16 moduleLines = 70;

		position.X = 147;
		position.Y = 0;

		position.Y = 2;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << "		DATA PACKAGE STORAGE";

		position.Y = 5;

		for(i16 i = 0; i < hero -> number_of_cards; i++) {
			SetConsoleCursorPosition(handle, position);
			this -> outputCardName(handle, 
									settings, 
									hero -> card_list[i],
									settings -> CS_FIRST_COLOR);
			position.Y += 2;
		}
	}


	// backpack controle module
	void Interface::controlGameBackpack(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;	

		// const i16 moduleColums = 52;
		// const i16 moduleLines = 70;

		position.X = 147;
		position.Y = 5;

		i16 vector_index = 0;
		i16 second_vector_index = vector_index;
		
		this -> outputGameFieldInfo(handle, hero, settings, hero -> card_list[vector_index]);

		SetConsoleCursorPosition(handle, position);	
		this -> outputCardName(handle, settings, hero -> card_list[vector_index], settings -> CS_SECOND_COLOR);
		
		COORD second_position;

		second_position.X = position.X;
		second_position.Y = position.Y;

		while(true) {
			switch(_getch()) {
				case (i16)settings -> CONTROL_KEY_UP:
					second_position.X = position.X;
					second_position.Y = position.Y;
					second_vector_index = vector_index;

					if (vector_index == 0) {
						position.Y = 5 + (hero -> card_list.size() - 1) * 2;
						vector_index = hero -> card_list.size() - 1;
					}
					else {
						position.Y -= 2;
						vector_index--;
					}
					
					this -> outputGameFieldInfo(handle, hero, settings, hero -> card_list[vector_index]);
					break;

				case (i16)settings -> CONTROL_KEY_DOWN:
					second_position.X = position.X;
					second_position.Y = position.Y;
					second_vector_index = vector_index;

					if (vector_index == hero -> card_list.size() - 1) {
						position.Y = 5;
						vector_index = 0;
					}
					else {
						position.Y += 2;
						vector_index++;
					}

					this -> outputGameFieldInfo(handle, hero, settings, hero -> card_list[vector_index]);
					break;

				case (i16)settings -> CONTROL_KEY_MODULE_IF_BACKPACK:

					SetConsoleCursorPosition(handle, position);	
					this -> outputCardName(handle, settings, hero -> card_list[vector_index], settings -> CS_FIRST_COLOR);

					this -> outputGameFieldInfo(handle, hero, settings, hero -> card_list[vector_index], true);
					return;
			}

			SetConsoleCursorPosition(handle, second_position);	
			this -> outputCardName(handle, settings, hero -> card_list[second_vector_index], settings -> CS_FIRST_COLOR);

			SetConsoleCursorPosition(handle, position);	
			this -> outputCardName(handle, settings, hero -> card_list[vector_index], settings -> CS_SECOND_COLOR);
		}
	}

	// A detailed field of information: 
	// about the items of the backpack, 
	// about the characteristics of the character, 
	// about the status of the character in the status bar
	void Interface::outputGameFieldInfo(HANDLE handle, 
									GameHero *hero,
									Settings *settings,
									i16 vector_value, 
									bool field_clearing_mode) 
	{
		COORD position;

		const i16 moduleColums = 98;
		const i16 moduleLines = 20;

		position.X = 51;
		position.Y = 50;

		for (i16 i = 1; i < moduleLines - 1; i++) {
			if(i > this -> cleaning_lines_gameFieldInfo) {
				break;
			}
			SetConsoleCursorPosition(handle, position);
			cout << "                                "; // 32 spaces
			cout << "                                "; // 32 spaces
			cout << "                                "; // 32 spaces
			position.Y += 1;
		}

		this -> cleaning_lines_gameFieldInfo = 0;

		if(field_clearing_mode == true) {
			return;
		}

		position.X = 51;
		position.Y = 50;

		SetConsoleCursorPosition(handle, position);
		this -> outputCardName(handle, settings, vector_value, settings -> CS_SECOND_COLOR);

		this -> cleaning_lines_gameFieldInfo += 2;

		position.X = 53;
		position.Y = 52;

		SetConsoleCursorPosition(handle, position);

		switch(vector_value) {
			case KNIGHT_STRIKE:

				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Cost    ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 1 << " ]";

				position.Y += 1;

				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Damage  ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 6 << " ]";
				
				this -> cleaning_lines_gameFieldInfo += 2;

				break;
			case KNIGHT_DEFEND:

				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Cost    ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 1 << " ]";

				position.Y += 1;

				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Armor   ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ +" << 5 << " ]";

				this -> cleaning_lines_gameFieldInfo += 2;

				break;
			case KNIGHT_FLAMING_SWORD_STRIKE:

				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Cost    ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 2 << " ]";

				position.Y += 1;

				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Damage  ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 8 << " ]";

				position.Y += 2;

				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "# Superimposed effects: ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "Flame [ " << 3 << " ] ";
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << ";";

				this -> cleaning_lines_gameFieldInfo += 4;

				break;
			default:
				break;
		}
	}

// battle interface

	void Interface::outputBattleListOfEnemy(HANDLE handle, 
								Settings *settings,
								Enemy *enemy) 
	{
		COORD position;

		// const i16 moduleColums = 51;
		// const i16 moduleLines = 26;

		position.X = 1;
		position.Y = 1;

		for (int i = 0; i <	enemy -> number_of_enemies; i++) {
			SetConsoleCursorPosition(handle, position);
			SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
			cout << enemy -> name[i];
			position.Y++;

			SetConsoleCursorPosition(handle, position);
			SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
			cout << "    HP: ";
			SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
			cout << enemy -> health_points[i];
			position.Y += 5;
		}
	}

	void Interface::outputBattleHeroInfo(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;

		// const i16 moduleColums = 51;
		// const i16 moduleLines = 24;

		position.X = 1;
		position.Y = 27;

		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << "	" << hero -> name;

		position.Y += 2;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << "& Health points: ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << hero -> health_points;

		position.Y++;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << "& Memory: ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << hero -> memory_points;
	}

	void Interface::outputBattleStackOfCard(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;	

		// const i16 moduleColums = 52;
		// const i16 moduleLines = 70;

		position.X = 147;
		position.Y = 0;

		position.Y = 4;
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << "		CARD STACK";

		position.Y = 7;

		for(i16 i = 0; i < hero -> card_stack.size(); i++) {
			SetConsoleCursorPosition(handle, position);
			this -> outputCardName(handle, settings, hero -> card_stack[i], settings -> CS_FIRST_COLOR);
			position.Y += 2;
		}
	}

	void Interface::outputBattleHand(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;	

		// const i16 moduleColums = 52;
		// const i16 moduleLines = 70;

		position.X = 147;
		position.Y = 4;

		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << "   stack [ ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << hero -> card_stack.size();
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << " ] ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << "CARD HAND";
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << " [ ";
		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << hero -> dump_stack.size();
		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << " ] dump";

		position.Y = 7;

		for(i16 i = 0; i < hero -> card_hand.size(); i++) {
			SetConsoleCursorPosition(handle, position);
			this -> outputCardName(handle, settings, hero -> card_hand[i], settings -> CS_FIRST_COLOR);
			position.Y += 2;
		}
	}

	void Interface::clearBattleCardsInteface(HANDLE handle, i16 size) {
		COORD position;

		// const i16 moduleColums = 52;
		// const i16 moduleLines = 70;

		position.X = 147;
		position.Y = 4;

		SetConsoleCursorPosition(handle, position);
		cout << "                          ";
		cout << "                          ";

		position.Y = 7;

		for (i16 i = 0; i < size; i++) {
			SetConsoleCursorPosition(handle, position);
			cout << "                          ";
			cout << "                          ";
			position.Y += 2;		
		}
	}

	void Interface::outputCardName(HANDLE handle, Settings *settings, i16 card, i16 color) {
		switch(card) {
			case KNIGHT_STRIKE:
				SetConsoleTextAttribute(handle, settings -> CS_COMMON_RARITY_COLOR);
				cout << "&  ";
				SetConsoleTextAttribute(handle, color);
				cout << "Strike";
				break;
			case KNIGHT_DEFEND:
				SetConsoleTextAttribute(handle, settings -> CS_COMMON_RARITY_COLOR);
				cout << "&  ";
				SetConsoleTextAttribute(handle, color);
				cout << "Defend";
				break;
			case KNIGHT_FLAMING_SWORD_STRIKE:
				SetConsoleTextAttribute(handle, settings -> CS_RARE_RARITY_COLOR);
				cout << "&  ";
				SetConsoleTextAttribute(handle, color);
				cout << "Sword Strike: Flaming";
				break;
			default:
				break;
		}
	}

	void Interface::controlBattleHand(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;	

		// const i16 moduleColums = 52;
		// const i16 moduleLines = 70;

		position.X = 147;
		position.Y = 7;

		i16 vector_index = 0;
		i16 second_vector_index = vector_index;

		this -> outputBattleFieldInfo(handle, hero, settings, hero -> card_hand[vector_index]);

		SetConsoleCursorPosition(handle, position);	
		this -> outputCardName(handle, settings, hero -> card_hand[vector_index], settings -> CS_SECOND_COLOR);
		
		COORD second_position;

		second_position.X = position.X;
		second_position.Y = position.Y;

		while(true) {
			switch(_getch()) {
				case (i16)settings -> CONTROL_KEY_UP:
					second_position.X = position.X;
					second_position.Y = position.Y;
					second_vector_index = vector_index;

					if (vector_index == 0) {
						position.Y = 7 + (hero -> card_hand.size() - 1) * 2;
						vector_index = hero -> card_hand.size() - 1;
					}
					else {
						position.Y -= 2;
						vector_index--;
					}
					
					this -> outputBattleFieldInfo(handle, hero, settings, hero -> card_hand[vector_index]);
					
					break;

				case (i16)settings -> CONTROL_KEY_DOWN:
					second_position.X = position.X;
					second_position.Y = position.Y;
					second_vector_index = vector_index;

					if (vector_index == hero -> card_hand.size() - 1) {
						position.Y = 7;
						vector_index = 0;
					}
					else {
						position.Y += 2;
						vector_index++;
					}

					this -> outputBattleFieldInfo(handle, hero, settings, hero -> card_hand[vector_index]);
					
					break;

				case (i16)settings -> CONTROL_KEY_MODULE_IF_CARD_HAND:

					SetConsoleCursorPosition(handle, position);	
					this -> outputCardName(handle, settings, hero -> card_hand[vector_index], settings -> CS_FIRST_COLOR);

					this -> outputBattleFieldInfo(handle, hero, settings, hero -> card_hand[vector_index], true);
					
					return;
			}

			SetConsoleCursorPosition(handle, second_position);	
			this -> outputCardName(handle, settings, hero -> card_hand[second_vector_index], settings -> CS_FIRST_COLOR);

			SetConsoleCursorPosition(handle, position);	
			this -> outputCardName(handle, settings, hero -> card_hand[vector_index], settings -> CS_SECOND_COLOR);
		}
	}

	void Interface::outputBattleFieldInfo(HANDLE handle, 
											GameHero *hero,
											Settings *settings,
											i16 vector_value, 
											bool field_clearing_mode) 
	{
		COORD position;

		const i16 moduleColums = 98;
		const i16 moduleLines = 35;

		position.X = 51;
		position.Y = 37;

		for (i16 i = 1; i < moduleLines - 1; i++) {
			if(i > this -> cleaning_lines_battleFieldInfo) {
				break;
			}

			SetConsoleCursorPosition(handle, position);
			cout << "                                "; // 32 spaces
			cout << "                                "; // 32 spaces
			cout << "                                "; // 32 spaces
			position.Y += 1;
		}

		this -> cleaning_lines_battleFieldInfo = 0;

		if(field_clearing_mode == true) {
			return;
		}

		position.X = 51;
		position.Y = 37;

		SetConsoleCursorPosition(handle, position);
		this -> outputCardName(handle, settings, vector_value, settings -> CS_SECOND_COLOR);

		this -> cleaning_lines_battleFieldInfo += 2;

		position.X = 53;
		position.Y = 39;

		SetConsoleCursorPosition(handle, position);

		switch(vector_value) {
			case KNIGHT_STRIKE:

				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Cost    ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 1 << " ]";

				position.Y += 1;
				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Damage  ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 6 << " ]";

				this -> cleaning_lines_battleFieldInfo += 2;

				break;

			case KNIGHT_DEFEND:

				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Cost    ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 1 << " ]";

				position.Y += 1;
				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Armor   ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ +" << 5 << " ]";

				this -> cleaning_lines_battleFieldInfo += 2;

				break;

			case KNIGHT_FLAMING_SWORD_STRIKE:

				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Cost    ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 2 << " ]";

				position.Y += 1;
				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "~ Damage  ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "[ " << 8 << " ]";

				position.Y += 2;
				SetConsoleCursorPosition(handle, position);
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << "# Superimposed effects: ";
				SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
				cout << "Flame [ " << 3 << " ] ";
				SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
				cout << ";";

				this -> cleaning_lines_battleFieldInfo += 4;

				break;

			default:
				break;
		}
	}

	void Interface::outputBattleTurn(HANDLE handle, Settings *settings, GameHero *hero) {
		COORD position;

		position.X = 150;
		position.Y = 1;

		SetConsoleCursorPosition(handle, position);

		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << "~/#$ ";

		SetConsoleTextAttribute(handle, settings -> CS_SECOND_COLOR);
		cout << "TURN [ " << hero -> turn_number << " ]";

		SetConsoleTextAttribute(handle, settings -> CS_FIRST_COLOR);
		cout << " $#/~";
	}