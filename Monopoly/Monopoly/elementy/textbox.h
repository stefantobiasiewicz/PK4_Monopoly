#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

// definicja klawiszy funkcyjnych
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;    //textbox jest wybrany
	bool hasLimit = false;      //czy przekroczono limit
	int limit = 0;              //d³ugoœæ limitu znaków

	// kasowanie ostatniego znaku
	void deleteLastChar()
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str() + "_");
	}

	// pobieranie znaków od u¿ytkownika
	void inputLogic(int charTyped)
	{
		//jeœli wciœniêty przycisk nie jest 'backspace'
		if (charTyped != DELETE_KEY)
		{
			text << static_cast<char>(charTyped);
		}
		//jeœli wciœniêty przycisk jest 'backspace' to wywo³anie metody kasuj¹cej znak
		else
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		//ustawienie treœci texboxu
		textbox.setString(text.str() + "_");  //"_" na koñcu jako kursor
	}
public:
	Textbox() {}
	Textbox(int size, sf::Color color, bool sel) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;

		//sprawd¿ czy textbox jest klikniêty i wypisz "_" lub nie
		if (isSelected)
			textbox.setString("_");
		else
			textbox.setString("");
	}

	//czcionka przekazywana przez referencjê
	void setFont(sf::Font& font)
	{
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f point) {
		textbox.setPosition(point);
	}

	//w³¹czanie/wy³¹czanie limitu znaków
	void setLimit(bool ToF)
	{
		hasLimit = ToF;
	}

	//ustawienie limitu znaków
	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim - 1;
	}

	//Zmieñ aktualny stan
	void setSelected(bool sel)
	{
		isSelected = sel;

		//jeœli isSelected = 0 - nie pisz "_"
		if (!sel)
		{
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}

	std::string getText()
	{
		return text.str();
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(textbox);
	}

	//obs³uga eventu
	void typedOn(sf::Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;

			//tylko znaki klasyczne
			if (charTyped < 128)
			{
				if (hasLimit)
				{
					//jeœli jest limit znaków, nie mo¿na pisaæ dalej
					if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					//ale mo¿na kasowaæ
					else if (text.str().length() > limit&& charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				//jeœli nie ma limitu, po prostu pisz
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

};