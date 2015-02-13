/*
   Chemin le plus court (Dijkstra) 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

#include "Station.h"
#include "Liaison.h"

using namespace std;

// comparaison pour une structure de type queue permet d'avoir le plus petit élément au début
// ------------------------------------------------------------------------------------------
struct compare
{
   bool operator()(Station* &ele1,Station* &ele2)const
   {
      return ele2->getCout() < ele1->getCout();      
	}
};
//---------------------------------------------
// algorithme de Dijkstra sur le plan de métro
//---------------------------------------------
void dijkstra(Station* stationDepart ,Station* stationArrivee,map<string,Station*> &lePlan)
{
	// On parcourt le plan de métro (= le graphe) afin d'initialiser les informations de chaque station  
	// permettant de calculer le trajet optimal

	map<string,Station*>::iterator iterStat;
	for(iterStat = lePlan.begin(); iterStat != lePlan.end(); iterStat++)
	{
		(*iterStat).second->setCout(numeric_limits<double>::max( )); 
		(*iterStat).second->setStationPrecedente(0);
		(*iterStat).second->setDejaPasse(false);
	}

	double leCout;
	// création d'une priority queue, comparaison selon critère du coût
	priority_queue<Station*, deque<Station*>, compare> pq; 
	// placement de station de départ dans la queue. (Initialisation)
	pq.push(stationDepart);	
	// le coût de la station de départ est positionné à 0
	stationDepart->setCout(0);
	// on repète le traitement jusqu'à ce que la queue soit vide
	while(pq.empty() == false)
	{
		// création d'un pointeur (de nom de curr) sur la station (présente dans la queue) 
		// ayant le plus petit coût 
		Station* curr = pq.top();  
		// on supprime l'élément (que l'on vient de récupérer) de la queue
		pq.pop();  
		// on indique que l'on a traité cette station (pointée par curr)
		curr->setDejaPasse(true);

		// Création d'un itérateur sur les liaisons de la station. (liste liaisonsSuivantes)
		list<Liaison*>::iterator iterLiaison;
		list<Liaison*> lesLiaisons = curr->getLiaisonsSuivantes();

		// on parcourt toutes les stations suivantes de curr
		for(iterLiaison = lesLiaisons.begin(); iterLiaison != lesLiaisons.end(); iterLiaison++)
		{
			//on récupère une station suivante de la station en cours d'analyse (pointée par curr)
			Station* uneStationSuivante = (*iterLiaison)->getDestination(); 

			// si la station n'a pas encore été traitée on la prend en compte
			if(uneStationSuivante->getDejaPasse() == false)
			{
				// on calcule le cout = durée de la liaison +  cout de la station en cours d'analyse (pointée par curr)
				double dur = (*iterLiaison)->getDuree();
				double co = curr->getCout();
				leCout = dur +co;
				
				// on calcule le min entre le coût déjà enregistré sur la station suivante 
				// et le coût que l'on vient de calculer  contenu dans leCout
				if(leCout < uneStationSuivante->getCout())
				{
					// on met à jour avec le min
					uneStationSuivante->setCout(leCout);
					// on garde la station d'où l'on vient
					uneStationSuivante->setStationPrecedente(curr);
				}
				// on ajoute la station suivante dans la queue
				pq.push(uneStationSuivante);
			}
		}
	}

	// ----------------------------------------------
	// Affichage de la durée du chemin le plus court
	// ----------------------------------------------
	cout << " Le chemin le plus court dure " << stationArrivee->getCout() << " minutes";

	// ----------------------------------------------------------------
	// Affichage des stations correspondant au chemin le plus court
	// ----------------------------------------------------------------
	// on part de l'arrivée pour trouver les stations du chemin le plus court
	// les noms des stations concernées sont mis dans la liste trajetOpt
	Station* uneStation;
	uneStation = stationArrivee->getStationPrecedente();
	list<string> trajetOpt;
	trajetOpt.push_front(stationArrivee->getNomStation());
	while(uneStation != 0)
	{
		trajetOpt.push_front(uneStation->getNomStation());
		uneStation=uneStation->getStationPrecedente();
	}

	// on affiche le nom des stations contenues dans liste trajetOpt
	list<string>::iterator iteParcourir;
	cout << " Vous devez passer par les stations : " <<endl;
	for(iteParcourir=trajetOpt.begin(); iteParcourir!=trajetOpt.end(); iteParcourir++)
	{
		cout << *iteParcourir << endl;
	}
	cout << endl;
}

// --------------------------------------------------------------------------------------------------
// création d'une fonction rechercheStation qui recherche si une station existe. Si
// elle n'existe pas on crée la station. Dans tous les cas, on retourne un pointeur sur une station
// --------------------------------------------------------------------------------------------------
Station* rechercheStation(map<string,Station*> &plan, string name)
{ 
	Station* pstation = plan[name]; // prend la valeur qui a la clé name.
	if ( pstation == 0 ) // s'il n'existe pas de station avec le nom name, on la créer sur la heap.
		pstation = plan[name] = new Station(name);
	return pstation;
}

// ------------------------------------------------------------------
// création du plan du métro (= graphe) à partir d'un fichier .txt
// ------------------------------------------------------------------
void creationGraphe(string filename, map<string,Station*> &laMap) 
{
    ifstream inf(filename); // création d'un objet inf de type ifstream qui permet
    string de, vers;
    double duree;
	Station* orig;
	Station* dest;
	Liaison* laLiaison;
    while ( !inf.eof() ) 
    {
        inf >> de >> vers >> duree;
        if ( !inf.eof()  ) 
        {
			// dans un sens
            dest = rechercheStation(laMap,vers); 
            orig = rechercheStation(laMap,de);
            laLiaison = new Liaison(duree,dest);
            orig->ajouteLiaison(laLiaison);
			
			// dans l'autre
			dest = rechercheStation(laMap,de); 
            orig = rechercheStation(laMap,vers);
            laLiaison = new Liaison(duree,dest);
            orig->ajouteLiaison(laLiaison);
        }
    }
}

// -------------------------
//   programme principal
//  qui pilote le traitement
// -------------------------
void main()
{
	// ---------------------------------------
	// création du plan du métro (=le graphe)
	// ---------------------------------------
    // création d'une collection de type map ayant pour clé un nom de station 
	// et pour valeur un pointeur sur une station
	map<string,Station*> planMetro;

	// appel de la fonction creationGraphe qui va lire les caractéristiques du graphe à partir d'un fichier texte
	// et créer toutes les stations dans la map planMetro (=le graphe)
    creationGraphe("graph.txt", planMetro);

	//affichage du plan du métro (pour vérifier que le chargement est correct) peut être enlevé 
    cout << "Affichage du plan du metro" << endl;
	map<string,Station*>::iterator iterMap;
	for(iterMap = planMetro.begin(); iterMap != planMetro.end(); iterMap++) 
	{
		//affichage du nom de la station
		cout << (*iterMap).first << endl; //first indique qu'on prend la clé
		//on récupère la liste de liaisons. 
		list<Liaison*> lesLiaisons = (*iterMap).second->getLiaisonsSuivantes();
		//création d'un itérateur sur les liaisons
		list<Liaison*>::iterator iterLiaison;
		//on parcourt la liste des liaisons avec l'itérateur, on affiche son poids et la station pointée par destination
		for(iterLiaison = lesLiaisons.begin(); iterLiaison != lesLiaisons.end(); iterLiaison++)
		{
			cout << "   -> " << (*iterLiaison)->getDestination()->getNomStation() << " distance " << (*iterLiaison)->getDuree() <<endl;
		}
    }
	 
	// ----------------------------------
	// recherche du chemin le plus court
	// ----------------------------------
    string depart,arrivee, reponse;
    do
	{

		// on demande à l'utilisateur de saisir la station de départ 
		Station* staDep;

		// tant que le nom de station n'est pas valide, on redemande à l'utilisateur de saisir un autre nom
		do
		{
			cout << " Saisir le nom de la station de depart" << endl;
			cin >> depart;

			//on vérifie que la station de départ existe bien
			iterMap = planMetro.find(depart); 
	
			if(iterMap==planMetro.end())
			{
				cout << "La station " << depart << " n'est pas dans le plan de metro " << endl;
			}
			else
			{
				staDep = planMetro[depart];
			}
		} while(iterMap==planMetro.end());
		

		// on demande à l'utilisateur de saisir la station d'arrivée
		Station* staArr;
		do
		{

			cout << " Saisir le nom de la station d'arrivee" << endl;
			cin >> arrivee;

			iterMap = planMetro.find(arrivee); 
	
			if(iterMap==planMetro.end())
			{
				cout << "La station " << arrivee << " n'est pas dans le plan de metro " << endl;
			}
			else
			{
				staArr = planMetro[arrivee];
			}
		} while(iterMap==planMetro.end());
	
		// on appelle l'algorithme de Dijkstra
		dijkstra(staDep,staArr,planMetro);
		
		// l'utilisateur est invité à faire une nouvelle recherche
        cout << "Veuillez entrer O pour faire une autre recherche " << endl;
        cin >> reponse;
    } while("O" == reponse  || "o"==reponse );
}
