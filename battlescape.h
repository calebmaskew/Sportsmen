#pragma once

#include "globals.h"

class battlescape{
public:
	battlescape(){id = "None"; }
	battlescape(std::string id, BIOME valid_biome){
		battlescape::valid_biome = valid_biome;
		battlescape::id = id;
	}
	std::string get_id() {return id; }
	BIOME get_biome() {return valid_biome; }

	void set_id(std::string id) {battlescape::id = id; }
private:
	BIOME valid_biome;
	std::string id;
};
