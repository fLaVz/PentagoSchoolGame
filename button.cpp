#include <iostream>
#include "button.h"

using namespace std;
using namespace sf;

button::button() {
	
}


button::button(string name, sf::Vector2f position) {

	m_path = "images/.png";
	m_path.insert(7, name);

	m_sprite.setPosition(position);


	if(!m_texture.loadFromFile(m_path))
		cout << "ERROR, Can't load texture located in " << m_path << endl;
	else
		m_sprite.setTexture(m_texture);

    if(name != "background")
		m_sprite.setScale(0.6, 0.6);

}


bool button::isClicked(RenderWindow &av_Window) {

    int mouseX = Mouse::getPosition(av_Window).x;
    int mouseY = Mouse::getPosition(av_Window).y;

    if(mouseX > m_sprite.getPosition().x
    && mouseX < (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width)
    && mouseY < (m_sprite.getPosition().y + m_sprite.getGlobalBounds().height)
    && mouseY > m_sprite.getPosition().y) {

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        }
        return false;
    }
    return false;
}


void button::drawButton(RenderWindow &window) {
	
	window.draw(m_sprite);
}