#pragma once
#include"SFML/Network.hpp"
#include <iostream>
#include <list>
#include <thread>

class Internet
{
public:
	sf::TcpSocket socket;
	sf::TcpListener listener;
	sf::IpAddress ip;
	char connectionType; // czy prgoram bêdzie dzi¹³ jako server czy jako klijent

	std::list<char> dane;

	sf::Packet Packet_data;
	char data[100];

	std::thread* watek;

	//domyœlnie w³aczany jest tryb servera 
	Internet(char type , sf::IpAddress ip );
	void begin(); // funkcja w³¹czaj¹ca transmisje
	void end();
	std::thread run();		// funkcja dzia³aj¹ca w tle i nas³uchuj¹ca 
	void listen();

	int available(); // funcja sprawdza czy sa jakieœ dane do odczytu 
	char read();
	void write();

	void flush(); // funkcja czeka a¿ wszystkie dane zostan¹ wys³ane 


	//bool transmit();
	std::string recive();

};

