#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>
#include <list>

#include "globals.h"
#include "upgrade.h"
#include "soldier.h"
#include "item.h"
#include "text_wrapping.h"

/*=========================================================
City class containing guild information on a per city basis
=========================================================*/

class city{
public:
	//constructor
	city(std::string, std::string, int, int, int, int, int);
	//destructor
	~city();
	//accessors
	std::string get_name() { return name; }
	//ALLEGRO_BITMAP *get_guild_image(){ return withguild; }
	//ALLEGRO_BITMAP *get_without_guild_image(){ return withoutguild; }
	int get_reputation(){ return reputation; }
	int get_defense(){return defense_rating; }
	//std::vector<item> get_full_store(){ return full_store; }
	//std::list<item> get_for_sale() {return for_sale; }
	std::list<soldier> get_soldiers(){ return guild_soldiers; }
	int get_max_soldiers() { return max_soldiers; }
	std::vector<std::string> get_description() { return city_description; }
	int get_x() { return x; }
	int get_y() { return y; }
	bool get_selected() { return selected; }
	bool get_has_guild() { return has_guild; }

	//mutators
	void change_gold(int &gold, int value){ gold += value; }	//function used when purchasing things on guild screen
	void add_soldier(soldier new_soldier);
	void set_soldiers(std::vector<soldier> soldiers);
	void change_has_guild() {has_guild = !has_guild; }
	bool clicked_on(int mouse_x, int mouse_y);
	bool guild_clicked_on(int mouse_x, int mouse_y);
	void change_selected(){ selected = !selected; }
	void add_def(int def) {defense_rating += def; }	//def should be negative if subtracting
	void add_rep(int rep) {reputation += rep; }	//rep should be negative if subtracting

	std::vector<upgrade> guild_upgrades; //array of all guild upgrades

	//rendering
	void map_draw(ALLEGRO_FONT *);
	void guild_draw(ALLEGRO_FONT *, ALLEGRO_FONT *);
	void draw_guild_icon(ALLEGRO_FONT *, int, int);

private:
	std::string name;

	//ALLEGRO_BITMAP *withguild;	//image on map for a guild-occupied city
	//ALLEGRO_BITMAP *withoutguild;	//image on map when unoccupied by guild

	int reputation;
	int defense_rating;
	
	std::vector<item> full_store; //vector containing all store items the shop in the city can sell
	std::list<item> for_sale; //list containing all items currently unlocked and purchasable

	std::list<soldier> guild_soldiers; //list of soldiers currently housed at the guild
	int max_soldiers;

	std::vector<std::string> city_description;

	int x;	//position of city button on map screen
	int y;

	int guild_x;	//position of the button to quickly jump between guilds
	int guild_y;	//this value is set by the draw function

	std::vector<std::string> mythological_hunters;	//these two vectors work together to randomly
	std::vector<std::string> follower_titles;		//generate a name for the guild, can be moved out
													//-side of the class later

	bool selected;	//if on the guild screen, this bool tells the  game which guild to draw
	bool has_guild;	//determines the image for the guild, whether it can house soldiers, etc...
};
