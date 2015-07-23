#pragma once

#include "globals.h"

class monster{
public:
	monster(std::string id, int point_value, DIFFICULTY diff, BIOME biome){
		monster::point_value = point_value;
		monster::diff = diff;
		monster::biome = biome;
		monster::id = id;
	}
	int get_points() { return point_value; }
	DIFFICULTY get_diff() { return diff; }
	BIOME get_biome() {return biome; }
	std::string get_id() {return id; }
	void show_info(){
		std::cout << "Name: " << id << std::endl;
		std::cout << "Points: " << point_value << std::endl;
		std::cout << "Difficulty: " << diff << std::endl;
		std::cout << "Biome: " << biome << std::endl;
	}
private:
	int point_value;
	DIFFICULTY diff;
	BIOME biome;
	std::string id;
};
