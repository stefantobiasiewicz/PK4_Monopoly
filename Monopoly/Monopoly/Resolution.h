#pragma once
#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Resolution
{
	int w_res;
	int h_res;
public:

	Resolution();

	int x(float width);
	int y(float height);
	sf::Vector2f scale();

	int GetW_res();
	int GetH_res();
};