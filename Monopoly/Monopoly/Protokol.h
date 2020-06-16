#pragma once
#include <SFML/Network.hpp>

#define WIEZIENIE "WIEZIENIE"
#define CZYNSZ "CZYNSZ"

class Protokol
{
protected:
	sf::Packet pakiet;
	Protokol() {}
	Protokol(sf::Packet& otrzymany_pakiet);
	~Protokol() {}
	virtual void rozpakuj() {}
public:
	sf::Packet getPakiet();
};

class Packet_Wiezienie : public Protokol
{
	int liczba_kolejek;

	virtual void rozpakuj();

public:
	Packet_Wiezienie(int liczba_kolejek_do_odczekania);
	Packet_Wiezienie(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Wiezienie() {}
	int getLiczbaKolejek();
};

class Packet_Czynsz_Zap : public Protokol
{
	std::string nick_platnika;
	std::string nick_wlasciciela;
	int kwota;

	virtual void rozpakuj();

public:
	Packet_Czynsz_Zap(std::string nick_plat, std::string nick_odb, int kwota);
	Packet_Czynsz_Zap(sf::Packet& otrzymany_pakiet) : Protokol(otrzymany_pakiet) {}
	~Packet_Czynsz_Zap() {}
	std::string getNickPlatnika();
	std::string getNickOdbiorcy();
	int getKwota();
};