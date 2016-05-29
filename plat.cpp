#include <iostream>
#include <sstream>
#include "player.h"
#include "plat.h"
#include "button.h"

using namespace std;
using namespace sf;


plat::plat() {
	this->size = 6;                   //initialisation de la size -> modifiable plus tard
  this->serie = 5;                  //initialisation des conditions de victoire, modifiable

	tab = new int *[size];            //création de la matrice
	for(int k = 0; k < size; k++) {
		tab[k] = new int[size];
	}


	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++) {
			tab[i][j] = 0;
		} 

    //Tableau de sprite pour le nombre de sous tableau 
    s_tab = new Sprite[4];

    //Tableau de sprite pour les icones de rotation
    s_rotation = new Sprite[8];        

    //Declaration des textures pour les icones de rotation
    if(!rotationTextureDroite.loadFromFile("images/droite.png"))
      cout << "ERROR, Can't load texture located in images" << endl;
    else
      rotation.setTexture(rotationTextureDroite);

    if(!rotationTextureGauche.loadFromFile("images/gauche.png"))
      cout << "ERROR, Can't load texture located in images" << endl;
    else
      rotation.setTexture(rotationTextureDroite);

      rotation.setPosition(Vector2f(100, 150));
      s_rotation[0] = rotation;

      rotation.setTexture(rotationTextureGauche);
      rotation.setPosition(Vector2f(100, 250));
      s_rotation[1] = rotation;

      rotation.setTexture(rotationTextureDroite);
      rotation.setPosition(Vector2f(600, 150));
      s_rotation[2] = rotation;

      rotation.setTexture(rotationTextureGauche);
      rotation.setPosition(Vector2f(600, 250));
      s_rotation[3] = rotation;

      rotation.setTexture(rotationTextureDroite);
      rotation.setPosition(Vector2f(100, 350));
      s_rotation[4] = rotation;

      rotation.setTexture(rotationTextureGauche);
      rotation.setPosition(Vector2f(100, 450));
      s_rotation[5] = rotation;

      rotation.setTexture(rotationTextureDroite);
      rotation.setPosition(Vector2f(600, 350));
      s_rotation[6] = rotation;

      rotation.setTexture(rotationTextureGauche);
      rotation.setPosition(Vector2f(600, 450));
      s_rotation[7] = rotation;




    //Grille de sprite correspond aux emplacements ou l'on peu placer les pions
    grid = new Sprite *[size];            //création de la matrice
    for(int o = 0; o < size; o++) {
      grid[o] = new Sprite[size];
    }

    //Defiition des textures transparentes de grid
    if(!def.loadFromFile("images/default.png")) {
          cout << "ERROR, Can't load texture located in /images" << endl;
        }else {
          cout << "setTexture" << endl;
      }
      def.setSmooth(true);      //"lisse" la texture mais trop downscalé pour le moment


    if(!pionTexture1.loadFromFile("images/blueP.png")) {
          cout << "ERROR, Can't load texture located in /images" << endl;
    }else {
          cout << "PionTextureLoaded 1" << endl;
    }
      pionTexture1.setSmooth(true);

    if(!pionTexture2.loadFromFile("images/greenP.png")) {
          cout << "ERROR, Can't load texture located in /images" << endl;
    }else {
          cout << "PionTextureLoaded 2" << endl;
    }
      pionTexture2.setSmooth(true);

    
    //Assignation des positions des sprites ou l'on pourra placer les pions
    int x, y;
    x = 234;
    y = 167;


    for(int l = 0; l < size; l++) {
      for(int m = 0; m < size; m++) {
        //cout << x << " : " << y << endl; //Affichage des points d'origine des texures pour le calibrage
        grid[l][m].setTexture(def);
        grid[l][m].setPosition(Vector2f(x, y));
        grid[l][m].setScale(0.19, 0.19);    //Texture trop grande donc je la downscale

        if(m == 2)
          x += 37;
        if(m == 5) {
          y += 61;
          x = 183;
        }
      x += 51;
      }
      if(l == 2)
        y += 8;
    }

    //Initialisation des texures sur le sprite du sous tableau
    if(!tabTexture.loadFromFile("images/soustab.png"))
    cout << "ERROR, Can't load texture located in images/soustab.png" << endl;
  else
    sousTab.setTexture(tabTexture);

    sousTab.setScale(0.6, 0.6);
    sousTab.setPosition(Vector2f(210, 150));
    s_tab[0] = sousTab;

    sousTab.setPosition(Vector2f(400, 150));
    s_tab[1] = sousTab;

    sousTab.setPosition(Vector2f(210, 340));
    s_tab[2] = sousTab;

    sousTab.setPosition(Vector2f(400, 340));
    s_tab[3] = sousTab;

     if(!pause.loadFromFile("images/pause.png"))
      cout << "ERROR, Can't load texture located in images" << endl;
    else
      pauseMenu.setTexture(pause);
}


void plat::reset(int &id) {

  for (int i = 0; i < size; ++i)
  {
    for (int j = 0; j < size; ++j)
    {
      tab[i][j] = 0;
    }
  }
  id = 1;
  update();
}

void plat::setSize() {

  delete tab;
  int taille;

  cout << "Entrez la taille de tableau désiré : (6, 8, 10, 12 etc...)" << endl;
  cin >> taille;

  this->size = taille;

  tab = new int *[size];            
  for(int k = 0; k < size; k++) {
    tab[k] = new int[size];
  }


  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++) {
      tab[i][j] = 0;
    }  
}




void plat::setWinConditions() {

  cout << "Quel est le nombre de pions requis pour gagner ? " << endl;
  cin >> serie;

}




int plat::getSize() {

  return this->size;
}


int ** plat::getPlat() {

  return tab;
}



//Affiche la table de jeu dans la console
void plat::display() {

  int taille = getSize();
	int y = 1;

	cout << "AFFICHAGE DE LA TABLE DE JEU : " << endl;
	cout << endl;


	cout << "      A           B     " << endl;
	cout << "   1  2  3     4  5  6" << endl;

	for(int i = 0; i < size; i++) {
		cout << y << " ";
		y++;

			for(int j = 0; j < size; j++) {

				if(j == (size/2))
					cout << "   ";			//espacement des tables

				cout << "[" << tab[i][j] << "]";
			}
			if(i == (size/2)-1)
				cout << endl;				//espacement des tables

		cout << endl;
	}
	cout << "      C           D     " << endl;
	cout << endl;

}


//Affiche la table de jeu dans une fenetre SFML
void plat::draw(RenderWindow &window) {

  //Affichage des sous tableaux
  for(int i = 0; i < 4; i++)
      window.draw(s_tab[i]);

  //Affichage de la grille de sprite invisibles
  for (int j = 0; j < size; j++)
    for (int k = 0; k < size; k++) {
      window.draw(grid[j][k]);
    }

  //Affichage des icones de rotation
  for(int l = 0; l < 8; l++)
    window.draw(s_rotation[l]);
      
}

int ** plat::getTab() {
  
  return tab;
}



void plat::pauseGame(RenderWindow &window) {

  window.draw(pauseMenu);


}



//Verification que le joueur 1 joue
int plat::check1(RenderWindow &window, int &cpt) {
  
  int temp = cpt; //Pour verifier

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if((isClicked(window, grid[i][j]) == true && !isBusy(i, j))) {
        assign(i, j, cpt);
        if(verify(temp))
          return 3;         //Si le joueur a joué et gagné
        return 2;           //Si le joueur a joué mais pas gagné
      }
    }
  }
  return 0; //Si rien ne se passe
}

//Test pour savoir si un sprite a été clické
bool plat::isClicked(RenderWindow &av_Window, Sprite &p_sprite) {  

    int mouseX = Mouse::getPosition(av_Window).x;
    int mouseY = Mouse::getPosition(av_Window).y;

    if(mouseX > p_sprite.getPosition().x
    && mouseX < (p_sprite.getPosition().x + p_sprite.getGlobalBounds().width)
    && mouseY < (p_sprite.getPosition().y + p_sprite.getGlobalBounds().height)
    && mouseY > p_sprite.getPosition().y) {

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        }
        return false;
    }
    return false;
}

int plat::rotateSprite(RenderWindow &window, int &cpt, int &id) {

    int temp;
    if(cpt == 1)
      temp = 2;
    else
      temp = 1;
  
    for(int k = 0; k < 8; k++) {
        if(isClicked(window, s_rotation[k]) && k%2 == 0) {    //k % 0 pour savoir quel indice du tebleau de rotation a été clické
          rotateSpriteRight(k);
          if(verify(id))
            return 3;       //Gagne
          else
            return 2;         //rotation efectuée mais pas gagné
        }else if(isClicked(window, s_rotation[k]) && (k%2) == 1) {
          rotateSpriteLeft(k);
          if(verify(id))
            return 3;
          else
            return 2;
        }
        
    }
    return 1;    //Ne se passe rien

}



//Tourne un sous plateau vers la droite
void plat::rotateSpriteRight(int k) {

  cout << "RotateRight" << endl;
  string minTab;

  if(k == 0) {
    minTab = "A";
    rotateRight(minTab);
  }else if(k == 2) {
    minTab = "B";
    rotateRight(minTab);
  }else if(k == 4) {
    minTab = "C";
    rotateRight(minTab);
  }else if(k == 6) {
    minTab = "D";
    rotateRight(minTab);
  }

  update();
}


void plat::rotateSpriteLeft(int k) {

  cout << "RotateLeft" << endl;
  string minTab;

  if(k == 1) {
    minTab = "A";
    rotateLeft(minTab);
  }else if(k == 3) {
    minTab = "B";
    rotateRight(minTab);
    rotateRight(minTab);
    rotateRight(minTab);
  }else if(k == 5) {
    minTab = "C";
    rotateRight(minTab);
    rotateRight(minTab);
    rotateRight(minTab);
  }else if(k == 7) {
    minTab = "D";
    rotateRight(minTab);
    rotateRight(minTab);
    rotateRight(minTab);
  }

  update();

  
}


//Lis la matrice et affecte les textures en fonction
void plat::update() {

  for(int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {
        if(tab[i][j] == 1) {

          grid[i][j].setTexture(pionTexture1);
        }else if(tab[i][j] == 2)
        {
          
          grid[i][j].setTexture(pionTexture2);
        }else {

          grid[i][j].setTexture(def);
        }
      }
  }
}

//Affecte une valeur au tableau "console" et verifie en meme temps si la case est occupée
void plat::assign(int k, int l, int &cpt) {

        if(cpt == 1) {
          tab[k][l] = cpt;
          cpt = 2;
        }else if(cpt == 2) {
          tab[k][l] = cpt;
          cpt = 1;
        }

  update();
}

void plat::assignConsole(vector <int> coord, int id) {

  tab[coord[1]-1][coord[0]-1] = id;
}

void plat::assignIa(vector <int> coord, int id) {

  tab[coord[0]][coord[1]] = id;
}


//Teste une case pour savoir si elle est occupée
bool plat::isBusy(int i, int j) {

  if(tab[i][j] == 1 || tab[i][j] == 2) {
    cout << "busy" << endl;
    return true;
  }
  return false;
}

//VERSION CONSOLE
bool plat::isBusy(vector<int> coord) {


  if((coord[1]-1) < 0 || (coord[0]-1) < 0 || (coord[0]-1) > size || (coord[1]-1) > size) {
    cout << endl;
    cout << "//////////////////// Case inéxistante ! ///////////////////" << endl;
    cout << endl;
    return false;
  }else if(tab[coord[1]-1][coord[0]-1] == 1 || tab[coord[1]-1][coord[0]-1] == 2) {
    cout << endl;
    cout << "//////////////////// Case occupée ! ///////////////////" << endl;
    cout << endl;
    return false;
  }

  return true;  
}







//Verifie si le joueur a gagné ou pas
bool plat::verify(int & id) {

  bool test;
  cout << "VERIF" << endl;

  //On parcoure tout la table de jeu et on lance une vérification sur chaque pion placé
  for(int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {

        //Si un pion est dans la case i j, on vérifie
        if(tab[i][j] == 1 || tab[i][j] == 2) {     

          id = tab[i][j];     //On stocke la valeur a tester 1->player1, 2->player2
          test = backtrack(1, id, i, j); //on lance la verification

          if(test == true) {
            return true;
          }else {
            id = 0;
          } 
        } 
      }
  }
  return false;
}



bool plat::backtrack(int cpt, int check, int x, int y) {

  int i, j;
  //Variable pour reinitialiser la case a tester car plusieurs tests possibles
  i = x;
  j = y;
  //x et y inversés par rapport a l'affichage

    //Verification ligne
    while(y < 5 && tab[x][y+1] == check) {
      y++;
      cpt++;
      if(cpt == serie) {
        return true;
      }   
    }
    cpt = 1;
    x = i;
    y = j;

    //Verification colonne
    while (x < 5 && tab[x+1][y] == check) { 
      x++;
      cpt++;
      if(cpt == serie) {
        return true;
      }
    }
    cpt = 1;
    x = i;
    y = j;

    //Verification diagonale bas droite 
    while(x < 5 && y < 5 && tab[x+1][y+1] == check) { 
      x++;
      y++;
      cpt++;
      if(cpt == serie) {
        return true;
      }
    }
    cpt = 1;
    x = i;
    y = j;


    //Verification diagonale haut droite
    while( x >= 1 && tab[x-1][y+1] == check) {
      x--;
      y++;
      cpt++;
      if(cpt == serie) {
        return true;
      }
    }
  return false;
}


//Gere la rotation d'un sous-tableau
void plat::rotate() {

	string minTab;
	string sens;
	bool temp;

	

	//Saisie sécurisée non utilisée dans le pentagoSFML
	while(42) {
		cout << "Quel plateau voulez-vous tourner ? (A/B/C/D)" << flush << endl;
		cin >> minTab;
		cin.clear();

		if(minTab == "A")
			break;
		else if(minTab == "B")
			break;
		else if(minTab == "C")
			break;
		else if(minTab == "D")
			break;

		cout << "Désolé, je n'ai pas compris..." << endl;
	}

	while(42) {
		cout << "Dans quel sens ? (D/G)" << endl;
		cin >> sens;

		if(sens == "D")
			break;
		else if(sens == "G")
			break;

		cout << "Désolé, je n'ai pas compris..." << endl;
	}

	if(sens == "D") {
		rotateRight(minTab);
	}
	if(sens == "G") {
		rotateLeft(minTab);	
	}
}


void plat::rotateRight(string minTab) {

	int n = size/2;			//indice pour les plateaux de la table							
	int i,j,temp;
	int ** copy;				//tableau de copie
  int ** turn; 
	int x,y;
	x = y = 0;

	 //On crée un plateau vide qui servira a stocker le plateau choisi
  copy = new int *[n];            //création de la matrice
  for(int k = 0; k < n; k++) {
    copy[k] = new int[n];
  }

  for(i=0; i<n; i++) {  
    for(j=0; j<n; j++) {
      copy[i][j] = 0;
    }
  }

  turn = new int *[n];            //création de la matrice
  for(int k = 0; k < n; k++) {
    turn[k] = new int[n];
  }

  for(i=0; i<n; i++) {  
    for(j=0; j<n; j++) {
      turn[i][j] = 0;
    }
  }


  if(minTab == "A") {

    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
        copy[i][j] = tab[n-j-1][i];

      }
    }

    for(i = 0; i < n; i++) {
      for(j = 0; j < n; j++) {
        tab[i][j] = copy[i][j];
      }
    }

	}else if(minTab == "B") {

    //on copie la matrice
		for(i=0; i<n; i++) {
			x = 0;
     	for(j=n; j<size; j++) {
       	copy[y][x] = tab[i][j];
       	x++;
    	}
    	y++;
    }

    //on applique la rotation
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
        turn[i][j] = copy[n-j-1][i];
      }
    }


   		x = y = 0;
      //on recopie le tableau
   		for(i = 0; i < n; i++) {
   			x = 0;
       	for(j=n; j < size; j++) {
         	tab[i][j] = turn[y][x];
         	x++;
     		}
     		y++;
    	}


	}else if(minTab == "C") {

    //on copie la matrice
    for(i=n; i<n*2; i++) {
      x = 0;
      for(j=0; j<n; j++) {
        copy[y][x] = tab[i][j];
        x++;
      }
      y++;
    }

    //on applique la rotation
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
        turn[i][j] = copy[n-j-1][i];
      }
    }


      x = y = 0;
      //on recopie le tableau
      for(i=n; i<n*2; i++) {
        x = 0;
        for(j=0; j<n; j++) {
          tab[i][j] = turn[y][x];
          x++;
        }
        y++;
      }
		

	}else if(minTab == "D") {

    //on copie la matrice
    for(i=n; i<n*2; i++) {
      x = 0;
      for(j=n; j<n*2; j++) {
        copy[y][x] = tab[i][j];
        x++;
      }
      y++;
    }

    //on applique la rotation
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
        turn[i][j] = copy[n-j-1][i];
      }
    }


      x = y = 0;
      //on recopie le tableau
      for(i=n; i<n*2; i++) {
        x = 0;
        for(j=n; j<n*2; j++) {
          tab[i][j] = turn[y][x];
          x++;
        }
        y++;
      }
	}
  //update();
}


void plat::rotateLeft(string minTab) {

 rotateRight(minTab);
 rotateRight(minTab);
 rotateRight(minTab);

}