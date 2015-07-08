#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <vector>
#include <string>
#include <allegro5\allegro_native_dialog.h>

class button{
public:
	button(std::string identifier, std::string imagename, std::string selectedname, int a, int b){
		image = al_load_bitmap(imagename.c_str());
		//if(image)
			//al_convert_mask_to_alpha(image, al_map_rgb(255,255,255));
		clicked = al_load_bitmap(selectedname.c_str());
		//if(clicked)
			//al_convert_mask_to_alpha(clicked, al_map_rgb(255,255,255));
		x = a;
		y = b;
		id = identifier;
		if(image)
			current = image;
		clicking = false;
	}
	~button(){
		if(image)
			al_destroy_bitmap(image);
		if(clicked)
			al_destroy_bitmap(clicked);
		if(current)
			al_destroy_bitmap(current);
	}
	void draw(){
		al_draw_bitmap(current, x, y, 0);
	}
	bool clicked_on(int mouse_x, int mouse_y){
		if(mouse_x > x && mouse_x < x+37 && mouse_y > y
			&& mouse_y < y+24) return true;
		else return false;
	}
	void swap_image(){
		if(current == image)
			current = clicked;
		else current = image;
	}
	std::string id;
	bool clicking;
protected:
	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *clicked;
	ALLEGRO_BITMAP *current;
	int x;
	int y;


};

int main(){
	
	bool done = false;
	bool draw = true;
	bool redraw = true;
	int color = 0;
	int mouse_x = 0;
	int mouse_y = 0;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *main_q = NULL;
	ALLEGRO_FONT *font16 = NULL;
	ALLEGRO_FONT *font32 = NULL;
	ALLEGRO_TIMER *gametimer = NULL;
	ALLEGRO_BITMAP *menu_background = NULL;

	if(!al_init())
		return -1;

	display = al_create_display(640,480);
	//display = al_create_display(1920, 1080);
	if(!display)
		return -1;

	al_init_primitives_addon();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	main_q = al_create_event_queue();
	font16 = al_load_font("COLONNA.ttf", 16, 0);
	font32 = al_load_font("COLONNA.ttf", 32, 0);
	gametimer = al_create_timer(1.0/60);
	menu_background = al_load_bitmap("menu_background.png");
	
	al_register_event_source(main_q, al_get_display_event_source(display));
	al_register_event_source(main_q, al_get_mouse_event_source());
	al_register_event_source(main_q, al_get_timer_event_source(gametimer));

	//start game timer
	al_start_timer(gametimer);

	//initialize buttons
	std::vector<button *> main_m;
	button *current = new button("play", "play.png", "highlighted_play.png", 300, 200);
	main_m.push_back(current);
	//current = new button("quit", "quit.png", "highlighted_quit.png", 291, 733);
	current = new button("quit", "quit.png", "highlighted_quit.png", 300, 250);
	main_m.push_back(current);
	/*current = new button("settings", "settings.png", "highlighted_settings.png", 243, 650);
	main_m.push_back(current);
	current = new button("load", "load.png", "highlighted_load.png", 285, 561);
	main_m.push_back(current);*/

	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(main_q, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if(ev.mouse.button == 2)
				done = true;
			if(ev.mouse.button == 1){
				for(unsigned int i=0; i<main_m.size(); i++){
					if(main_m[i]->clicked_on(ev.mouse.x, ev.mouse.y)){
						main_m[i]->swap_image();
						main_m[i]->clicking = true;
					}
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			if(ev.mouse.button == 1){
				for(unsigned int i=0; i<main_m.size(); i++){
					if(main_m[i]->clicking){
						main_m[i]->swap_image();
						main_m[i]->clicking = false;
					}
					if(main_m[i]->clicked_on(ev.mouse.x, ev.mouse.y)){
						if(main_m[i]->id == "quit")
							done = true;
						else if(main_m[i]->id == "play")
							al_show_native_message_box(display, NULL, "Play Game",
								"You are now playing Sportsmen of Fairmoor", NULL, 0);
					}
				}
			}
		}


		if(redraw && al_is_event_queue_empty(main_q)){
			redraw = false;	
			//al_draw_bitmap(menu_background, 0, 0, 0);
			for(unsigned int i=0; i<main_m.size(); i++)
				main_m[i]->draw();
			if(color == 255)
				color = 0;
			else color++;
			al_draw_text(font32, al_map_rgb(255,color, color), 170, 150, 0, "Sportsmen of Fairmoor");
			al_draw_textf(font16, al_map_rgb(255,255,255), 10, 10, 0, "Mouse Position: %i, %i", mouse_x, mouse_y);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_display(display);
	al_destroy_font(font16);
	al_destroy_font(font32);
	al_destroy_timer(gametimer);
	al_destroy_event_queue(main_q);
	al_destroy_bitmap(menu_background);

	return 0;
}
