#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "globals.h"

//This class is currently only expanded enough to support the guild screen display

class soldier{
public:
	//constructor will later take these parameters to specify an image
	//	for now, only primitives are needed to make sure the logic functions
	//soldiers(std::string name, int level, std::string class_image)
	soldier(std::string name, int level, CLASS soldier_class){
		soldier::name = name;
		soldier::level = level;
		soldier::soldier_class = soldier_class;
		//current_class = al_load_bitmap(class_image.c_str());
		//this will be in the final constructor, but not this one
	}
	~soldier(){
		if(current_class)
			al_destroy_bitmap(current_class);
	}
	
	std::string get_name() { return name; }
	int get_level() {return level; }
	CLASS get_soldier_class() {return soldier_class; }
	/*The following function will need to be passed pixel positions to be drawn because
	the soldier icon will be drawn different places in the list depending on how many
	soldiers the player has, what order he got them in, how they've been sorted, etc*/
	void draw_icon(int x, int y, ALLEGRO_FONT *font12){
		//draw a background square
		al_draw_filled_rectangle(x, y, x+128, y+128, al_map_rgb(255,255,255));
		al_draw_rectangle(x, y, x+128, y+128, al_map_rgb(0,0,255), 2);
		//draw the soldiers name
		al_draw_textf(font12, al_map_rgb(0,0,0), x+4, y+4, 0, "%s", name);
	}

private:
	std::string name;
	int level;
	ALLEGRO_BITMAP *current_class;
	CLASS soldier_class;
};
