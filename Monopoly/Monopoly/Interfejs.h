#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>

#include "Obiekt_Na_Planszy.h"
#include "Plansza.h"

#include "BazaDanych.h"
#include "Resolution.h"

class Interfejs
{

public:
	sf::RenderWindow* MainWindow;
	Plansza * PoleGry;
	BazaDanych* resources;

	Interfejs(BazaDanych* res) : resources(res)
	{
		//MainWindow = new sf::RenderWindow(sf::VideoMode(1000, 800), "My window");
		//PoleGry = new Plansza(std::string("res/p.png"));
	}
	~Interfejs()
	{
		delete MainWindow;
		delete PoleGry;
	}

	void StartWindow();


	// funkcja do odpalenia przez w¹tek 
	void DrawThread();

};

class Button : public sf::Sprite
{
public:

	Button(sf::Vector2f vect, std::string def_tex , std::string click_tex, std::string text);
	Button(sf::Vector2f vect, sf::Texture def_tex, sf::Texture click_tex, std::string text);
	~Button();

	bool click(int mouse_x_pos , int mouse_y_pos);		//funkcja która wywo³ujemy w evencie klikniecia myszka
	bool mouse_move(int mouse_x_pos, int mouse_y_pos);	//funkcja ktora wywo³ujemy w evencie poruszenia myszki

	void frame_scale(int x, int y);
	void frame_pos(int x, int y);

	int size_x, size_y;

private:

	void set_change(bool on);

	int frame_x, frame_y;


	sf::Texture def_tex;
	sf::Texture click_tex;


	sf::Texture button_tex;
};

