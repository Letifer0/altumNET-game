#include <fstream>

#include "../include/settings.h"

Settings::Settings() {
	CS_FIRST_COLOR = 12; 
	// light-blue
	CS_SECOND_COLOR = 11; 
	// white
	CS_COMMON_RARITY_COLOR = 7;
	// light-green
	CS_RARE_RARITY_COLOR = 10;
	// light-pirple
	CS_EPIC_RARITY_COLOR = 13;
	// light-yellow
	CS_LEGENDARY_RARITY_COLOR = 14;
	// light-dark-blue
	CS_MYTHICAL_RARITY_COLOR = 9;
}

Settings::~Settings() {
	
}