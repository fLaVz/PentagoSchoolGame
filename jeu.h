#ifndef jeu_H
#define jeu_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "plat.h"
#include "player.h"
#include "ia.h"

using namespace std;

//CETTE CLASSE CONTIENT LES PARAMETRES DU JEU

class jeu
{

	plat p;
	string m_gameState;
	player * count[2];		//nombre de joueurs
	string date;			//date de debut de la partie
	string mode;			//classique ou perso
	string type;			//pvp ou pvia
	int diff;				//difficultée choisie, regle la profondeur de l'ia, 
							//plus la difficulté est grande plus la prondeur et haute
			

	public :
	
	jeu();
	void Set();
	void reset(int &id);
	//ACCESSEURS ET MUTATEURS
	void setGameState(string gameState);
	string getGameState();

	void setMode(string mode);
	string getMode();
	
	void setType(string type);
	string getType();

	void setDiff();

	int ** getTab();
	int getSize();

	void getPlayerList();
	string getPlayerName(int playerid);
	void renameToBot();

	void draw(sf::RenderWindow &window);
	void setPauseGame(sf::RenderWindow &window);
	////////////////////////////////////

	void update(sf::RenderWindow &window);
	int placeButton(sf::RenderWindow &window, int &cpt);
	int rotate(sf::RenderWindow &window, int &cpt);

	void save();
	void load();
	void run();

	int botPlay(ia bot, int cpt);
	int playerPlay(sf::RenderWindow &window, int cpt);

};
#endif
