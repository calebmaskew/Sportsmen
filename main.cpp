#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "button.h"
#include "city.h"
#include "soldier.h"
#include "globals.h"
#include "initialization.h"
#include "upgrade.h"
#include "text_wrapping.h"
#include "main_vars.h"
#include "mission_gen.h"

void ChangeState(int &state, int newState);

int main(){

	bool done = false;
	bool render = false;

	//gold is initialized here for testing purposes only
	GOLD = 2750;

	//==============================================
	//ALLEGRO INITIALIZATION
	//==============================================
	if(!al_init())
		return -1;
	if(!al_install_keyboard())
		return -2;
	if(!al_install_mouse())
		return -3;
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_native_dialog_addon();

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
	ALLEGRO_EVENT_QUEUE *game_queue = al_create_event_queue();
	ALLEGRO_TIMER *gametimer = al_create_timer(1.0/60);
	ALLEGRO_FONT *font32 = al_load_font("AGENCYR.ttf", 32, 0);
	ALLEGRO_FONT *font12 = al_load_font("AGENCYR.ttf", 12, 0);
	ALLEGRO_FONT *font16 = al_load_font("AGENCYR.ttf", 16, 0);
	ALLEGRO_FONT *alegreya16 = al_load_font("AlegreyaSC-Regular.ttf", 16, 0);
	ALLEGRO_FONT *alegreya32 = al_load_font("AlegreyaSC-Regular.ttf", 32, 0);
	ALLEGRO_BITMAP *background = al_load_bitmap("menu_background.jpg");
	ALLEGRO_BITMAP *map_background = al_load_bitmap("sportsmen main menu map.jpg");
	ALLEGRO_BITMAP *guild_background = al_load_bitmap("rough_guild_background2.jpg");

	//==============================================
	//REGISTER EVENT SOURCES
	//==============================================
	al_register_event_source(game_queue, al_get_timer_event_source(gametimer));
	al_register_event_source(game_queue, al_get_keyboard_event_source());
	al_register_event_source(game_queue, al_get_mouse_event_source());
	al_register_event_source(game_queue, al_get_display_event_source(display));
	
	//START GAME TIMER
	al_start_timer(gametimer);

	//==============================================
	//INITIALIZE MASTER CONTENT LISTS
	//==============================================
	initialize_cities_by_biome(cities_by_biome);
	master_monster_list = initialize_monster_list();
	master_battlescape_list = initialize_battlescape_list();
	master_mission_description_list = initialize_mission_description_list(master_monster_list, master_battlescape_list);
	master_story_mission_description_list = initialize_master_story_mission_list(master_monster_list, master_battlescape_list);

	/*The following comment is for if testing the mission generator for certain story progressions
	is desired.  Otherwise, this is not how the function will be used in game
	std::cout << "Please enter the current story progress: ";
	std::cin >> story_progression;
	std::cout << "Please enter the number of weeks until next story mission: ";
	std::cin >> weeks_until_next_story_mission;

	mission_gen generator(master_story_mission_description_list);
	std::vector<mission> current_missions = generator.generate(weeks_until_next_story_mission, story_progression, 
		cities_by_biome, master_battlescape_list, master_monster_list, master_mission_description_list);

	for(unsigned i=0; i<current_missions.size(); i++)
		current_missions[i].show_info();
	*/

	//==============================================
	//INITIALIZE MAIN MENU
	//==============================================
	std::vector<button *> main_menu;
	button *cur_button = new button("newgame", "new_game.png", "newgame_high.png",
		1435, 386, 452, 75);
	main_menu.push_back(cur_button);
	cur_button = new button("quit", "quit.png", "quit_high.png",
		1525, 780, 223, 85);
	main_menu.push_back(cur_button);
	cur_button = new button("load", "load.png", "load_high.png",
		1525, 520, 225, 77);
	main_menu.push_back(cur_button);
	cur_button = new button("settings", "settings.png", "settings_high.png",
		1450, 650, 344, 98);
	main_menu.push_back(cur_button);

	//===============================================
	//INITIALIZE GAME MAP SCREEN
	//===============================================
	//city initialization
	std::vector<city> cities = init_cities();

	//seed random number generator for testing purposes
	srand(time(NULL));

	//initialize original game state
	int state = MAIN_MENU;

	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(game_queue, &ev);

		//===========================================
		//INPUT PROCESSING
		//===========================================

		if(ev.type == ALLEGRO_EVENT_TIMER){
			render = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				if(state == GUILD){
					ChangeState(state, MAP);
					//deselect selected guild
					for(unsigned int i=0; i<cities.size(); i++){
						if(cities[i].get_selected())
							cities[i].change_selected();
					}
				}
				else done = true;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(ev.mouse.button == 1){
				//=======================================================
				//MAIN MENU: Check whether or not a button is clicked and
				//			 change the image to its clicked bitmap
				//=======================================================
				switch(state){
				case MAIN_MENU:
					for(unsigned int i=0; i<main_menu.size(); i++){
						if(main_menu[i]->clicked_on(ev.mouse.x, ev.mouse.y)){
							main_menu[i]->swap_image();
							main_menu[i]->setclicked(true);
						}
					}
					break;
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			if(ev.mouse.button == 1){
				//=======================================================
				//MAIN MENU: Check whether or not a button is clicked and
				//			 perform appropriate action
				//=======================================================
				switch(state){
				case MAIN_MENU:
					for(unsigned int i=0; i<main_menu.size(); i++){
						if(main_menu[i]->getclicked()){
							main_menu[i]->swap_image();
							main_menu[i]->setclicked(false);
						}
						if(main_menu[i]->clicked_on(ev.mouse.x, ev.mouse.y)){
							if(main_menu[i]->getid() == "quit")
								done = true;
							else if(main_menu[i]->getid() == "newgame")
								ChangeState(state, MAP);
						}
					}
					break;
				//========================================================
				//MAP SCREEN: Check whether or not a guild is clicked and
				//	change to guild screen if so
				//========================================================
				case MAP:
					for(unsigned int i=0; i<cities.size(); i++){
						if(cities[i].clicked_on(ev.mouse.x, ev.mouse.y)){
							cities[i].change_selected();
							std::cout << cities[i].get_name() << " has been clicked\n";
							ChangeState(state, GUILD);
						}
					}
					break;
				//========================================================
				//GUILD SCREEN: Oh so many things.  Currently though, just
				//	change the active guild when a different icon is clicked
				//========================================================
				case GUILD:
					std::cout << "We released the mouse button on the guild screen\n";
					for(unsigned int i=0; i<cities.size(); i++){
						//loop through guild/city buttons and check to see if guild needs changing
						if(cities[i].guild_clicked_on(ev.mouse.x, ev.mouse.y)){
							std::cout << cities[i].get_name() << " was clicked on on the guild screen\n";
							//loop through all cities and change the selected variable to be unselected
							for(unsigned int j=0; j<cities.size(); j++){
								if(cities[j].get_selected() == true){
									cities[j].change_selected();
									std::cout << cities[j].get_name() << " was selected, now it is not\n";
								}
							}
							//set the city clicked on to selected
							cities[i].change_selected();
						}
						//loop through upgrade buttons and see if the player is trying to purchase one
						//	Note: this only needs to be done for the selected guild
						al_unregister_event_source(game_queue, al_get_keyboard_event_source());
						if(cities[i].get_selected()){
							for(unsigned int j=0; j<cities[i].guild_upgrades.size(); j++){
								if(cities[i].guild_upgrades[j].clicked_on(ev.mouse.x, ev.mouse.y) && cities[i].guild_upgrades[j].locked == false){
									//=======================================================
									//If it is found later that the background should not be 
									//	black during the confirmation message, the draw code
									//	for the guild screen has to be copied and done once
									//=======================================================
									//display a message box asking the user to confirm his/her choice of upgrade
									if(cities[i].guild_upgrades[j].confirm_upgrade(alegreya16, GOLD)){
										//subtract the cost of the upgrade from player gold
										cities[i].change_gold(GOLD, -1*cities[i].guild_upgrades[j].cost);
										//add the defensive value of the upgrade to the city's defensive rating
										cities[i].add_def(cities[i].guild_upgrades[j].defensive_value);
										//change the upgrade to purchased and lock the upgrade so it cannot be bought again
										cities[i].guild_upgrades[j].purchased = true;
										cities[i].guild_upgrades[j].locked = true;
									}
									
								}
							}
						}
						al_register_event_source(game_queue, al_get_keyboard_event_source());
					}
					break;
				}
			}
		}

		//============================================
		//RENDERING
		//============================================

		if(render && al_is_event_queue_empty(game_queue)){
			render = false;
			
			switch(state){
			//===========================================================
			//MAIN MENU: Draw buttons and menu background
			//===========================================================
			case MAIN_MENU:
				al_draw_bitmap(background, 0, 0, 0);
				for(unsigned int i=0; i<main_menu.size(); i++)
					main_menu[i]->draw();
				break;
			//===========================================================
			//MAP SCREEN: Draw relevant guild and mission info, as well
			//	as player gold and the game options menu button in corner
			//===========================================================
			case MAP:
				al_draw_bitmap(background, 0, 0, 0);
				for(unsigned int i=0; i<cities.size(); i++)
					cities[i].map_draw(alegreya16);
				break;
			//===========================================================
			//GUILD SCREEN: Draw the guild background and the information
			//	associated with the clicked-on guild as well as gold
			//===========================================================
			case GUILD:
				al_draw_bitmap(guild_background, 0, 0, 0);
				al_draw_textf(alegreya16, al_map_rgb(0,0,0), 1750, 45, 0, "%i", GOLD);
				for(unsigned int i=0; i<cities.size(); i++){
					if(cities[i].get_selected() == true){
						cities[i].guild_draw(alegreya16, alegreya32);
					}
				}
				//loop through guilds and draw buttons for them
				for(unsigned int i=0; i<cities.size(); i++){
					cities[i].draw_guild_icon(alegreya16, 1710, 122 + (i*50));
				}
				//loop through the cities and draw their associated upgrades
				for(unsigned int i=0; i<cities.size(); i++){
					if(cities[i].get_selected()){
						for(unsigned int j=0; j<cities[i].guild_upgrades.size(); j++){
							cities[i].guild_upgrades[j].draw(alegreya16);
						}
					}
				}
				break;
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}

	}

	//=================================================
	//DESTROY ALLEGRO VARIABLES
	//=================================================

	al_destroy_display(display);
	al_destroy_timer(gametimer);
	al_destroy_event_queue(game_queue);
	al_destroy_font(font32);

	return 0;
}

//function for changing the current game state
//State is used to determine what input to receive and what to draw
void ChangeState(int &state, int newState){

	if(state == MAIN_MENU)
		std::cout << "Now leaving the main menu\n";
	else if(state == GUILD)
		std::cout << "Now leaving guild screen and returning to map\n";

	state = newState;

	if(state == LOAD)
		std::cout << "Attempting to load a game\n";
	else if(state == NEW_GAME)
		std::cout << "Entering the new game screen\n";
	else if(state == LOAD_MENU)
		std::cout << "Entering the saved game selection screen\n";
	else if(state == MAP)
		std::cout << "Entering the map screen\n";
}
