#ifndef ia_H
#define ia_H

#include <iostream>
#include <vector>


class ia {

	int currentPlayer;
	//int profondeur;				//regel la difficulté, parametrable plus tard

	public :

	ia();
	std::vector<int> think(int ** tab, int size, int profondeur);

	int min(int tab[][6], int size, int profondeur, int alpha, int beta);
	int max(int tab[][6], int size, int profondeur, int alpha, int beta);

	void nbRate(int tab[][6], int * p1Rate, int * p2Rate, int profondeur, int size);

	int eval(int tab[][6], int size);
	int isWinner(int tab[][6], int size);
	int calcScore(int cntpion, int cntjoueur);

	int rotateRight(int tab[][6], int size, int minTab);
	int rotateLeft(int tab[][6], int size, int minTab);

};
#endif