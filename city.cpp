#include "city.h"

city::city(std::string name, std::string description, /*std::string without_guild_image, std::string with_guild_image,*/ int x, int y, int reputation, int defense, int max_soldiers){
	city::name = name;
	//withoutguild = al_load_bitmap(without_guild_image.c_str());
	//withguild = al_load_bitmap(with_guild_image.c_str());
	city::x = x;
	city::y = y;
	city::reputation = reputation;
	defense_rating = defense;
	city::max_soldiers = max_soldiers;
	selected = false;
	has_guild = false;
	city_description = text_wrap(description, 480);
}

city::~city(){

}

void city::add_soldier(soldier new_soldier){
	guild_soldiers.push_back(new_soldier);
}

void city::set_soldiers(std::vector<soldier> soldiers){
	for(unsigned int i=0; i<soldiers.size(); i++)
		guild_soldiers.push_back(soldiers[i]);
}

void city::map_draw(ALLEGRO_FONT *font12){
	al_draw_circle(x, y, 16, al_map_rgb(0,0,255), 3);
	if(has_guild)
		al_draw_rectangle(x-10, y-10, x+10, y+10, al_map_rgb(255,0,0), 2);
	al_draw_filled_rectangle(x-30, y-38, x+30, y-18, al_map_rgb(255,255,255));
	al_draw_rectangle(x-30, y-38, x+30, y-18, al_map_rgb(0,0,0), 2);
	al_draw_textf(font12, al_map_rgb(0,0,255), x - 26, y - 34, 0, "Def: %i  Rep: %i", defense_rating, reputation);
}

void city::guild_draw(ALLEGRO_FONT *font_small, ALLEGRO_FONT *font_large){
	al_draw_textf(font_large, al_map_rgb(0,0,0), 50, 92, 0, "%s", name.c_str());
	al_draw_textf(font_small, al_map_rgb(0,0,0), 380, 38, 0, "%i", defense_rating);
	//44,88
	for(unsigned int i=0; i<city_description.size(); i++){
		al_draw_textf(font_small, al_map_rgb(0,0,0), 50, 145 + i*14, 0,"%s", city_description[i].c_str());
	}
}

void city::draw_guild_icon(ALLEGRO_FONT *font12, int guild_x, int guild_y){
	city::guild_x = guild_x;
	city::guild_y = guild_y;
	al_draw_rectangle(guild_x, guild_y, guild_x + 160, guild_y + 50, al_map_rgb(0,0,0), 2);
	al_draw_textf(font12, al_map_rgb(0,0,0), guild_x + 5, guild_y + 5, 0, "%s", name.c_str());
}

bool city::clicked_on(int mouse_x, int mouse_y){
	if(mouse_x > x - 14 &&
	   mouse_x < x + 14 &&
	   mouse_y > y - 14 && 
	   mouse_y < y + 14)
		return true;
	else return false;
}

bool city::guild_clicked_on(int mouse_x, int mouse_y){
	if(mouse_x > guild_x &&
	   mouse_x < guild_x + 160 &&
	   mouse_y > guild_y &&
	   mouse_y < guild_y + 50)
	   return true;
	else return false;
}
