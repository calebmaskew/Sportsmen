#pragma once

#include "globals.h"
#include "monster.h"
#include "battlescape.h"
#include "city.h";
#include "mission_descriptions.h"

int story_progression;	//int keeping up with how far along the vector of story missions the
						//the player has progressed; fed to the mission generation algorithm
						//to tell it which story mission to generate next

int weeks_until_next_story_mission;	//int keeping up with how many more weeks the player must
									//	get through in order to have a chance of generating
									//	the next story mission

int GOLD;				//player gold


//===================================================
//MASTER LISTS NEEDED BY THE MISSION GENERATOR
//===================================================

//biomes and their associated cities
std::vector<std::vector<CITY>> cities_by_biome;

//list of all monsters, battlescapes, story mission descriptions, and ordinary mission descriptions
std::map<std::string, monster> master_monster_list;
std::map<std::string, battlescape> master_battlescape_list;
std::map<std::string, mission_description> master_mission_description_list;
std::vector<mission_description> master_story_mission_description_list;
