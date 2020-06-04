#include "Textbox.h"

void Textbox::deleteLastChar()
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

void Textbox::inputLogic(int charTyped)
{
	//je�li wci�ni�ty przycisk nie jest 'backspace'
	if (charTyped != DELETE_KEY)
	{
		text << static_cast<char>(charTyped);
	}
	//je�li wci�ni�ty przycisk jest 'backspace' to wywo�anie metody kasuj�cej znak
	else
	{
		if (text.str().length() > 0)
		{
			deleteLastChar();
		}
	}
	//ustawienie tre�ci texboxu
	textbox.setString(text.str() + "_");  //"_" na ko�cu jako kursor
}

Textbox::Textbox(int size, sf::Color color, bool sel)
{
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = sel;

	//sprawd� czy textbox jest klikni�ty i wypisz "_" lub nie
	if (isSelected)
		textbox.setString("_");
	else
		textbox.setString("");
}

void Textbox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f point)
{
	textbox.setPosition(point);
}

void Textbox::setLimit(bool ToF)
{
	hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim)
{
	hasLimit = ToF;
	limit = lim - 1;
}

void Textbox::setSelected(bool sel)
{
	isSelected = sel;

	//je�li isSelected = 0 - nie pisz "_"
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

std::string Textbox::getText()
{
	return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window)
{
	window.draw(textbox);
}

void Textbox::typedOn(sf::Event input)
{
	if (isSelected)
	{
		int charTyped = input.text.unicode;

		//tylko znaki klasyczne
		if (charTyped < 128)
		{
			if (hasLimit)
			{
				//je�li jest limit znak�w, nie mo�na pisa� dalej
				if (text.str().length() <= limit)
				{
					inputLogic(charTyped);
				}
				//ale mo�na kasowa�
				else if (text.str().length() > limit&& charTyped == DELETE_KEY)
				{
					deleteLastChar();
				}
			}
			//je�li nie ma limitu, po prostu pisz
			else {
				inputLogic(charTyped);
			}
		}
	}
}