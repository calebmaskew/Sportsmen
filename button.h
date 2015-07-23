#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

class button{
public:
	button(std::string identifier, std::string imagename, std::string selectedname,
		int a, int b, int w, int h);
	~button();
	void draw(){if(current) al_draw_bitmap(current, x, y, 0); }
	bool clicked_on(int mouse_x, int mouse_y);
	void swap_image();

	int getx() { return x; }
	int gety() { return y; }
	std::string getid() {return id; }
	bool getclicked() {return clicked; }
	void setclicked(bool clicked) { button::clicked = clicked; }

private:
	ALLEGRO_BITMAP *def_image;
	ALLEGRO_BITMAP *click_image;
	ALLEGRO_BITMAP *current;
	int x;
	int y;
	std::string id;
	bool clicked;
	int w;
	int h;
};
