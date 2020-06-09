#include "Internet.h"


Internet::Internet(char type , sf::IpAddress ip ) : connectionType(type), ip(ip)
{
	this->watek = nullptr;

	if (type == 's')
	{
		this->listener.listen(60123);
		this->listener.accept(this->socket);
	}
	else if (type == 'c')
	{
		sf::Socket::Status status = this->socket.connect(this->ip, 60123);
		if (status != sf::Socket::Done)
		{
			// error...
		}
	}

}

void Internet::begin() // funkcja w³¹czaj¹ca transmisje
{
	this->watek = &this->run();
}
void Internet::end()
{
	this->watek->~thread();
	this->watek = nullptr;
}

std::thread Internet::run()
{
	return std::thread(&Internet::run, this);
}
void Internet::listen()
{
	/// funkcja ktora wype³nia liste danych odczytanych z tcp
}

int Internet::available()
{
	return dane.size();
}
char Internet::read()
{
	if (this->socket.receive(this->Packet_data) != sf::Socket::Done)
	{

	}
//	char data = dane.front();
//	dane.pop_front();
//	return data;
	return 'a';
}
void Internet::write()
{
	if (this->socket.send(this->Packet_data) != sf::Socket::Done)
	{

	}
}

void Internet::flush() // funkcja czeka a¿ wszystkie dane zostan¹ wys³ane 
{


}