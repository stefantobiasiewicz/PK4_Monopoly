#include "Internet.h"



Internet::Internet(bool isClient, int port) // konstruktor serwera 
{
	if (isClient)
	{
		std::cerr << "zly konstruktor \n";
		return;
	}
	this->isClient = isClient;
	this->port = port;
	this->isConnected = false;
	this->listener.setBlocking(false);	// ustawienie trybu nie blokujacego 
	//this->selector(listener);
	if (this->listener.listen(this->port) != sf::Socket::Done)
	{
		// error...
		std::cerr << "nie znaleziono portu listener error \n";
	}
}
Internet::Internet(bool isClient, sf::IpAddress Serv, int port) // konstruktor klienta
{
	if (!isClient)
	{
		std::cerr << "zly konstruktor \n";
		return;
	}
	this->isClient = isClient;
	this->IPserv = Serv;
	this->port = port;
	this->isConnected = false;
	sf::TcpSocket *client = new sf::TcpSocket;
	//client->setBlocking(false); // ustawienie trybu nie blokujacego 
	this->sockets.push_back(client); // pierwszy socket w tablicy i jedyny to jestem ja 
}

void Internet::setIP(sf::IpAddress Serv)	// ustawia ip
{
	this->IPserv = Serv;
}
void Internet::setPort(int port)
{
	this->port = port;
}

sf::Socket::Status Internet::setConnection()	// funkcja ³aczaca komputery 
{
	sf::Socket::Status status;
	if (this->isClient)	// klient
	{
		status = this->sockets[0]->connect(this->IPserv, this->port , sf::seconds(1));
		if (status != sf::Socket::Done)
		{
			// error...
			std::cerr << "blad polaczenia z serverem\n";
		}
		else
		{
			this->isConnected = true;
			this->sockets[0]->setBlocking(false);		// ustawienie trybu nieblokujacego 
		}

	}
	else	// server
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		status = listener.accept(*client);
		if (status != sf::Socket::Done)
		{
			// error...
			delete client;
			std::cerr << "blad polaczenia z socketem ? ? ? \n";   //*************************************************************
		}
		else
		{
			client->setBlocking(false);	// ustawienie soketu w trybie nie blikujacym 
			this->sockets.push_back(client);
		}
	}
	return status;
}

void Internet::Send(sf::Packet packet, int kt)		// funkcja wsy³ajaca dane
{
	sf::Socket::Status state = sockets[kt]->send(packet);
	while(state == sf::Socket::Partial)
	{
		state = sockets[kt]->send(packet);
	}
}
bool Internet::Recive(sf::Packet& packet, int kt)	// funkcja zwraca ture gdy odebra³a nowe dane
{
	sf::Socket::Status state = sockets[kt]->receive(packet);
	if (state == sf::Socket::Done)
	{
		return true;
	}
	return false;
}

int Internet::getClientCount()
{
	return sockets.size();
}

void Internet::SendAll(sf::Packet pack)
{
	for (int i = 0; i < this->sockets.size(); i++)
	{
		this->Send(pack, i);
	}
}

int Internet::RecieveAll(sf::Packet& pack)
{
	for (int i = 0; i < this->sockets.size(); i++)
	{
		if (this->Recive(pack, i))
			return i;
	}
	return -1;
}



Internet::~Internet()
{
	for (auto all : sockets)
	{
		delete all;
	}
}