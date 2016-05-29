#include <iostream>
#include "ia.h"

using namespace std;

ia::ia() {

	currentPlayer = 2;

}


/////////////////////////ALGORITHME MIN-MAX ///////////////////////////////////////////////

vector<int> ia::think(int ** copy, int size, int profondeur) {

    int tab[6][6];

    for(int x=0; x<size; x++) {     //tableau de copie
      for(int y=0; y<size; y++) {
          tab[x][y] = copy[x][y];
      }
    }

	cout << "Ia is thinking..." << endl;

	vector<int> play;
	int tmp, tmpi, tmpj, tmpk, tmpl; // respectivement : la valeur max, coordonnées en i, j puis la sous table a tourner et enfin dans quel sens
  int minTab;
  int resetProfondeur = profondeur;
  int alpha = -1000;
  int beta = 1000;

	for(int i = 0; i < size; i++) {  //correspond aux colonnes
		for(int j = 0; j < size; j++) { //correspond au lignes
      for(int k = 0; k < 8; k++) { //correspond au plateau a tourner

      if(tab[i][j] == 0) {              //Si case vide

        tab[i][j] = 2;                  //on joue

        if(k == 0) {        
            profondeur = resetProfondeur; 
            minTab = 1;   
            rotateRight(tab, size, minTab);       //on teste la 1ere rotation

            tmp = min(tab, size, profondeur-1, alpha, beta); //au joueur de jouer

            if(alpha < tmp) {                 //comparaison coupure alpha beta
              alpha = tmp;
              tmpi = i;
              tmpj = j;
              tmpk = k;
            }
            rotateLeft(tab, size, minTab);    //on annule le coup
            tab[i][j] = 0;

          }


          else if(k == 1) {
            profondeur = resetProfondeur;
            minTab = 1;
            rotateLeft(tab, size, minTab);
            tmp = min(tab, size, profondeur-1, alpha, beta);

          if(alpha < tmp) {
            alpha = tmp;
            tmpi = i;
            tmpj = j;
            tmpk = k;
          }

       
          rotateRight(tab, size, minTab);
          tab[i][j] = 0;
          }


          else if(k == 2) {
            profondeur = resetProfondeur;
            minTab = 2;
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          if(alpha < tmp) {
              alpha = tmp;
            tmpi = i;
            tmpj = j;
            tmpk = k;
          }

             
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          }


          else if(k == 3) {
            profondeur = resetProfondeur;
            minTab = 2;
            rotateLeft(tab, size, minTab);
            tmp = min(tab, size, profondeur-1, alpha, beta);

          if(alpha < tmp) {
            alpha = tmp;
            tmpi = i;
            tmpj = j;
            tmpk = k;
          }

         
          
          rotateRight(tab, size, minTab);
          tab[i][j] = 0;
          }


          else if(k == 4) {
            profondeur = resetProfondeur;
            minTab = 3;
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          if(alpha < tmp) {
            alpha = tmp;
            tmpi = i;
            tmpj = j;
            tmpk = k;
          }

         
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;
          }


          else if(k == 5) {
            profondeur = resetProfondeur;
            minTab = 3;
            rotateLeft(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          if(alpha < tmp) {
            alpha = tmp;
            tmpi = i;
            tmpj = j;
            tmpk = k;
          }

          rotateRight(tab, size, minTab);
          tab[i][j] = 0;
          
          }


          else if(k == 6) {
            profondeur = resetProfondeur;
            minTab = 4;
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          if(alpha < tmp) {
            alpha = tmp;
            tmpi = i;
            tmpj = j;
            tmpk = k;
          }

     
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          }
          else if(k == 7) {
            profondeur = resetProfondeur;
            minTab = 4;
            rotateLeft(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

            if(alpha < tmp) {
              alpha = tmp;
              tmpi = i;
              tmpj = j;
              tmpk = k;
            }
          
            rotateRight(tab, size, minTab);
            tab[i][j] = 0;
          }
        }
        }
        
      }
     
		} 

	play.push_back(tmpi);
	play.push_back(tmpj);
  play.push_back(tmpk);

  cout << play[0] << " : " << play[1] << " : " << play[2] << endl;

	return play;
}




//Coup du joueur, doit être a la valeur minimum
int ia::min(int tab[][6], int size, int profondeur, int alpha, int beta) {

	if(profondeur == 0 || isWinner(tab, size) != 0) {

		return eval(tab, size);
	}

	int tmp = 0;
  int minTab;
  int resetProfondeur = profondeur;

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
      for(int k = 0; k < 8; k++) {

      if(tab[i][j] == 0) {

        tab[i][j] = 1;

        if(k == 0) {
          minTab = 1;
          rotateRight(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);
    
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }

          }
          else if(k == 1) {
            minTab = 1;
            rotateLeft(tab, size, minTab);
            tmp = max(tab, size, profondeur-1, alpha, beta);

          

        
          rotateRight(tab, size, minTab);
          tab[i][j] = 0;

          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }

          }
          else if(k == 2) {
            minTab = 2;
            rotateRight(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);    
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;


          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }

          }
          else if(k == 3) {
            minTab = 2;
            rotateLeft(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);
          
          rotateRight(tab, size, minTab);
          tab[i][j] = 0;

          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }

          }
          else if(k == 4) {
             minTab = 3;
            rotateRight(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);
        
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;


          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }

          }


          else if(k == 5) {
            minTab = 3;
            rotateLeft(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);

          rotateRight(tab, size, minTab);
          tab[i][j] = 0;

          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }
          
          }


          else if(k == 6) {
            minTab = 4;
            rotateRight(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);

    
         rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }


          }
          else if(k == 7) {
            minTab = 4;
            rotateLeft(tab, size, minTab);

            tmp = max(tab, size, profondeur-1, alpha, beta);
      
            rotateRight(tab, size, minTab);
            tab[i][j] = 0;


            if(beta > tmp) {
              beta = tmp;
            }
            if(beta <= alpha) {
              return beta;
            }
          }
        }
      }
      
		} 
	}
	return beta;

}



//Meilleur coup de l'ia calculé, doit avoir la plus grande valeur
int ia::max(int tab[][6], int size, int profondeur, int alpha, int beta) {

	 if(profondeur == 0 || isWinner(tab, size) != 0) {

    return eval(tab, size);
  }

  int tmp = 0;
  int minTab;
  int resetProfondeur = profondeur;

  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      for(int k = 0; k < 8; k++) {

      if(tab[i][j] == 0) {

        tab[i][j] = 2;

        if(k == 0) {                       //Indique dans quel sens tourne
            minTab = 1;                   //Indique quel plateau tourner
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          rotateLeft(tab, size, minTab);  //On annule le coup
          tab[i][j] = 0;

           if(alpha < tmp) {             //coupure alpha beta
            alpha = tmp;
          } 
          if(beta <= alpha) {
            return alpha;
          }


          }
          else if(k == 1) {
            minTab = 1;
            rotateLeft(tab, size, minTab);
            tmp = min(tab, size, profondeur-1, alpha, beta);

          rotateRight(tab, size, minTab);
          tab[i][j] = 0;

          if(alpha < tmp) {
             alpha = tmp;
            } 
            if(beta <= alpha) {
              return alpha;
            }


          }
          else if(k == 2) {
            minTab = 2;
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          if(alpha < tmp) {
            alpha = tmp;
          } 
          if(beta <= alpha) {
            return alpha;
          }
          

          }
          else if(k == 3) {
            minTab = 2;
            rotateLeft(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);
         
          rotateRight(tab, size, minTab);
           tab[i][j] = 0;

           if(alpha < tmp) {
            alpha = tmp;
          } 
          if(beta <= alpha) {
            return alpha;
          }
          

          }
          else if(k == 4) {
             minTab = 3;
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);

          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          if(alpha < tmp) {
            alpha = tmp;
          } 
          if(beta <= alpha) {
            return alpha;
          }

          }
          else if(k == 5) {
            minTab = 3;
            rotateLeft(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);
      
          rotateRight(tab, size, minTab);
          tab[i][j] = 0;


          if(alpha < tmp) {
            alpha = tmp;
          } 
          if(beta <= alpha) {
            return alpha;
          }
          
          }
          else if(k == 6) {
            minTab = 4;
            rotateRight(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);
          rotateLeft(tab, size, minTab);
          tab[i][j] = 0;

          if(alpha < tmp) {
            alpha = tmp;
          } 
          if(beta <= alpha) {
            return alpha;
          }


          }
          else if(k == 7) {
            minTab = 4;
            rotateLeft(tab, size, minTab);

            tmp = min(tab, size, profondeur-1, alpha, beta);
          
            rotateRight(tab, size, minTab);
            tab[i][j] = 0;

            if(alpha < tmp) {
              alpha = tmp;
            } 
            if(beta <= alpha) {
              return alpha;
            }
          }
        }
        
      }
      
    } 
  }
  return alpha;
}

////////////////////////////////////////////////////////////////////////////////


///////////////////////CALCUL VICTOIRE ///////////////////////////////////////



//p1rate et p2rate sont les alignements de pions respectifs des joueurs, cela permet de
//connaitre qui a gagné
void ia::nbRate(int tab[][6], int * p1Rate, int * p2Rate, int aligne, int size) {

  int cpt1, cpt2, i, j, x, y;
     
  *p2Rate = 0;
  *p1Rate = 0;

  cpt1 = 0;
  cpt2 = 0;

  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      if(tab[i][j] == 1 || tab[i][j] == 2) {
        cpt1++;

        x = i;
        y = j;

         //Verification ligne
        while(y < 5 && tab[x][y+1] == 1) {
          y++;
          cpt1++;
          if(cpt1 == aligne) {
            *p1Rate++;
          }    
        }

        x = i;
        y = j;

        while(y < 5 && tab[x][y+1] == 2) {
          y++;
          cpt2++;
          if(cpt2 == aligne) {
            *p2Rate++;
          }   
        }
        cpt1 = 0;
        cpt2 = 0;
        x = i;
        y = j;


        //Verification colonne
        while (x < 5 && tab[x+1][y] == 1) { 
        x++;
        cpt1++;
          if(cpt1 == aligne) {
          p1Rate++;
          }
        }

        x = i;
        y = j;

        while (x < 5 && tab[x+1][y] == 2) { 
          x++;
          cpt2++;
          if(cpt2 == aligne) {
            p2Rate++;
          }
        }

        cpt1 = 0;
        cpt2 = 0;
        x = i;
        y = j;


        //Verification diagonale bas droite 
        while(x < 5 && y < 5 && tab[x+1][y+1] == 1) { 
          x++;
          y++;
          cpt1++;
          if(cpt1 == aligne) {
            p1Rate++;
          }
        }

        x = i;
        y = j;

        while(x < 5 && y < 5 && tab[x+1][y+1] == 2) { 
          x++;
          y++;
          cpt2++;
          if(cpt2 == aligne) {
            p2Rate++;
          }
        }   

        cpt1 = 0;
        cpt2 = 0;
        x = i;
        y = j;



        //Verification diagonale haut droite
        while( x >= 1 && tab[x-1][y+1] == 1) {
          x--;
          y++;
          cpt1++;
          if(cpt1 == aligne) {
            p1Rate++;
          }
        }

        x = i;
        y = j;

        while( x >= 1 && tab[x-1][y+1] == 2) {
          x--;
          y++;
          cpt2++;
          if(cpt2 == aligne) {
            p2Rate++;
          }
        }      
      }
    }
  }    
}

int ia::isWinner(int tab[][6], int size) {

  int i, j;
  int p1 = 0;
  int p2 = 0;

  nbRate(tab, &p1, &p2, 5, size); //verifie si il y a une série de 5 pions alignés

  if(p1 == 1) {

    return 1;

  }else if(p2 == 1){

    return 2;

  }else {

    for(int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {

        if(tab[i][j] == 0) {

          return 0;   //Jeu pas fini et personne gagne
        }
      }
    } 
  }

  return 3;   //egalité
}


int ia::calcScore(int cpion, int cplay) {


  if(cpion == 1) {      //renvoie une valeur * le nombre de pions de l'ia sur la ligne concerée

    return 1*cplay;

  }else if(cpion == 2) {
    return 5*cplay;  

  }else if(cpion == 3) {
    return 10*cplay;  

  }else if(cpion == 4) {
    return 15*cplay;  

  }else {
    return 0;
  }
}

//Penser a verifier a chaque fois rotation gauche et droite

int ia::eval(int tab[][6], int size) {

	int winner, nbPion = 0;

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {

			if(tab[i][j] != 0) {
				nbPion++;
			}

		}
	}


	if((winner = isWinner(tab, size)) != 0) {

		//Si le joueur 1 gagne et non l'ia -> petit nombre
		if(winner == 1) {
			return -1000 + nbPion;
		}else if(winner == 2) {		//Si l'ia gagne -> grand nombre		
			return 1000 - nbPion;
		}else {
			return 0; //si egalité
		}
	}

  int score = 0;


  int cpion=0;
  int cplay=0;

//Diagonale 1//
  for(int i = 0; i < size; i++) {
    if(tab[i][i] != 0) {           //des qu'il y a un pion on le compte
      cpion++;

      if(tab[i][i] == 2)            //si pion ia, score augmente
        cplay++;
      else
        cplay--;                    //si pions joueur, score diminue
    }
  
  }
  score += calcScore(cpion,cplay);


//Diagonale 2//
  cpion = 0;
  cplay = 0;
  
  for(int i = 1; i < size; i++) {
    for(int j = 0; j < size-1; j++) {

      if(tab[i][j] !=  0) {
        cpion++;

        if(tab[i][j] == 2)
          cplay++;
        else
          cplay--;
      }
    }
  }
  score += calcScore(cpion,cplay);


//Diagonale 3//
  cpion = 0;
  cplay = 0;
  
  for(int i = 0; i < size-1; i++) {
    for(int j = 1; j < size; j++) {

      if(tab[i][j] !=  0) {
      cpion++;

      if(tab[i][j] == 2)
        cplay++;
      else
        cplay--;
      }
    }
  
  }
  score += calcScore(cpion,cplay);

  cpion = 0;
  cplay = 0;
  //Diagonale 4//
  for(int i = 0; i < size-1; i++) {
    for(int j = size-1; j > -1; j--) {
      if(tab[i][j] !=  0) {
        cpion++;

        if(tab[i][j] == 2)
          cplay++;
        else
          cplay--;
      }
    }
  
  }
  score += calcScore(cpion,cplay);


//Diagonale 5//
  cpion = 0;
  cplay = 0;
  
  for(int i = 1; i < size; i++) {
    for(int j = size; j > -1; j--) {

      if(tab[i][j] !=  0) {
        cpion++;

      if(tab[i][j] == 2)
        cplay++;
      else
        cplay--;
      } 
    }
  
  }
  score += calcScore(cpion,cplay);

//Diagonale 6//
  cpion = 0;
  cplay = 0;
  
  for(int i = 0; i < size-1; i++) {
    for(int j = size-2; j > -1 ; j--) {

      if(tab[i][j] !=  0) {
        cpion++;

        if(tab[i][j] == 2)
          cplay++;
        else
          cplay--;
      }
    }
  
  }
  score += calcScore(cpion,cplay);

  //Lignes
  for(int i = 0; i < size-1; i++) {
    cpion = 0;
    cplay = 0;
    for(int j = 0; j < size; j++) {
      if(tab[i][j] !=  0) {
        cpion++;

        if(tab[i][j] == 2)
          cplay++;
        else
          cplay--;
      }
    }
  score += calcScore(cpion,cplay); 
  }

  //Collonnes
  for(int i = 0; i < size-1; i++) {
    cpion = 0;
    cplay = 0;
    for(int j = 0; j < size; j++) {
      if(tab[j][i] !=  0) {
        cpion++;

        if(tab[j][i] == 2)
          cplay++;
        else
          cplay--;
      }
    }
   score += calcScore(cpion,cplay);
  }
  
  return score;
}
  
/////////////////////////////////////////////////////////////////////




/////////////////////////ROTATIONS////////////////////////////////////

int ia::rotateLeft(int tab[][6], int size, int minTab) {

  rotateRight(tab, size, minTab);
  rotateRight(tab, size, minTab);
  rotateRight(tab, size, minTab);
}


int ia::rotateRight(int tab[][6], int size, int minTab) {

  int n = size/2;     //indice pour les plateaux de la table              
  int i,j,temp;
  int ** copy;        //tableau de copie
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


  if(minTab == 1) {

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

  }else if(minTab == 2) {

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


  }else if(minTab == 3) {

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
    

  }else if(minTab == 4) {

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
}





















