#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "elementy_graficzne.h"

// definicja klawiszy funkcyjnych
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27


class Textbox : public Klik_Prostokat
{
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;    //textbox jest wybrany
	bool hasLimit = false;      //czy przekroczono limit
	int limit = 0;              //d³ugoœæ limitu znaków

	// kasowanie ostatniego znaku
	void deleteLastChar();

	// pobieranie znaków od u¿ytkownika
	void inputLogic(int charTyped);
public:
	Textbox(int size, sf::Color color_text, bool sel, float bar_length, sf::Vector2f pos, sf::Color color_shape);

	//czcionka przekazywana przez referencjê
	void setFont(sf::Font& font);

	void setPosition(sf::Vector2f point);

	//w³¹czanie/wy³¹czanie limitu znaków
	void setLimit(bool ToF);

	//ustawienie limitu znaków
	void setLimit(bool ToF, int lim);

	//Zmieñ aktualny stan
	void setSelected(bool sel);

	std::string getText();

	void drawTo(sf::RenderWindow& window);

	//obs³uga eventu
	void typedOn(sf::Event input);

	bool click(int mouse_x, int mouse_y);

	bool is_mouse_on(int mouse_x, int mouse_y);

	void EnterTheText(sf::Event event);

};