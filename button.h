#ifndef button_H
#define button_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//CETTE CLASSE LA CREATION DES BOUTONS DE MENUS

class button
{
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	string m_path;
	

	public :
	
	button();
	button(string name, sf::Vector2f position);

	bool isClicked(sf::RenderWindow &window);
	void drawButton(sf::RenderWindow &window);

};
#endif