//=======================================================
//Global enumerators used by multiple functions
//=======================================================

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

//game states
enum STATE{MAIN_MENU, MAP, GUILD, BATTLE, LOAD,
			LOAD_MENU, NEW_GAME};

//difficulty, biome, and city enumerations
enum DIFFICULTY{EASY, MEDIUM, HARD, BRUTAL};
enum BIOME{FOREST, COAST, JUNGLE, SWAMP, NECROZONE, DESERT, TUNDRA, VOLCANO};
enum CITY{CITY1, CITY2, CITY3, CITY4, CITY5, CITY6,  NOCITY};

//soldier classes
enum CLASS{BASTION, ARTILLATOR, DISTORTER, CHAPLAIN};

//arrays keeping up with the biome and city names for the map screen
const std::string city_names[7] = {"Anyd", "Tullav", "Wrotridge", "Cissel", "Adanicus", "Repha", "NoCity"};
const std::string biome_names[8] = {"forest", "coast", "jungle", "swamp", "corrupted lands", "desert", "tundra", "volcano"};

//array with default gold values by difficulty
const int def_gold[4] = {1000, 2000, 3000, 4000};
//array with default point values by difficulty
const int def_point_values[4] = {250, 500, 750, 1000};
//array with default reputation rewards by difficulty
const int def_rep_gains[4] = {10, 20, 30, 40};
//array with default reputation losses by difficulty
const int def_rep_loss[4] = {2, 5, 10, 15};
