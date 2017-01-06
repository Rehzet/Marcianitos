#include "Nave.h"

Nave::Nave(sf::VideoMode resolucion) {

	this->setPosition((float)resolucion.width / 2 - 56, (float)resolucion.height - 100);

	if (!soundBuffer.loadFromFile("res/Bonus/sfx_laser2.ogg"))
		std::cout << "No se ha podido cargar el sonido del disparo 1" << std::endl;
	sonidoDisparo.setBuffer(soundBuffer);
}

Nave::~Nave(){
}

void Nave::processInput(float deltaTime) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {		
		Nave::mover(-1, 0, deltaTime);
	}
		
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {		
		Nave::mover(1, 0, deltaTime);
	}	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
		if (relojDisparo.getElapsedTime().asSeconds() - tiempo > TIEMPO_DISPARO) {
			disparar();
			tiempo = relojDisparo.getElapsedTime().asSeconds();
		}
	}

}

void Nave::setTexture(sf::Texture &textura) {
	_sprite.setTexture(textura);
}

sf::Vector2f Nave::getPosition() {
	return _sprite.getPosition();
}

void Nave::setPosition(float x, float y) {
	_sprite.setPosition(x, y);
}


sf::Sprite Nave::getSprite() {
	return _sprite;
}

void Nave::mover(float x, float y, float deltaTime) {

	if (_sprite.getPosition().x > 10 && x==-1)		
		this->_sprite.move(x * deltaTime * (LIMITE_DERECHA)/1.8 , 0);

	if (_sprite.getPosition().x < LIMITE_DERECHA - 112 - 10 && x == 1)
		this->_sprite.move(x * deltaTime * (LIMITE_DERECHA) / 1.8, 0);
}


void Nave::disparar() {
	Disparo disp(this->_sprite.getPosition().x + 51, this->_sprite.getPosition().y - 55);
	vectorDisparos.push_back(disp);
	sonidoDisparo.play();
}


void Nave::draw(sf::RenderWindow &Window, float deltaTime) {
	Window.draw(_sprite);	
}

void Nave::setRightLimit(int width) {
	LIMITE_DERECHA = width;
}