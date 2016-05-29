#ifndef plat_H
#define plat_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//CETTE CLASSE CONTIENT LE PLATEAU DE JEU

class plat
{
	int ** tab;					//La matrice qui gere les pions placés par les joueurs
	int size;					//Taille de la matrice
	int serie;					//Nombre de pions a aligner pour gagner

	//SPRITES
	sf::Sprite sousTab;			//Le sprite qui contient la texture d'un sous tableau
	sf::Sprite rotation;
	sf::Sprite * s_tab;
	sf::Sprite * s_rotation;
	sf::Sprite ** grid;			//La grille "transparente" on l'on peut placer des pions
	sf::Sprite pauseMenu;

	//TEXTURES
	sf::Texture tabTexture;		//La texture du sprite
	sf::Texture def;			//La texture invisible
	sf::Texture pionTexture1;	//La texture d'un pion
	sf::Texture pionTexture2;
	sf::Texture rotationTextureDroite; //La texture de l'icone de rotation
	sf::Texture rotationTextureGauche;
	sf::Texture pause;				//Texture du menu pause

	public :
	
	plat();

	//Accesseurs et mutateurs
	void Set();
	void reset(int &id);

	void setSize();
	int getSize();

	void setWinConditions();

	int ** getPlat();
	////////////////////////////

	void display();
	void draw(sf::RenderWindow &window);
	void pauseGame(sf::RenderWindow &window);

	int check1(sf::RenderWindow &window, int &cpt);

	bool isClicked(sf::RenderWindow &window, sf::Sprite &sprite);

	void assign(int k, int l, int &cpt);
	void assignConsole(vector<int> coord, int id);
	void assignIa(vector<int> coord, int id);

	void update();

	bool isBusy(int i, int j);
	bool isBusy(vector<int> coord);

	void modify();

	int rotateSprite(sf::RenderWindow &window, int &cpt, int &id);
	void rotateSpriteRight(int k);
	void rotateSpriteLeft(int k);

	bool verify(int & id);
	bool backtrack(int cpt, int check, int x, int y);

	void rotate();
	void rotateRight(string minTab);
	void rotateLeft(string minTab);

	int ** getTab();
	

};
#endif


/*///////////////////////////tab[i][j] rotate = tab[j][n-1 - i]
AG[i][j] = AG[n-1-j][i]*/