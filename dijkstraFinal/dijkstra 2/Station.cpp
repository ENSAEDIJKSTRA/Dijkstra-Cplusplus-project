#ifndef STATION_H
#define STATION_H

#include "Station.h"
#endif
Station::Station(string initNom)
{
	_nomStation=initNom;
	_dejaPasse=false;
	_cout=0;
}
string Station::getNomStation()
{
	return _nomStation;
}
list<Liaison*> Station::getLiaisonsSuivantes()
{
	return _liaisonsSuivantes;
}
bool Station::getDejaPasse()
{
	return _dejaPasse;
}
double Station::getCout()
{
	return _cout;
}
Station* Station::getStationPrecedente()
{
	return _stationPrecedente;
}
void Station::setNomStation(string nouvNom)
{
	_nomStation = nouvNom;
}
void Station::setLiaisonsSuivantes(list<Liaison*> nouvList)
{
	_liaisonsSuivantes = nouvList;
}
void Station::setDejaPasse(bool nouvPasse)
{
	_dejaPasse = nouvPasse;
}
void Station::setCout(double nouvCout)
{
	_cout = nouvCout;
}
void Station::setStationPrecedente(Station* nouvStation) 
{
	_stationPrecedente = nouvStation;
}
void Station::ajouteLiaison(Liaison* laLiaison)
{
	_liaisonsSuivantes.push_back(laLiaison);
}

