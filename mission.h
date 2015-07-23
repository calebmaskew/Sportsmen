#pragma once

#include "battlescape.h"
#include "monster.h"
#include "globals.h"

class mission{
public:
	mission(){}
	//accessors
	std::string get_id() {return id; }
	std::string get_description() {return description; }
	std::vector<monster> get_monsters() {return mission_monsters; }
	battlescape get_battlescape() {return mission_battlescape; }
	BIOME get_biome() {return biome; }
	CITY get_city() {return associated_city; }
	DIFFICULTY get_diff() {return diff; }
	int get_gold() {return gold; }
	int get_rep_gain() {return rep_gain; }
	int get_rep_loss() {return rep_loss; }

	//mutators
	void set_id(std::string id) {mission::id = id; }
	void set_description(std::string description) {mission::description = description; }
	void add_monster(monster new_monster) {mission_monsters.push_back(new_monster); }
	void set_battlescape(battlescape new_battlescape) {mission::mission_battlescape = new_battlescape; }
	void set_biome(BIOME biome) {mission::biome = biome; }
	void set_city(CITY city) {mission::associated_city = city; }
	void set_diff(DIFFICULTY diff) {mission::diff = diff; }
	void set_gold(int gold) {mission::gold = gold; }
	void set_rep_gain(int rep_gain) {mission::rep_gain = rep_gain; }
	void set_rep_loss(int rep_loss) {mission::rep_loss = rep_loss; }
	void clear_monsters() {mission_monsters.clear(); }

	//testing purposes
	void show_info(){
		std::cout << "ID: " << id << "\n";
		std::cout << "Description: " << description << "\n";
		std::cout << "Battlescape: " << mission_battlescape.get_id() << "\n";
		std::cout << "Biome: " << biome << "\n";
		std::cout << "Associated City: " << associated_city << "\n";
		std::cout << "Difficulty: " << diff << "\n";
		std::cout << "Gold Reward: " << gold << "\n";
		std::cout << "Reputation Gain with City: " << rep_gain << "\n";
		std::cout << "Reputation Loss with City: " << rep_loss << "\n";
		for(unsigned int i=0; i<mission_monsters.size(); i++)
			std::cout << "\t" << mission_monsters[i].get_id() << std::endl;
		std::cout << std::endl;
	}

private:
	//all of the following elements are required for the mission to
	//be a valid mission.  They will have to be set individually by the
	//mutator functions because the generator sets them one at a time
	std::string id;
	std::string description;
	std::vector<monster> mission_monsters;
	battlescape mission_battlescape;
	BIOME biome;
	CITY associated_city;
	DIFFICULTY diff;
	int gold;
	int rep_gain;
	int rep_loss;

};
