#include "mission_descriptions.h"

mission_description::mission_description(std::string description, CITY city, int gold,
	int rep_gain, int rep_loss, int points, int next_available){
		mission_description::description = description;
		custom_city = city;
		custom_gold = gold;
		custom_rep_gain = rep_gain;
		custom_rep_loss = rep_loss;
		custom_point_value = points;
		next_story_mission_available = next_available;
		//a default id must be set by battlescape to tell whether or not it is actually defined
		custom_battlescape.set_id("None");
		//finding it difficult to initialize the boolean arrays to all false;
		//the compiler should do it for me, however, test to find out
}

void mission_description::make_all_biomes_valid() {
	biomes[FOREST] = true;
	biomes[COAST] = true;
	biomes[JUNGLE] = true;
	biomes[NECROZONE] = true;
	biomes[TUNDRA] = true;
	biomes[DESERT] = true;
	biomes[SWAMP] = true;
	//note this function does not make the volcanic biome valid;
	//that should be done on a per-mission basis as the majority of the
	//game's missions will not take place in the volcanic biome
}

void mission_description::make_monster_valid(monster new_valid_monster){
	valid_monsters.push_back(new_valid_monster);	
}

void mission_description::make_monster_invalid(monster new_invalid_monster){
	invalid_monsters.push_back(new_invalid_monster);
}

void mission_description::set_battlescape(battlescape custom){
	custom_battlescape = custom;
}

void mission_description::set_basic_difficulties_valid(){
	difficulties[EASY] = true;
	difficulties[MEDIUM] = true;
	difficulties[HARD] = true;
}

void mission_description::set_custom_monster(monster new_monster){
	custom_monsters.push_back(new_monster);
}

void mission_description::show_info(){
	std::cout << "Description: " << description << std::endl;
	std::cout << "Associated City: " << custom_city << std::endl;
	std::cout << "Gold Earned: " << custom_gold << std::endl;
	std::cout << "Reputation Gain: " << custom_rep_gain << std::endl;
	std::cout << "Reputation Loss: " << custom_rep_loss << std::endl;
	std::cout << "Mission Point Value: " << custom_point_value << std::endl;
	if(custom_battlescape.get_id() != "None")
		std::cout << "Battlescape: " << custom_battlescape.get_id() << std::endl;
	else std::cout << "Battlescape: No battlescape defined" << std::endl;
	std::cout << "Next Story Mission Available in " << next_story_mission_available << " weeks\n";
	std::cout << "Valid Biomes: ";
	for(int i=0; i<8; i++)
		if(biomes[i] == true)
			std::cout << i << " ";
	std::cout << std::endl;
	std::cout << "Valid Difficulties: ";
	for(int i=0; i<4; i++)
		if(difficulties[i] == true)
			std::cout << i << " ";
	std::cout << std::endl;
	std::cout << "Valid Monsters: ";
	if(valid_monsters.size() == 0)
		std::cout << "All\n";
	else{
		std::cout << std::endl;
		for(unsigned int i=0; i<valid_monsters.size(); i++){
			std::cout << '\t' << valid_monsters[i].get_id() << std::endl;
		}
	}
	std::cout << "Invalid Monsters: ";
	if(invalid_monsters.size() == 0)
		std::cout << "None\n";
	else{
		std::cout << std::endl;
		for(unsigned int i=0; i<invalid_monsters.size(); i++)
			std::cout << '\t' << invalid_monsters[i].get_id() << std::endl;
	}
	std::cout << "Monsters Guaranteed to be in this Mission: ";
	if(custom_monsters.size() == 0)
		std::cout << "None Specified\n";
	else{
		std::cout << std::endl;
		for(unsigned int i=0; i<custom_monsters.size(); i++)
			std::cout << '\t' << custom_monsters[i].get_id() << std::endl;
		std::cout << std::endl;
	}
}
