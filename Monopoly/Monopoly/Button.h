#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>


class Button
{
public:

	Button(sf::Vector2f vect, std::string def_tex_string, std::string click_tex_string, std::string text);
	~Button();



	bool event(sf::Event event);		// funkcja zczytujaca wszzystkie eventy // do umieszczenia w sekcji eventów // funkcja zwraca czy przycisk zostal wcisniety


	void scale(float factorX, float factorY);
	void setPosition(float x, float y);

	//void set_frame_scale(int x, int y);	//
	//void set_frame_pos(int x, int y);	// funkcja ustawiajaca pozycje ramki przyciskania
	//void set_window_size(int x, int y);

	void drawTo(sf::RenderWindow& window); // funkcja rysujaca przycisk



private:

	bool click(int mouse_x_pos, int mouse_y_pos);		//funkcja która wywo³ujemy w evencie klikniecia myszka
	bool mouse_move(int mouse_x_pos, int mouse_y_pos);	//funkcja ktora wywo³ujemy w evencie poruszenia myszki

	void set_change(bool on);


	int size_x, size_y;



	sf::Texture def_tex;
	sf::Texture click_tex;

	sf::Sprite button;

};

