/*This is not currently an example of even decent encapsulation.  This struct became far more complicated than I originally
  thought, will need to be converted to a class, and will need to have it's own source code file*/

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "globals.h"
#include "text_wrapping.h"

struct upgrade{
	upgrade(){
		locked = true;
		purchased = false;
	}
	upgrade(int cost, int defensive_value, std::string name, std::string description, int x, int y){
		upgrade::cost = cost;
		upgrade::defensive_value = defensive_value;
		upgrade::name = name;
		upgrade::x = x;
		upgrade::y = y;
		locked = true;
		purchased = false;
		upgrade::description = description;
	}
	std::string description;
	int cost;
	int defensive_value;
	std::string name;
	bool purchased;
	bool locked;
	int x;	//x and y position to be drawn on screen
	int y;
	void draw(ALLEGRO_FONT *font){
		//change the color based on upgrade's availability
		//	later this will be separate bitmaps
		ALLEGRO_COLOR button_color = al_map_rgb(0,0,0);
		if(locked)
			button_color = al_map_rgb(150,150,150);
		else if(!locked)
			button_color = al_map_rgb(0,150,150);
		if(purchased)
			button_color = al_map_rgb(0,255,0);
		al_draw_filled_rectangle(x, y, x+70, y+70, button_color);
		al_draw_textf(font, al_map_rgb(0,0,0), x+78, y, 0, "%s", name.c_str());
		al_draw_textf(font, al_map_rgb(0,0,0), x+78, y+18, 0, "Def:%4i Cost:%5i", defensive_value, cost);

	}
	bool clicked_on(int mouse_x, int mouse_y){
		if(mouse_x > x &&
		   mouse_x < x + 70 &&
		   mouse_y > y &&
		   mouse_y < y + 70)
		   return true;
		else return false;
	}

	//function for the player to confirm upgrade purchase with message box
	bool confirm_upgrade(ALLEGRO_FONT *font, int GOLD){
		//setup function to take mouse input
		ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
		ALLEGRO_EVENT ev2;
		al_register_event_source(event_queue, al_get_mouse_event_source());
		al_register_event_source(event_queue, al_get_keyboard_event_source());

		//drawing message box
		al_draw_filled_rectangle(660, 415, 1260, 665, al_map_rgb(255,255,255)); 
		al_draw_rectangle(660, 415, 1260, 665, al_map_rgb(0,0,0), 4);
		//if we can't afford it, tell the player so
		if(cost > GOLD)
			al_draw_textf(font, al_map_rgb(255,0,0), 960, 520, ALLEGRO_ALIGN_CENTRE, "You require an additional %i Gold to purchase this upgrade", cost - GOLD);
		al_draw_textf(font, al_map_rgb(0,0,0), 960, 540, ALLEGRO_ALIGN_CENTRE, "Are you sure you want to buy %s for %i gold?", name.c_str(), cost);
		al_draw_rectangle(820, 585, 940, 635, al_map_rgb(0,0,0), 4);
		al_draw_rectangle(980, 585, 1100, 635, al_map_rgb(0,0,0), 4);
		al_draw_text(font, al_map_rgb(0,0,0), 880, 600, ALLEGRO_ALIGN_CENTRE, "Yes");
		al_draw_text(font, al_map_rgb(0,0,0), 1040, 600, ALLEGRO_ALIGN_CENTRE, "No");
		
		std::vector<std::string> desc = text_wrap(description, 550);
		for(unsigned int i=0; i<desc.size(); i++)
			al_draw_textf(font, al_map_rgb(0,0,0), 685, 425 + i*18, 0, "%s", desc[i].c_str());
		
		al_flip_display();

		//event handling
		bool finished = false;
		bool yes = false;
		while(!finished){
			al_wait_for_event(event_queue, &ev2);

			if(ev2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
				//if we click yes
				int mouse_x = ev2.mouse.x;
				int mouse_y = ev2.mouse.y;
				if(mouse_x > 820 && 
					mouse_x < 940 &&
					mouse_y > 565 && 
					mouse_y < 615 &&
					cost <= GOLD){
						finished = true;
						yes = true;
				}
				//if we click no
				else if(mouse_x > 980 &&
					mouse_x < 1100 &&
					mouse_y > 565 &&
					mouse_y < 615)
					finished = true;
			}
			else if(ev2.type == ALLEGRO_EVENT_KEY_UP){
				if(ev2.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					finished = true;
				}
			}
		}
		al_destroy_event_queue(event_queue);

		return yes;
	}

};
