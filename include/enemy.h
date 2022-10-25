#pragma once

#include <vector>

#include "RustTypes.h"

using namespace std;

class Enemy {
	public:
		vector<char*> name;
		vector<i16> type;
		vector<i16> id;
		vector<i16> health_points;
		vector<i16> battle_pattern;
		u16 number_of_enemies;

		Enemy() {};
		Enemy(i16, i16, i16);
		~Enemy();
		
		void battleSystem();
		void attack();
		void defence();
		void skill_one();
		void skill_two();
};