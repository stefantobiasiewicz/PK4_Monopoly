#include "Protokol.h"

sf::Packet Protokol::getPakiet()
{
	return this->pakiet;
}

Protokol::Protokol(sf::Packet& otrzymany_pakiet)
{
	pakiet = otrzymany_pakiet;
	rozpakuj();
}


Packet_Wiezienie::Packet_Wiezienie(int liczba_kolejek_do_odczekania) : Protokol()
{
	pakiet << WIEZIENIE;
	pakiet << liczba_kolejek_do_odczekania;
}

int Packet_Wiezienie::getLiczbaKolejek()
{
	return liczba_kolejek;
}

void Packet_Wiezienie::rozpakuj()
{
	std::string pom;
	pakiet >> pom;
	pakiet >> liczba_kolejek;
}

Packet_Czynsz_Zap::Packet_Czynsz_Zap(std::string nick_plat, std::string nick_odb, int kwota)
{
	pakiet << CZYNSZ;
	pakiet << nick_plat;
	pakiet << kwota;
	pakiet << nick_odb;
}

void Packet_Czynsz_Zap::rozpakuj()
{
	std::string pom;
	pakiet >> pom;
	pakiet >> nick_platnika;
	pakiet >> kwota;
	pakiet >> nick_wlasciciela;
}

std::string Packet_Czynsz_Zap::getNickPlatnika()
{
	return nick_platnika;
}

std::string Packet_Czynsz_Zap::getNickOdbiorcy()
{
	return nick_wlasciciela;
}
int Packet_Czynsz_Zap::getKwota()
{
	return kwota;
}
