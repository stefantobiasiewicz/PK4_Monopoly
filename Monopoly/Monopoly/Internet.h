#pragma once
#include"SFML/Network.hpp"
#include <iostream>
class Internet
{

	sf::TcpSocket socket;
	sf::IpAddress ip;
	char connectionType; // czy prgoram bêdzie dzi¹³ jako server czy jako klijent

	//domyœlnie w³aczany jest tryb servera 
	Internet(char type = 's', sf::IpAddress ip = sf::IpAddress::getLocalAddress()) : connectionType(type) , ip(ip) {}	

	bool begin(); // funkcja w³¹czaj¹ca transmisje
	bool transmit();
	std::string recive();

};

