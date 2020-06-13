#pragma once
#include"SFML/Network.hpp"
#include <iostream>
#include <list>
#include <thread>
#include <vector>

#define INTERNET_PORT 64003

class Internet
{
private:

	bool isClient; // serwer - 0 klient - 1

	sf::IpAddress IPserv; // ip serwera 
	int port;

	std::vector<sf::TcpSocket*> sockets;	// wektor soketów 
	sf::TcpListener listener;

	sf::SocketSelector selector;

	bool isConnected;

public:
	Internet(bool isClient, int port); // konstruktor serwera 
	Internet(bool isClient, sf::IpAddress Serv, int port); // konstruktor klienta 

	void setIP(sf::IpAddress Serv);	// ustawia ip
	void setPort(int port);

	sf::Socket::Status setConnection();	// funkcja ³aczaca komputery 

	void Send(sf::Packet packet, int kt = 0 /* oznacza z którym soketem chcemy rozmawiac */);		// funkcja wsy³ajaca dane
	bool Recive(sf::Packet& packet, int kt = 0 /* oznacza z którym soketem chcemy rozmawiac */);	// funkcja zwraca ture gdy odebra³a nowe dane

	int getClientCount();

	~Internet();
};

