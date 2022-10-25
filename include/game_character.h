#pragma once

#include <vector>

#include "RustTypes.h"

using namespace std;

class GameHero {
	public:
		// character name
		// character id
		char *name;
		// 1 - knight
		i16 id;
		// the amount of memory (RAM)
		// that can be used to send data packets
		i16 memory_points;
		// health point
		i16 health_points;

		u16 number_of_cards;
		u16 hand_size;
		u16 max_hand_size;
		u16 turn_number;

		vector<u16> card_list;
		vector<u16> card_hand;
		vector<u16> dump_stack;
		vector<u16> card_stack;

		GameHero(i16);
		~GameHero();

		// shuffle card stack
		// true (default) - card_stack = dump_stack
		// false - card_stack = card_list
		void shufflingDeckOfCards(bool = true);
		// gettings card(s) from the deck in card hand
		// true - in the move
		// false - after the move
		void gettingsCardsFromTheDeck(bool = true);
		// reset card(s) from the card hand into dump stack
		// true - in the move
		// false - after the move
		void resetCardsIntoTheDumpStack(bool = true);
};