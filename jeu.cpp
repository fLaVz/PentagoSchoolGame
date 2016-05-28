#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include "jeu.h"

using namespace std;
using namespace sf;

jeu::jeu() {

	time_t timer = time(NULL);

	m_gameState = "MENU1";
	count[0] = new player(1);
	count[1] = new player(2);
	date = ctime(&timer);
	mode = "";
	type = "";
	diff = 5;
}

void jeu::reset(int &id) {
	p.reset(id);
}



//Etat du jeu, si on est dans un menu ou si le jeu tourne
void jeu::setGameState(string gameState) {

	m_gameState = gameState;
}

//On recupere l'état du jeu
string jeu::getGameState() {

	return m_gameState;
}

//definit le mode
void jeu::setMode(string mod) {
	this->mode = mod;
}

//recupere le mode
string jeu::getMode() {
	return this->mode;
}

//definit le type
void jeu::setType(string typ) {
	this->type = typ;
}

//retourne le type
string jeu::getType() {
	return this->type;
}

//retourne le tableau
int ** jeu::getTab() {
	return p.getPlat();
}

//retourne la taille du tableau
int jeu::getSize() {
	return p.getSize();
}

void jeu::setDiff() {
	cout << "Entrez la difficulté : 1 very easy, 3 medium, 5 hard, 7 very hard" << endl;
	cin >> diff;

}

//retourne la liste de joueurs
void jeu::getPlayerList() {

	player * a, * b;
	a = count[0];
	b = count[1];

	cout << a->name << b->name << endl;
}

//Renvoie le nom du joueur spécifié
string jeu::getPlayerName(int playerid) {

	string a = count[playerid-1]->getName();

	return a;
}





//Renomme le joueur 2 pour faire comprendre que c'est un bot
void jeu::renameToBot() {

	count[1]->rename("BOT"); 
}



//Affiche le plateau et les pions
void jeu::draw(RenderWindow &window) {

	p.draw(window);
}

//////////GESTION DE L'INTERFACE GRAPHIQUE/////////////////


//Permet de placer un bouton
int jeu::placeButton(RenderWindow &window, int &cpt) {	

	int p1 = p.check1(window, cpt); 

	if(p1 == 3) { // SI un des deux hjoueurs a gagné
		if(cpt == 1) { // joueur 2 car cpt changé dans la fonction assign
			cout << count[1]->name << " : WINNNNNNNNNNNERRRRRRRRRR" << endl;
			window.close();
		}else{ //joueur 1 
			cout << count[0]->name << " : WINNNNNNNNNNNERRRRRRRRRR" << endl;
			window.close();
		}
	}else if(p1 == 2) { // Si le coup est placé
		cout << "clic" << endl;
		p.display();
		return 1;
	}else {
		return 0; // si rien ne se passe
	}	
}

//Appelle la rotation d'un sous tableau
int jeu::rotate(RenderWindow &window, int &cpt) {

	int id = 0;
	int test = p.rotateSprite(window, cpt, id);
	
	if(test == 2) {
		p.display();
		p.update();
		return 1;								//L'autre joueur joue
	}else if(test == 3) {		//winner!
		p.display();
		cout << count[id-1]->name << " : WINNNNNNNNNNNERRRRRRRRRR" << endl;
		window.close();
	}else {
		return 0; //il ne se passe rien
		
	}
}

void jeu::setPauseGame(RenderWindow &window) {

	p.pauseGame(window);
}


//Permet de sauvegarder une partie
void jeu::save() {

	//On crée un fichier qui contient la matrice avec les pions placés par les joueurs 
	
	int ** saveTab;
	saveTab = p.getTab();

	string path = "saved/save.txt";

	ofstream file(path.c_str(), ios::out | ios::trunc);

    	if(file) {

    		//file << date; //stocke la date du game
    		file << type << " ";
    		for(int i = 0; i < 6; i++)
    			for(int j = 0; j < 6; j++)
    				file << saveTab[i][j]; //stocke la matrice
      		file.close(); 
        }else {
        	cout << "Ouverture impossible !" << endl;
        }

                
    cout << "game succesfully saved !" << endl;
}


//Permet de charger une partie
void jeu::load() {

	int size = getSize();
	int cpt = 0;
	int value = 0;
	ifstream file("saved/save.txt", ios::in);  // on ouvre le fichier

    if(file) {

    	string name; //chaine qui contiendra la matrice
    	string type; //chaine qui contien le type de jeu.

    	file >> type >> name;
   	 		
 		cout << type << " : " << name << endl;

   	 	setType(type);	

   	 	for(int i = 0; i < size; i++)
    		for(int j = 0; j < size; j++) {
    			char a = name[cpt];
    			value = a - '0';
    			cpt++;
    			p.assign(i, j, value); //on assigne chaque valeur du tableau a ses coordonnées
    		}

    	file.close();
    }
    else {
    	cerr << "Impossible d'ouvrir le fichier !" << endl;
    }   
    	
}


//////////FIN DE LA GESTION DE L'INTERFACE GRAPHIQUE/////////////////


/////////GESTION DE LA CONSOLE////////////////////

void jeu::run() {

	vector<int> coord; 
	bool busy;
	int id = 0;

	p.setSize();
	p.setWinConditions();
	setDiff();

	
	p.display();

	while(42) {

		coord = count[0]->play();
		busy = p.isBusy(coord);
		while(busy == false) {
			coord = count[0]->play();
			busy = p.isBusy(coord);
		}
		p.assignConsole(coord, 1);

		p.display();
		if (p.verify(id) == true) {
			cout << count[id-1]->name << " GAGNE !" << endl << endl;
			break;
		}
		p.rotate();
		if (p.verify(id) == true) {
			cout << count[id-1]->name << " GAGNE !" << endl << endl;
			break;
		}
		p.display();
			


		coord = count[1]->play();
		busy = p.isBusy(coord);
		while(busy == false) {
			coord = count[1]->play();
			busy = p.isBusy(coord);
		}
		p.assignConsole(coord, 2);

		p.display();
		if(p.verify(id) == true) {
			cout << count[id-1]->name << " GAGNE !" << endl << endl;
			break;
		}
		p.rotate();
		if (p.verify(id) == true) {
			cout << count[id-1]->name << " GAGNE !" << endl << endl;
			break;
		}
		p.display();
	}

	cout << "Fin de la partie !" << endl;

}
/////////FIN DE LA GESTION DE LA CONSOLE////////////////////



////////GESTION DU MODE PVIA/////////////////////////

int jeu::botPlay(ia bot, int cpt) {

	vector<int> test;
	int id = 2;
	int ** tab = p.getPlat();
	int size = getSize();

	test = bot.think(tab, size, 5);

	cout << test[0] << " : " << test[1] << " : " << test[2] << endl;
	p.assignIa(test, cpt);

	if(p.verify(id)) {
		p.display();
		cout << count[id-1]->name << " : WINNNNNNNER" << endl;
		return 3;
	}

	p.update();

	string minTab;
	if(test[2] == 0) {
		minTab = "A"; 
		p.rotateRight(minTab);
	}
	if(test[2] == 1) {
		minTab = "A"; 
		p.rotateLeft(minTab);
	}
	if(test[2] == 2) {
		minTab = "B"; 
		p.rotateRight(minTab);
	}
	if(test[2] == 3) {
		minTab = "B"; 
		p.rotateLeft(minTab);
	}
	if(test[2] == 4) {
		minTab = "C"; 
		p.rotateRight(minTab);
	}
	if(test[2] == 5) {
		minTab = "C"; 
		p.rotateLeft(minTab);
	}
	if(test[2] == 6) {
		minTab = "D"; 
		p.rotateRight(minTab);
	}
	if(test[2] == 7) {
		minTab = "D"; 
		p.rotateLeft(minTab);
	}
		
	p.update();

	if(p.verify(id)) {
		p.display();
		return 3;
	}

	p.display();
	return 1;
}

int jeu::playerPlay(RenderWindow &window, int cpt) {


	int p1 = p.check1(window, cpt); 

	if(p1 == 3) { // SI un des deux hjoueurs a gagné
		if(cpt == 1) { // joueur 2 car cpt changé dans la fonction assign
			cout << count[1]->name << " : WINNNNNNNNNNNERRRRRRRRRR" << endl;
			window.close();
		}else{ //joueur 1 
			cout << count[0]->name << " : WINNNNNNNNNNNERRRRRRRRRR" << endl;
			window.close();
		}
	}else if(p1 == 2) { // Si le coup est placé
		cout << "clic" << endl;
		p.display();
		p.update();
		return 1;
	}else {
		return 0; // si rien ne se passe
	}	
}



/////FIN GESTION DE L'IA////////////////////////