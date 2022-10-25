#include "../include/game_character.h"
#include "../include/RustTypes.h"
#include "../include/card_codes.h"

GameHero::GameHero(i16 character_id) {
	this -> id = character_id;
	this -> turn_number = 0;
	switch(this -> id) {
		// knight
		case 1: 
			this -> name = const_cast<char*>("Knight");
			this -> health_points = 100;
			this -> memory_points = 3;
			this -> number_of_cards = 10;
			this -> hand_size = 5;
			this -> max_hand_size = 10;
			this -> card_hand.resize(hand_size);
			this -> card_stack.resize(0);
			this -> dump_stack.resize(0);
			this -> card_list.resize(number_of_cards);
			// 0 - strike
			this -> card_list[0] = KNIGHT_STRIKE;
			this -> card_list[1] = KNIGHT_STRIKE;
			this -> card_list[2] = KNIGHT_STRIKE;
			this -> card_list[3] = KNIGHT_STRIKE;
			// 1 - defend
			this -> card_list[4] = KNIGHT_DEFEND;
			this -> card_list[5] = KNIGHT_DEFEND;
			this -> card_list[6] = KNIGHT_DEFEND;
			this -> card_list[7] = KNIGHT_DEFEND;
			// 2 - flaming sword strike
			this -> card_list[8] = KNIGHT_FLAMING_SWORD_STRIKE;
			this -> card_list[9] = KNIGHT_FLAMING_SWORD_STRIKE;
			break;	
		default:
			break;
	}
}

GameHero::~GameHero() {
	
}

void GameHero::shufflingDeckOfCards(bool dump_shuffle) {
	if(dump_shuffle) {
		this -> card_stack = this -> dump_stack;
		this -> dump_stack.resize(0);
	}
	else {
		this -> card_stack = this -> card_list;
	}

	for (i16 i = 0; i < this -> card_stack.size(); i++) {
		i16 tmp = this -> card_stack[i];
		i16 tmp_rand = (1 + rand() % this -> card_stack.size()) - 1;
		this -> card_stack[i] = this -> card_stack[tmp_rand];
		this -> card_stack[tmp_rand] = tmp;
	}
}

void GameHero::gettingsCardsFromTheDeck(bool in_move) {
	if (in_move) {
		
	}
	else {
		for (i16 i = 0; i < this -> hand_size; i++) {
			if(this -> card_stack.size() == 0) {
				this -> shufflingDeckOfCards();
			}
			
			this -> card_hand[i] = this -> card_stack.back();
			this -> card_stack.pop_back();
		}
	}
}

void GameHero::resetCardsIntoTheDumpStack(bool in_move) {
	if (in_move) {
		
	}
	else {
		for (i16 i = 0; i < this -> card_hand.size(); i++) {
			dump_stack.push_back(card_hand[i]);
		}
		card_hand.resize(0);
		card_hand.resize(this -> hand_size);
	}
}