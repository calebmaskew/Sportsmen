#pragma once

#include "globals.h"
#include "monster.h"
#include "battlescape.h"

class mission_description{
public:
	mission_description(std::string description, CITY city = NOCITY, int gold = -1, int rep_gain = -1,
		int rep_loss = 1, int points = -1, int next_available = -1);
	std::vector<monster> get_valid_monsters() {return valid_monsters; }
	std::vector<monster> get_invalid_monsters() {return invalid_monsters; }
	std::vector<monster> get_custom_monsters() {return custom_monsters; }
	int get_gold() {return custom_gold; }
	int get_rep_gain() {return custom_rep_gain; }
	int get_rep_loss() {return custom_rep_loss; }
	int get_point_value() {return custom_point_value; }
	CITY get_custom_city() {return custom_city; }
	battlescape get_battlescape() {return custom_battlescape; }
	std::string get_description() {return description; }
	int get_next_mission_available() {return next_story_mission_available; }

	bool biomes[8];
	bool difficulties[4];

	void make_biome_valid(BIOME biome) { biomes[biome] = true; }
	void make_all_biomes_valid();
	void make_monster_valid(monster new_valid_monster);
	void set_battlescape(battlescape custom);
	void set_difficulty_valid(DIFFICULTY diff) { difficulties[diff] = true; }
	void set_basic_difficulties_valid();	//sets easy, medium, and hard valid diffs
	void make_monster_invalid(monster new_invalid_monster);
	void set_custom_monster(monster new_monster);
	void show_info();
private:
	std::string description;
	std::vector<monster> valid_monsters;
	std::vector<monster> invalid_monsters;
	std::vector<monster> custom_monsters;
	CITY custom_city;
	int custom_gold;
	int custom_rep_gain;
	int custom_rep_loss;
	int custom_point_value;
	battlescape custom_battlescape;
	int next_story_mission_available;	//int stating how many weeks must pass
										//before the next story mission has a
										//chance to appear
};
