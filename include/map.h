#pragma once

#include <string>

#include "RustTypes.h"

using namespace std;

class GameLevel {
	public:
		// level size <= 9
		i16 size;
		// game level number
		i16 level;
		// level map (size x size)
		//	   -1 - empty room
		//		0 - start room
		//		1 - battle room
		//		2 - boss fight room
		//		3 - entry to the next level
		i16 **map;
		// level map in interface
		string **map_masc;

		GameLevel(i16);
		~GameLevel();
		
		// generator levels
		void generateLevel(); 
};