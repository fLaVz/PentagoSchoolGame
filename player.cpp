#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <fstream>
#include "player.h"

int player::playerId = 0;

using namespace std;


player::player()
{
	name = "";
	nb_coups = 0;
}

player::player(int player_count) {

	string s;					//Conversion d'integer vers string pour 
	stringstream out;			//pouvoir identifier quel joueur doit 
	out << player_count;		//choisir son alias
	s = out.str();

	name = s;
	nb_coups = 0;

	Set();

}


void player::Set()		//Affectation d'un alias perso pour la clarté de la sauvegarde
{ 
	cout << "Choisissez un alias : " << "(joueur " << name << ")" << endl;
	cin >> name;
	cout << endl;
}


void player::rename(string botname) {

	name = botname;
}

string player::getName() {

	return name;
}

vector<int> player::play() {
	nb_coups++;

	vector<int> coord;
	int coordx;
	int coordy;

	cout << "Au tour de " << name << endl;
	cout << "Entrez les coordonnées en x : " << endl;
	cin >> coordx;
	coord.push_back(coordx);


	cout << "Puis en y :" << endl;
	cin >> coordy;
	coord.push_back(coordy);

	return coord;

}