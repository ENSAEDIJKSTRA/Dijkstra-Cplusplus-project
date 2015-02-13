class Station;

class Liaison 
{
	private :
		double _duree;
		Station* _destination;
	public :
		Liaison(double initCout, Station* initDestination);

		double getDuree();
		Station* getDestination();

		void setDuree(double nouvDuree);
		void setDestination(Station* nouvStation);
};