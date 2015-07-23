#include "mission_gen.h"

mission_gen::mission_gen(const std::vector<mission_description> &story_missions){
	mission_gen::story_missions = story_missions;
}

std::vector<mission> mission_gen::generate(int &weeks_until_next_mission, int &story_progression,
	const std::vector<std::vector<CITY>> &cities_by_biome, std::map<std::string, battlescape> &battlescapes,
	std::map<std::string, monster> &monster_list, std::map<std::string, mission_description> &mission_descriptions){

	std::vector<mission> mission_list;		//keeps up with the missions that have currently been generated
	std::string description;				//reassigns itself to hold the description of the mission being generated
	std::vector<DIFFICULTY> valid_diffs;	//keeps up with what difficulties can be chosen for this mission
	std::vector<BIOME> valid_biomes;		//keeps up with what biomes can be chosen for this mission
	std::string cur_id = "mission";
	std::vector<battlescape> valid_battlescapes;	//vector keeping up with what battlescapes can be chosen
	std::vector<monster> invalid_monsters;	//monsters that cannot be chosen for mission
	std::list<monster> mission_monsters;	//monsters already chosen for mission

	//values keeping up with how many of each mission should be generated this week
	//these values obviously subject to change as we proceed with playtesting
	int num_easy;
	int num_med;
	int num_hard;
	int num_brutal;

	if(story_progression == 0){
		num_easy = 2;
		num_med = 0;
		num_hard = 0;
		num_brutal = 0;
	}
	else if(story_progression == 1){
		num_easy = 1;
		num_med = 1;
		num_hard = 0;
		num_brutal = 0;
	}
	else if(story_progression == 2){
		num_easy = 3;
		num_med = 0;
		num_hard = 0;
		num_brutal = 0;
	}

	//set the total number of missions needed to be generated for the week
	int num_missions = num_easy + num_med + num_hard;


	bool available_biomes[8] = {true, true, true, true, true, true, true, true};	
					//array keeping up with which biomes haven't been used yet; at least
					//for now, no biome can have more than one mission a week, and a biome
					//currently assigned no mission will be true or available
	bool available_diffs[4];
					//array keeping up with which difficulties haven't been used yet;
					//these values are dependent on how many of each difficulty of 
					//mission are to be generated this week
	if(num_easy > 0)
		available_diffs[EASY] = true;
	if(num_med > 0)
		available_diffs[MEDIUM] = true;
	if(num_hard > 0)
		available_diffs[HARD] = true;
	if(num_brutal > 0)
		available_diffs[BRUTAL] = true;

	mission cur_mission;

	srand(unsigned(time(NULL)));

	std::cout << "Current story progression: " << story_progression << std::endl;
	
	//first, check to see if the game needs to try to generate the next story mission
	if(weeks_until_next_mission == 0){
		int num = (rand()%100) + 1;
		//for testing purposes, missions have a 33% chance of being generated
		if(num < 101){
			std::cout << "We are producing a story mission\n";
			//GENERATE THE NEXT STORY MISSION
			//story mission will be first in the list
			cur_mission.set_id("story");
			//grab the description from the story mission
			description = story_missions[story_progression].get_description();
			cur_mission.set_description(description);
			//look at all the mission's valid difficulties and populate the vector from them
			//throw this in a function
			if(story_missions[story_progression].difficulties[EASY] == true && num_easy > 0) valid_diffs.push_back(EASY);
			if(story_missions[story_progression].difficulties[MEDIUM] == true && num_med > 0) valid_diffs.push_back(MEDIUM);
			if(story_missions[story_progression].difficulties[HARD] == true && num_hard > 0) valid_diffs.push_back(HARD);
			if(story_missions[story_progression].difficulties[BRUTAL] == true && num_brutal > 0) valid_diffs.push_back(BRUTAL);
			//randomly choose one of the diffs from the vector and assign it to the mission
			int rand_choice = rand()%valid_diffs.size();
			cur_mission.set_diff(valid_diffs[rand_choice]);
			//decrement the count of the corresponding mission difficulty
			if(valid_diffs[rand_choice] == EASY) num_easy--;
			if(valid_diffs[rand_choice] == MEDIUM) num_med--;
			if(valid_diffs[rand_choice] == HARD) num_hard--;
			if(valid_diffs[rand_choice] == BRUTAL) num_brutal--;
			//if no more missions of a certain difficulty can be generated, the algorithm needs to know so
			if(num_easy == 0) available_diffs[EASY] = false;
			if(num_med == 0) available_diffs[MEDIUM] = false;
			if(num_hard == 0) available_diffs[HARD] = false;
			if(num_brutal == 0) available_diffs[BRUTAL] = false;

			//look at the missions valid biomes and populate the vector from them
			//throw this in a function
			if(story_missions[story_progression].biomes[FOREST]==true && available_biomes[FOREST]==true) valid_biomes.push_back(FOREST);
			if(story_missions[story_progression].biomes[TUNDRA]==true && available_biomes[TUNDRA]==true) valid_biomes.push_back(TUNDRA);
			if(story_missions[story_progression].biomes[JUNGLE]==true && available_biomes[JUNGLE]==true) valid_biomes.push_back(JUNGLE);
			if(story_missions[story_progression].biomes[SWAMP]==true && available_biomes[SWAMP]==true) valid_biomes.push_back(SWAMP);
			if(story_missions[story_progression].biomes[COAST]==true && available_biomes[COAST]==true) valid_biomes.push_back(COAST);
			if(story_missions[story_progression].biomes[NECROZONE]==true && available_biomes[NECROZONE]==true) valid_biomes.push_back(NECROZONE);
			if(story_missions[story_progression].biomes[DESERT]==true && available_biomes[DESERT]==true) valid_biomes.push_back(DESERT);
			if(story_missions[story_progression].biomes[VOLCANO]==true && available_biomes[VOLCANO]==true) valid_biomes.push_back(VOLCANO);
			rand_choice = rand()%valid_biomes.size();
			cur_mission.set_biome(valid_biomes[rand_choice]);
			available_biomes[valid_biomes[rand_choice]] = false;

			std::cout << "We chose a biome\n";

			//assign a city from the mission's biome if one is not specified in description
			if(story_missions[story_progression].get_custom_city() != NOCITY)
				cur_mission.set_city(story_missions[story_progression].get_custom_city());
			else{	//no city is assigned, scroll through the available cities for the biome and pick one
				rand_choice = rand()%cities_by_biome[cur_mission.get_biome()].size();
				//note that there is no bool array for cities, allowing multiple mmissions per city per week
				cur_mission.set_city(cities_by_biome[cur_mission.get_biome()][rand_choice]);
			}

			std::cout << "We chose an appropriate city\n";

			//assign the point value for the mission from default value if not defined by description
			int points;
			if(story_missions[story_progression].get_point_value() != -1)
				points = story_missions[story_progression].get_point_value();
			else points = def_point_values[cur_mission.get_diff()];

			//assign the gold reward from the default value if not defined by description
			if(story_missions[story_progression].get_gold() != -1)
				cur_mission.set_gold(story_missions[story_progression].get_gold());
			else cur_mission.set_gold(def_gold[cur_mission.get_diff()]);

			//assign the reputation gain from the default value if not defined by description
			if(story_missions[story_progression].get_rep_gain() != -1)
				cur_mission.set_rep_gain(story_missions[story_progression].get_rep_gain());
			else cur_mission.set_rep_gain(def_rep_gains[cur_mission.get_diff()]);

			//assign the reputation loss from the default value if not defined by description
			if(story_missions[story_progression].get_rep_loss() != 1)
				cur_mission.set_rep_loss(story_missions[story_progression].get_rep_loss());
			else cur_mission.set_rep_loss(def_rep_loss[cur_mission.get_diff()]);

			//assign the battlescape from the description if defined, otherwise choose one randomly from biome
			if(story_missions[story_progression].get_battlescape().get_id() != "None")
				cur_mission.set_battlescape(story_missions[story_progression].get_battlescape());
			else{	//otherwise choose a battlescape randomly from the available biome battlescapes
				//iterate through the list of battlescapes and add the ones that fit the mission's biome
				//to the list of valid battlescapes
				std::map<std::string, battlescape>::iterator it;
				for(it = battlescapes.begin(); it != battlescapes.end(); ++it){
					if((*it).second.get_biome() == cur_mission.get_biome())
						valid_battlescapes.push_back((*it).second);
				}
				//choose available battlescape at random
				rand_choice = rand()%valid_battlescapes.size();
				cur_mission.set_battlescape(valid_battlescapes[rand_choice]);
			}

			std::cout << "Set default values if applicable as well as biome\n";

			//first, if the mission has a list of valid monsters, copy those over
			if(story_missions[story_progression].get_valid_monsters().size() != 0){
				for(unsigned int i=0; i<story_missions[story_progression].get_valid_monsters().size(); i++)
					available_monsters.push_back(story_missions[story_progression].get_valid_monsters()[i]);
			}
			else{	//otherwise, generate a list of valid monsters based on biome and difficulty
				//update the valid monsters list with monsters from the appropriate biome, not on the
				//	mission description's invalid monsters list, and with a difficulty equal or lower than
				//  the currently defined mission difficulty

				//populate the invalid monsters list
				for(unsigned int i=0; i<story_missions[story_progression].get_invalid_monsters().size(); i++)
					invalid_monsters.push_back(story_missions[story_progression].get_invalid_monsters()[i]);

				//iterate through the master monster list and add all monsters meeting pre-defined criteria
				//	into the vector of valid monsters
				std::map<std::string, monster>::iterator it = monster_list.begin();
				std::vector<monster>::iterator it2;
				for(it; it!=monster_list.end(); ++it){
					//check to see if the monster is in the invalid monsters list
					it2 = invalid_monsters.begin();
					for(it2; it2!=invalid_monsters.end(); ++it2){
						if((*it2).get_id() == (*it).second.get_id()) break;
					}												//will stop the iterator on the monster
																	//if it is in the invalid list; otherwise
																	//the iterator will reach the end of list
					if(it2 == invalid_monsters.end()){
						if((*it).second.get_diff() <= cur_mission.get_diff() &&
							(*it).second.get_biome() == cur_mission.get_biome())
							available_monsters.push_back((*it).second);
					}
				}

				std::list<monster>::iterator it3 = available_monsters.begin();
				/*for(it3; it3!=available_monsters.end(); ++it3)
					std::cout << '\t' << (*it3).get_id() << std::endl;*/

				//initial lowest points set to the first monster in the available list
				it3 = available_monsters.begin();
				int lowest_monster_cost = (*it3).get_points();
				for(it3; it3 != available_monsters.end(); ++it3){
					if((*it3).get_points() < lowest_monster_cost)
						lowest_monster_cost = (*it3).get_points();
				}

				//loop grabbing monsters from list
				while(lowest_monster_cost <= points){
					//grab a random monster from available monsters to add to the mission
					rand_choice = rand()%available_monsters.size();
					it3 = available_monsters.begin();
					for(int i=0; i<rand_choice; i++){
						++it3;
					}
					//add the randomly selected monster
					mission_monsters.push_back(*it3);
					//reduce the available points for the mission by the cost of the monster
					points -= (*it3).get_points();
					//remove any monsters who cost more than the remaining points
					for(it3 = available_monsters.begin(); it3 != available_monsters.end(); /*++it3*/){
						if((*it3).get_points() > points){
							it3 = available_monsters.erase(it3);
						}
						else ++it3;
					}
				}
			}

			std::list<monster>::iterator it3;
			for(it3 = mission_monsters.begin(); it3!=mission_monsters.end(); ++it3)
				cur_mission.add_monster(*it3);

			//personalize the description of the mission to correct (city) and (biome)
			description = cur_mission.get_description();
			std::string personal_city = city_names[cur_mission.get_city()];
			std::string personal_biome = biome_names[cur_mission.get_biome()];
			while(description.find("(city)") != std::string::npos)
				description.replace(description.find("(city)"), 6, personal_city);
			while(description.find("(biome)") != std::string::npos)
				description.replace(description.find("(biome)"), 7, personal_biome);

			cur_mission.set_description(description);

			//finally, add mission to this week's mission vector
			mission_list.push_back(cur_mission);

			//note that during the actual game the following values would only increment upon story mission completion
			weeks_until_next_mission = story_missions[story_progression].get_next_mission_available();
			story_progression++;

			//decrement the missions count
			num_missions--;

			std::cout << "Story mission generation processed successfully\n";

		}
	}

	while(num_missions>0){

		std::cout << "Generating a non-story mission\n";
	
		//clear all vectors
		valid_battlescapes.clear();
		mission_monsters.clear();
		invalid_monsters.clear();
		valid_diffs.clear();
		valid_biomes.clear();
		cur_mission.clear_monsters();

		//generate random number less than the number of random missions
		int rand_choice = rand()%mission_descriptions.size();;
		std::map<std::string, mission_description>::iterator it = mission_descriptions.begin();
		//iterate through random missions until that mission is reached
		for(int i=0; i<rand_choice; i++){
			++it;
		}
		mission_description misdescrip = (*it).second;

		//check the biomes for the chosen mission and make sure one of them is still available
		bool good_biome = false;
		for(int i=0; i<8; i++){
			if(misdescrip.biomes[i] == true && available_biomes[i] == true){
				good_biome = true;
			}
		}
		//check the difficulties for the chosen mission and make sure one of them is available
		bool good_diff = false;
		for(int i=0; i<4; i++){
			if(misdescrip.difficulties[i] == true && available_diffs[i] == true){
				good_diff = true;
			}
		}

		//while the mission generated isn't good, generate new ones and check them
		while(good_biome == false || good_diff == false){
			rand_choice = rand()%mission_descriptions.size();
			it = mission_descriptions.begin();
			for(int i=0; i<rand_choice; i++){
				++it;
			}
			misdescrip = (*it).second;
			for(int i=0; i<8; i++){
				if(misdescrip.biomes[i] == true && available_biomes[i] == true)
					good_biome = true;
			}
			for(int i=0; i<4; i++){
				if(misdescrip.difficulties[i] == true && available_diffs[i] == true)
					good_diff = true;
			}
		}

		//set the mission id
		cur_mission.set_id("mission");

		//set the mission description
		cur_mission.set_description(misdescrip.get_description());

		/*	Work out new solution for checking difficulty while also considering
			the number of each difficulty mission to generate*/
		//look at all the mission's valid difficulties and populate the vector from them
		//throw this in a function
		if(misdescrip.difficulties[EASY] == true && available_diffs[EASY] == true) valid_diffs.push_back(EASY);
		if(misdescrip.difficulties[MEDIUM] == true && available_diffs[MEDIUM] == true) valid_diffs.push_back(MEDIUM);
		if(misdescrip.difficulties[HARD] == true && available_diffs[HARD] == true) valid_diffs.push_back(HARD);
		if(misdescrip.difficulties[BRUTAL] == true && available_diffs[BRUTAL] == true) valid_diffs.push_back(BRUTAL);

		//randomly choose one of the diffs from the vector and assign it to the mission
		rand_choice = rand()%valid_diffs.size();
		cur_mission.set_diff(valid_diffs[rand_choice]);
		//decrement the count of the corresponding mission difficulty
		if(valid_diffs[rand_choice] == EASY) num_easy--;
		if(valid_diffs[rand_choice] == MEDIUM) num_med--;
		if(valid_diffs[rand_choice] == HARD) num_hard--;
		if(valid_diffs[rand_choice] == BRUTAL) num_brutal--;
		//if no more missions of a certain difficulty can be generated, the algorithm needs to know so
		if(num_easy == 0) available_diffs[EASY] = false;
		if(num_med == 0) available_diffs[MEDIUM] = false;
		if(num_hard == 0) available_diffs[HARD] = false;
		if(num_brutal == 0) available_diffs[BRUTAL] = false;

		//look at the missions valid biomes and populate the vector from them
		//throw this in a function
		if(misdescrip.biomes[FOREST]==true && available_biomes[FOREST]==true) valid_biomes.push_back(FOREST);
		if(misdescrip.biomes[TUNDRA]==true && available_biomes[TUNDRA]==true) valid_biomes.push_back(TUNDRA);
		if(misdescrip.biomes[JUNGLE]==true && available_biomes[JUNGLE]==true) valid_biomes.push_back(JUNGLE);
		if(misdescrip.biomes[SWAMP]==true && available_biomes[SWAMP]==true) valid_biomes.push_back(SWAMP);
		if(misdescrip.biomes[COAST]==true && available_biomes[COAST]==true) valid_biomes.push_back(COAST);
		if(misdescrip.biomes[NECROZONE]==true && available_biomes[NECROZONE]==true) valid_biomes.push_back(NECROZONE);
		if(misdescrip.biomes[DESERT]==true && available_biomes[DESERT]==true) valid_biomes.push_back(DESERT);
		if(misdescrip.biomes[VOLCANO]==true && available_biomes[VOLCANO]==true) valid_biomes.push_back(VOLCANO);

		//randomly select a biome from the list of valid biomes and assign it to mission
		rand_choice = rand()%valid_biomes.size();
		cur_mission.set_biome(valid_biomes[rand_choice]);
		available_biomes[valid_biomes[rand_choice]] = false;

		//assign a city from the mission's biome if one is not specified in description
		if(misdescrip.get_custom_city() != NOCITY)
			cur_mission.set_city(misdescrip.get_custom_city());
		else{	//no city is assigned, scroll through the available cities for the biome and pick one
			rand_choice = rand()%cities_by_biome[cur_mission.get_biome()].size();
			//note that there is no bool array for cities, allowing multiple mmissions per city per week
			cur_mission.set_city(cities_by_biome[cur_mission.get_biome()][rand_choice]);
		}

		//assign the point value for the mission from default value if not defined by description
		int points;
		if(misdescrip.get_point_value() != -1)
			points = misdescrip.get_point_value();
		else points = def_point_values[cur_mission.get_diff()];
			
		//assign the gold reward from the default value if not defined by description
		if(misdescrip.get_gold() != -1)
			cur_mission.set_gold(misdescrip.get_gold());
		else cur_mission.set_gold(def_gold[cur_mission.get_diff()]);

		//assign the reputation gain from the default value if not defined by description
		if(misdescrip.get_rep_gain() != -1)
			cur_mission.set_rep_gain(misdescrip.get_rep_gain());
		else cur_mission.set_rep_gain(def_rep_gains[cur_mission.get_diff()]);

		//assign the reputation loss from the default value if not defined by description
		if(misdescrip.get_rep_loss() != 1)
			cur_mission.set_rep_loss(misdescrip.get_rep_loss());
		else cur_mission.set_rep_loss(def_rep_loss[cur_mission.get_diff()]);

		//assign the battlescape from the description if defined, otherwise choose one randomly from biome
		if(misdescrip.get_battlescape().get_id() != "None")
			cur_mission.set_battlescape(misdescrip.get_battlescape());
		else{	//otherwise choose a battlescape randomly from the available biome battlescapes
			//iterate through the list of battlescapes and add the ones that fit the mission's biome
			//to the list of valid battlescapes
			std::map<std::string, battlescape>::iterator it;
			for(it = battlescapes.begin(); it != battlescapes.end(); ++it){
				if((*it).second.get_biome() == cur_mission.get_biome())
					valid_battlescapes.push_back((*it).second);
			}
			//choose available battlescape at random
			rand_choice = rand()%valid_battlescapes.size();
			cur_mission.set_battlescape(valid_battlescapes[rand_choice]);
		}

		//first, if the mission has a list of valid monsters, copy those over
		if(misdescrip.get_valid_monsters().size() != 0){
			std::vector<monster> copied = misdescrip.get_valid_monsters();
			for(unsigned int i=0; i<copied.size(); i++)
				available_monsters.push_back(copied[i]);
		}
		else{	//otherwise, generate a list of valid monsters based on biome and difficulty
			//update the valid monsters list with monsters from the appropriate biome, not on the
			//	mission description's invalid monsters list, and with a difficulty equal or lower than
			//  the currently defined mission difficulty

			//populate the invalid monsters list
			for(unsigned int i=0; i<misdescrip.get_invalid_monsters().size(); i++)
				invalid_monsters.push_back(misdescrip.get_invalid_monsters()[i]);

			//iterate through the master monster list and add all monsters meeting pre-defined criteria
			//	into the vector of valid monsters
			std::map<std::string, monster>::iterator it = monster_list.begin();
			std::vector<monster>::iterator it2;
			for(it; it!=monster_list.end(); ++it){
				//check to see if the monster is in the invalid monsters list
				it2 = invalid_monsters.begin();
				for(it2; it2!=invalid_monsters.end(); ++it2){
					if((*it2).get_id() == (*it).second.get_id()) break;
				}												//will stop the iterator on the monster
																//if it is in the invalid list; otherwise
																//the iterator will reach the end of list
				if(it2 == invalid_monsters.end()){
					if((*it).second.get_diff() <= cur_mission.get_diff() &&
						(*it).second.get_biome() == cur_mission.get_biome())
						available_monsters.push_back((*it).second);
				}
			}
		}

		//initial lowest points set to the first monster in the available list
		std::list<monster>::iterator it3 = available_monsters.begin();
		int lowest_monster_cost = (*it3).get_points();
		for(it3; it3 != available_monsters.end(); ++it3){
			if((*it3).get_points() < lowest_monster_cost)
				lowest_monster_cost = (*it3).get_points();
		}

		//loop grabbing monsters from list
		while(lowest_monster_cost <= points){
			//grab a random monster from available monsters to add to the mission
			rand_choice = rand()%available_monsters.size();
			it3 = available_monsters.begin();
			for(int i=0; i<rand_choice; i++){
				++it3;
			}
			//add the randomly selected monster
			mission_monsters.push_back(*it3);
			//reduce the available points for the mission by the cost of the monster
			points -= (*it3).get_points();
			//remove any monsters who cost more than the remaining points
			for(it3 = available_monsters.begin(); it3 != available_monsters.end(); /*++it3*/){
				if((*it3).get_points() > points){
					it3 = available_monsters.erase(it3);
				}
				else ++it3;
			}
		}

		//std::list<monster>::iterator it3;
		for(it3 = mission_monsters.begin(); it3!=mission_monsters.end(); ++it3)
			cur_mission.add_monster(*it3);

		description = cur_mission.get_description();
		std::string personal_city = city_names[cur_mission.get_city()];
		std::string personal_biome = biome_names[cur_mission.get_biome()];
		while(description.find("(city)") != std::string::npos)
			description.replace(description.find("(city)"), 6, personal_city);
		while(description.find("(biome)") != std::string::npos)
			description.replace(description.find("(biome)"), 7, personal_biome);

		cur_mission.set_description(description);

		//finally, add mission to this week's mission vector
		mission_list.push_back(cur_mission);
		num_missions--;
	}

	return mission_list;
}

std::string personalize_descrip(std::string descrip, std::string associated_city, std::string associated_biome){
	std::string s = descrip;
	//replace all instances of (city) with the associated city for the mission in the mission's description
	while(s.find("(city)") != std::string::npos)
		s.replace(s.find("(city)"), 6, associated_city);

	//replace all instances of (biome) in the mission's description with the missin's associated biome
	while(s.find("(biome)") != std::string::npos)
		s.replace(s.find("(biome)"), 7, associated_biome);

	return s;
}
