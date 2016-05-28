#ifndef player_H
#define player_H

#include <vector>
#include <iostream>

using namespace std;

//CETTE CLASSE DEFINIT UN JOUEUR

class player
{
	friend class jeu;

	string name;
	int nb_coups;		//Utilisation "competitive" -> chess like
	static int playerId;
	 

	public :
	
	player();
	player(int player_count);

	void Set();
	vector<int> play();

	void rename(string name);
	string getName();


	void Save(int ** tab, int taille, int player_count, string date, string mode, string type, string diff, player * a, player * b);
	void Load();

};
#endif