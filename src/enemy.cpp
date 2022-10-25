#include <ctime>

#include "../include/enemy.h"
#include "../include/RustTypes.h"
#include "../include/enemy_codes.h"

// enemy

	Enemy::Enemy(i16 game_level,
				i16 room_pattern,
				i16 enemy_types) 
	{
		if (enemy_types == ENEMY_COMMON) {
			switch(game_level) {
				case 1:
					switch(room_pattern) {
						case 1:
							this -> number_of_enemies = 1;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_COMMON_BANDIT;
							this -> name[0] = const_cast<char*>("BANDIT");
							this -> type[0] = ENEMY_COMMON;
							this -> health_points[0] = 42 + (1 + rand() % 10);
							this -> battle_pattern[0] = 0;
							break;
						case 2:
							this -> number_of_enemies = 2;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_COMMON_BANDIT;
							this -> name[0] = const_cast<char*>("BANDIT");
							this -> type[0] = ENEMY_COMMON;
							this -> health_points[0] = 42 + (1 + rand() % 10);
							this -> battle_pattern[0] = 0;

							this -> id[1] = E_COMMON_SHOOTER;
							this -> name[1] = const_cast<char*>("SHOOTER");
							this -> type[1] = ENEMY_COMMON;
							this -> health_points[1] = 28 + (1 + rand() % 6);
							this -> battle_pattern[1] = 0;
							break;
						case 3:
							this -> number_of_enemies = 2;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_COMMON_BANDIT;
							this -> name[0] = const_cast<char*>("BANDIT");
							this -> type[0] = ENEMY_COMMON;
							this -> health_points[0] = 42 + (1 + rand() % 10);
							this -> battle_pattern[0] = 0;

							this -> id[1] = E_COMMON_BANDIT;
							this -> name[1] = const_cast<char*>("BANDIT");
							this -> type[1] = ENEMY_COMMON;
							this -> health_points[1] = 42 + (1 + rand() % 10);
							this -> battle_pattern[1] = 0;
							break;
						case 4:
							this -> number_of_enemies = 2;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_COMMON_SHOOTER;
							this -> name[0] = const_cast<char*>("SHOOTER");
							this -> type[0] = ENEMY_COMMON;
							this -> health_points[0] = 28 + (1 + rand() % 6);
							this -> battle_pattern[0] = 0;

							this -> id[1] = E_COMMON_SHOOTER;
							this -> name[1] = const_cast<char*>("SHOOTER");
							this -> type[1] = ENEMY_COMMON;
							this -> health_points[1] = 28 + (1 + rand() % 6);
							this -> battle_pattern[1] = 0;
							break;
						case 5:
							this -> number_of_enemies = 3;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_COMMON_BANDIT;
							this -> name[0] = const_cast<char*>("BANDIT");
							this -> type[0] = ENEMY_COMMON;
							this -> health_points[0] = 42 + (1 + rand() % 10);
							this -> battle_pattern[0] = 0;

							this -> id[1] = E_COMMON_SHOOTER;
							this -> name[1] = const_cast<char*>("SHOOTER");
							this -> type[1] = ENEMY_COMMON;
							this -> health_points[1] = 28 + (1 + rand() % 6);
							this -> battle_pattern[1] = 0;

							this -> id[2] = E_COMMON_SHOOTER;
							this -> name[2] = const_cast<char*>("SHOOTER");
							this -> type[2] = ENEMY_COMMON;
							this -> health_points[2] = 28 + (1 + rand() % 6);
							this -> battle_pattern[2] = 0;
							break;
						default:
							break;
					}
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				default:
					break;
			}
		}
		else if (enemy_types == ENEMY_ELITE) {
			switch(game_level) {
				case 1:
					switch(room_pattern) {
						case 1:
							this -> number_of_enemies = 1;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_ELITE_BEAST;
							this -> name[0] = const_cast<char*>("CYBER BEAST");
							this -> type[0] = ENEMY_ELITE;
							this -> health_points[0] = 75 + (1 + rand() % 10);
							this -> battle_pattern[0] = 0;
							break;
						case 2:
							this -> number_of_enemies = 3;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_ELITE_CASTER;
							this -> name[0] = const_cast<char*>("NET CASTER");
							this -> type[0] = ENEMY_ELITE;
							this -> health_points[0] = 35 + (1 + rand() % 5);
							this -> battle_pattern[0] = 0;

							this -> id[1] = E_ELITE_CASTER;
							this -> name[1] = const_cast<char*>("SHIELD GENERATOR");
							this -> type[1] = ENEMY_ELITE;
							this -> health_points[1] = 20;
							this -> battle_pattern[1] = 0;

							this -> id[2] = E_ELITE_CASTER_SHIELD_GENERATOR;
							this -> name[2] = const_cast<char*>("SHIELD GENERATOR");
							this -> type[2] = ENEMY_ELITE;
							this -> health_points[2] = 20;
							this -> battle_pattern[2] = 0;
							break;
						default:
							break;
					}
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				default:
					break;
			}
		}
		else if (enemy_types == ENEMY_BOSS) {
			switch(room_pattern) {
				case 1:
					switch(game_level) {
						case 1:
							this -> number_of_enemies = 1;

							this -> name.resize(number_of_enemies);
							this -> type.resize(number_of_enemies);
							this -> id.resize(number_of_enemies);
							this -> health_points.resize(number_of_enemies);
							this -> battle_pattern.resize(number_of_enemies);

							this -> id[0] = E_BOSS_ABADDON;
							this -> name[0] = const_cast<char*>("ABADDON");
							this -> type[0] = ENEMY_BOSS;
							this -> battle_pattern[0] = 0;

							switch(game_level) {
								case 1:
									this -> health_points[0] = 100;
									break;
								case 2:
									break;
								case 3:
									break;
								case 4:
									break;
								case 5:
									break;
								case 6:
									break;
								case 7:
									break;
								case 8:
									break;
								case 9:
									break;
								case 10:
									break;
								default:
									break;
							}
							break;
						case 2:
							break;
						case 3:
							break;
						case 4:
							break;
						case 5:
							break;
						case 6:
							break;
						case 7:
							break;
						case 8:
							break;
						case 9:
							break;
						case 10:
							break;
						default:
							break;
					}				
					break;
				default:
					break;
			}
		}
	}

	Enemy::~Enemy() {
	
	}