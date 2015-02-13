 #include <list>
using namespace std;

class Liaison; 

class Station {
	private:
		string _nomStation;
		list<Liaison*> _liaisonsSuivantes;
		bool _dejaPasse;
		double _cout;
	    Station* _stationPrecedente;   // station de laquelle on vient
	public:
		// constructeur
		Station(string initNom) ;
		//accesseurs
		string getNomStation();
		list<Liaison*> getLiaisonsSuivantes();
		bool getDejaPasse();
		double getCout();
	    Station* getStationPrecedente() ;

		void setNomStation(string nouvNom);
		void setLiaisonsSuivantes(list<Liaison*> nouvList);
		void setDejaPasse(bool nouvPasse);
		void setCout(double nouvCout);
	    void setStationPrecedente(Station*) ;
		void ajouteLiaison(Liaison*);
};
 