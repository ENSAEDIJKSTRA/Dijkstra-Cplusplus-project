//
//#include "Graphe.h"
//// #include "Station.h"
//using namespace std;
//
//class Station;
//
//
//Station* Graphe::rechercheStation(string name)
//{ 
//
//	Station* pstation = lesStations[name]; // prend la valeur qui a la clé name.
//	if ( pstation == 0 ) // s'il n'existe pas de station ac le nom name, on la créer sur la heap.
//		pstation = lesStations[name] = new Station(name);
//	return pstation;
//}