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
	char connectionType; // czy prgoram b�dzie dzi�� jako server czy jako klijent

	std::list<char> dane;

	sf::Packet Packet_data;
	char data[100];

	std::thread* watek;

	//domy�lnie w�aczany jest tryb servera 
	Internet(char type , sf::IpAddress ip );
	void begin(); // funkcja w��czaj�ca transmisje
	void end();
	std::thread run();		// funkcja dzia�aj�ca w tle i nas�uchuj�ca 
	void listen();

	int available(); // funcja sprawdza czy sa jakie� dane do odczytu 
	char read();
	void write();

	void flush(); // funkcja czeka a� wszystkie dane zostan� wys�ane 


	//bool transmit();
	std::string recive();

};

