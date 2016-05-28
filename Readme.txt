/////////PENTAGO////////////
///////Version 1.80/////////
//////Julien Delvaux////////
////////////////////////////

Entrez dans la dossier avec la console :

make -> compile
make clean -> nettoie les fichiers .o
make mrproper -> nettoie tout

/!\ export LD_LIBRARY_PATH=SFML/lib -> Indique ou se trouve la bibliotheque : OBLIGATOIRE /!\

./game -> lance le jeu


Si le programme ne compile pas :

Essayer avec la version 4.9 de g++ et gcc : sudo apt-get install g++-4.9 gcc-4.9
											sudo apt-get update
Essayer d'installer la sfml sur le pc	: sudo apt-get install libsfml-dev


--->>> Pour changer la profondeur de l'ia, changez la valeur a la ligne 309 du fichier jeu.cpp


Le projet est entierement accessible sur github a l'adresse :
https://github.com/fLaVz/schoolGame.git