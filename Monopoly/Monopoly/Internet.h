#pragma once
#include"SFML/Network.hpp"
#include <iostream>
#include <list>
#include <thread>
#include <vector>

class Internet
{
private:

	bool SerCli; // serwer - 0 klient - 1

	sf::IpAddress IPserv; // ip serwera 
	int port;

	std::vector<sf::TcpSocket*> sockets;	// wektor soketów 
	sf::TcpListener listener;

	bool isConnected;

public:
	Internet(bool sercli , int port); // konstruktor serwera 
	Internet(bool sercli , sf::IpAddress Serv, int port); // konstruktor klienta 

	void setIP(sf::IpAddress Serv);	// ustawia ip
	void setPort(int port);

	sf::Socket::Status setConnection();	// funkcja ³aczaca komputery 

	void Send(sf::Packet packet, int kt = 0 /* oznacza z którym soketem chcemy rozmawiac */);		// funkcja wsy³ajaca dane
	bool Recive(sf::Packet& packet, int kt = 0 /* oznacza z którym soketem chcemy rozmawiac */);	// funkcja zwraca ture gdy odebra³a nowe dane


	~Internet();
};

