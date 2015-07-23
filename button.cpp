#include "button.h"

	//constructor initializing the button's ID, idle and clicked bitmaps, 
	//	x and y pixel position on screen, and the buttons width and height
	button::button(std::string identifier, std::string imagename, 
		std::string selectedname, int a, int b, int w, int h){
			def_image = al_load_bitmap(imagename.c_str());
			click_image = al_load_bitmap(selectedname.c_str());
			x = a;
			y = b;
			id = identifier;
			if(def_image)
				current = def_image;
			clicked = false;
			button::w = w;
			button::h = h;
	}

	button::~button(){
		if(def_image)
			al_destroy_bitmap(def_image);
		if(click_image)
			al_destroy_bitmap(click_image);
		if(current)
			al_destroy_bitmap(current);
	}

	bool button::clicked_on(int mouse_x, int mouse_y){
		if(mouse_x > x &&
			mouse_x < x + w &&
			mouse_y > y &&
			mouse_y < y + h)
			return true;
		else return false;
	}

	void button::swap_image(){
		if(current == def_image)
			current = click_image;
		else current = def_image;
	}
