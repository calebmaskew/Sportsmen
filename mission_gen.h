#pragma once

#include "globals.h"
#include "mission_descriptions.h"
#include "mission.h"

class mission_gen{
public:
	mission_gen(const std::vector<mission_description> &story_missions);
	std::string personalize_descrip(std::string, std::string, std::string);
	std::vector<mission> generate(int &weeks_until_next_mission, int &story_progression,
		const std::vector<std::vector<CITY>> &cities_by_biome, std::map<std::string, battlescape> &battlescapes,
		std::map<std::string, monster> & monster_list, std::map<std::string, mission_description> &mission_descriptions);
private:
	BIOME biomes[8];	//keeps up with what biomes can still hold missions
	CITY cities[8];		//keeps up with cities that can still associate with missions
	std::vector<mission> mission_list;
	std::list<monster> available_monsters;
	int num_missions;	//int keeping up with how many missions to generate this week
	std::vector<mission_description> story_missions;	//game's story IN ORDER
};
