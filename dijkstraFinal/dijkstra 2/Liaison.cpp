#ifndef LIAISON_H
#define LIAISON_H
#include "Liaison.h"
#endif
Liaison::Liaison(double initCout, Station* initDestination)
{
		_duree= initCout;
		_destination= initDestination;
}
double Liaison::getDuree()
{
	return _duree;
}
Station*  Liaison::getDestination()
{
	return _destination;
}
void Liaison::setDuree(double nouvDuree)
{
	_duree = nouvDuree;
}
void Liaison::setDestination(Station* nouvStation)
{
	_destination = nouvStation;
}
