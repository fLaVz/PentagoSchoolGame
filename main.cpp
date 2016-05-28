#include <iostream>
#include "jeu.h"
#include "plat.h"
#include "button.h"
#include "ia.h"

using namespace std;
using namespace sf;


int main()
{

    //Initialisation du jeu
    //input mouseIn;
    jeu game;
    ia bot;
    int cpt = 1; //Gere l'alternance des joueurs
    
    //Initialisation de la fenetre de rendu
    RenderWindow window(VideoMode(800, 600), "PENTAGO v1.0");
   // window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);


    //Initialisation des boutons
    button backGround("background", Vector2f(0, 0));
    button newgame("newgame", Vector2f(50, 150));
    button loadGame("load", Vector2f(50, 250));
    button leave("leave", Vector2f(50, 350));
    button classic("classic", Vector2f(300, 150));
    button perso("perso", Vector2f(300, 250));
    button pvp("pvp", Vector2f(150, 250));
    button pvia("pvia", Vector2f(450, 250));
    button save("save", Vector2f(100, 350));
    button load("load", Vector2f(450, 450));
    button cont("cont", Vector2f(450, 350));
    button newgamepause("newgame", Vector2f(250, 450));
    
    ///////////PARTIE INTERFACE GRAPHIQUE/////////////////////

    //Boucle de jeu avec un gamestate pour gerer ou non l'interface graphique
    while(window.isOpen())
    {
    
        Event event;                    //traite les évènements
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed)     //si on clic sur la croix rouge
                window.close(); 
            if(event.type == Event::KeyPressed) {
                //Si la touche echap est préssée et qu'on est dans une partie
                if(event.key.code == Keyboard::Escape && game.getGameState() == "RUN")
                    game.setGameState("PAUSE");

            }
        }
        /*if(game.getGameState() == "RUN")
            mouseIn.setInput(window);*/

        window.clear();
        backGround.drawButton(window);


        //////////////NEWGAME / LEAVE ////////////////////////
        if(game.getGameState() == "MENU1") {
            
            newgame.drawButton(window);
            loadGame.drawButton(window);
            leave.drawButton(window);

            if(newgame.isClicked(window)) {
                game.setGameState("MENU2");
            }
            if(loadGame.isClicked(window)) {
                game.setGameState("LOAD");
            }
                
            if(leave.isClicked(window))
                window.close();


        ////////////// CLASSIC / CUSTOM ////////////////////////
        }else if(game.getGameState() == "MENU2") {

            classic.drawButton(window);
            perso.drawButton(window);

            if(classic.isClicked(window)) {
            	game.setMode("standard");
                game.setGameState("MENU3");
            }else if(perso.isClicked(window)) {
                game.setGameState("CUSTOM");
                window.close();
            }

               
        ////////////// PVP / PVIA ////////////////////////
        }else if(game.getGameState() == "MENU3") {

            pvp.drawButton(window);
            pvia.drawButton(window);

            if(pvp.isClicked(window)) {
            	game.setType("PvP");
                game.setGameState("RUN");
            }else if(pvia.isClicked(window)) {
                game.setType("PvIA");
                game.setGameState("RUN");
            }

        //////////// GAME LOADING ///////////////////
        }else if(game.getGameState() == "LOAD") {
            game.load();

            game.setGameState("RUN");

        ////////////////// MODE PVP /////////////////////

        }else if(game.getGameState() == "RUN" && game.getType() == "PvP") {

            game.draw(window);
                if(game.placeButton(window, cpt) == 1) {
                    game.setGameState("ROTATE");
                }

        ///////////////// MODE PVIA /////////////////////////////

        }else if(game.getGameState() == "RUN" && game.getType() == "PvIA") {

            game.draw(window);

            if(game.getPlayerName(1) != "BOT")
                game.renameToBot();

            if(game.playerPlay(window, 1) == 1)
                game.setGameState("ROTATE");
            

        }else if(game.getGameState() == "RUN" && game.getType() == "PvIA1") {
            game.draw(window);

            if(game.botPlay(bot, 2) == 1) {
                game.setType("PvIA"); //On redemande au joueur de jouer
            }
                
            else if(game.botPlay(bot, 2) == 3) {
                window.close();
            }

        ///////////////////// ROTATION ////////////////////////:

        }else if(game.getGameState() == "ROTATE") {

            game.draw(window);

            if(game.getType() == "PvIA")            //Si joueur vs IA
                game.setType("PvIA1");
            if(game.rotate(window, cpt) == 1)       //Si la rotation a eu lieu
                game.setGameState("RUN");
            window.clear();                         //réaffiche le jeu 
            backGround.drawButton(window);          //et empeche la latence entre la
            game.draw(window);                      //rotation et la reflexion du bot
            

        ///////////////// PAUSE ////////////////////////////////

        }else if(game.getGameState() == "PAUSE") {  //Si escape menu pause
            game.draw(window);
            game.setPauseGame(window);
            cont.drawButton(window);
            save.drawButton(window);
            newgamepause.drawButton(window);

            if(cont.isClicked(window))          //si le bouton continuer est cliqué, on revient a la partie
                game.setGameState("RUN");
            if(save.isClicked(window))          //si le bouton sauvegardé est cliqué, on suavegarde
                game.save();
            if(newgamepause.isClicked(window)) {
                game.reset(cpt);
                game.setGameState("MENU2");
            }
                
        }
        
        window.display();
    }
    ////////////////FIN INTERFACE GRAPHIQUE///////////////////



    //////////////////////PARTIE CONSOLE//////////////////////
    if(game.getGameState() == "CUSTOM") {

        cout << "CUSTOM" << endl;
        game.run();
    }
    
	return 0;
}

