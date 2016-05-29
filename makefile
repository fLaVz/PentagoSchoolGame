game:		main.o plat.o jeu.o player.o button.o ia.o
			g++ *.o -o game -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

main.o:		main.cpp plat.h jeu.h player.h
			g++ -c main.cpp -I SFML/include

plat.o:		plat.cpp plat.h
			g++ -c plat.cpp -I SFML/include

jeu.o:		jeu.cpp jeu.h plat.h
			g++ -c jeu.cpp -I SFML/include

player.o:	player.cpp player.h
			g++ -c player.cpp -I SFML/include

button.o:	button.cpp button.h
			g++ -c button.cpp -I SFML/include

ia.o:		ia.cpp ia.h
			g++ -c ia.cpp -I SFML/include

clean:	
			rm -f *.o

mrproper: 	clean
			rm -f game
