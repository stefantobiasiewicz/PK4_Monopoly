#pragma once
#include"SFML/Network.hpp"
#include <iostream>
class Internet
{

	sf::TcpSocket socket;
	sf::IpAddress ip;
	char connectionType; // czy prgoram b�dzie dzi�� jako server czy jako klijent

	//domy�lnie w�aczany jest tryb servera 
	Internet(char type = 's', sf::IpAddress ip = sf::IpAddress::getLocalAddress()) : connectionType(type) , ip(ip) {}	

	bool begin(); // funkcja w��czaj�ca transmisje
	bool transmit();
	std::string recive();

};

