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

Textbox::Textbox(int size, sf::Color color_text, bool sel, float bar_length, sf::Vector2f pos, sf::Color color_shape) : Klik_Prostokat({0.f, 0.f}, pos, color_shape)
{
	this->shape.setSize({bar_length, (float)size * 1.33335f });
	this->shape.setOutlineColor(sf::Color(0, 0, 0));
	this->shape.setOutlineThickness(2.f);

	textbox.setPosition(pos);
	textbox.setCharacterSize(size);
	textbox.setFillColor(color_text);
	isSelected = sel;

	//sprawd¿ czy textbox jest klikniêty i wypisz "_" lub nie
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
	this->shape.setPosition(point);
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
	else
	{
		std::string temp = text.str();
		temp = temp + '_';
		textbox.setString(temp);
	}
}

std::string Textbox::getText()
{
	return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(textbox);
}

bool Textbox::click(int mouse_x, int mouse_y)
{
	setSelected(Klik_Prostokat::click(mouse_x, mouse_y));
	is_mouse_on(mouse_x, mouse_y);
	return isSelected;
}

bool Textbox::is_mouse_on(int mouse_x, int mouse_y)
{
	sf::Vector2f pos = this->shape.getPosition();
	if (mouse_x > pos.x&& mouse_x < (pos.x + this->getSize().x) && mouse_y > pos.y&& mouse_y < (pos.y + this->getSize().y))
	{
		shape.setOutlineThickness(5.f);
		return true;
	}
	else
	{
		if (!isSelected)
		{
			shape.setOutlineThickness(2.f);
		}
		return false;

	}
}

void Textbox::EnterTheText(sf::Event event)
{
	setSelected(false);
	is_mouse_on(event.mouseButton.x, event.mouseButton.y);
}

bool Textbox::event(sf::Event event)
{
	if (event.type == sf::Event::TextEntered)
	{
		this->typedOn(event);

	}
	bool czy_klikniety = Klikalny::event(event);
	return czy_klikniety;

}

void Textbox::typedOn(sf::Event input)
{
	if (isSelected)
	{
		int charTyped = input.text.unicode;

		if (charTyped == ENTER_KEY)
		{
			EnterTheText(input);

		}

		//tylko znaki klasyczne
		if (isSelected == true && charTyped < 128)
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