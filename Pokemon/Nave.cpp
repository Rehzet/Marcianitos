#include "Nave.h"

Nave::Nave(sf::VideoMode resolucion) {

	this->setPosition((float)resolucion.width / 2 - 56, (float)resolucion.height - 100);

	if (!soundBuffer.loadFromFile("res/Bonus/sfx_laser2.ogg"))
		std::cout << "No se ha podido cargar el sonido del disparo 1" << std::endl;
	sonidoDisparo.setBuffer(soundBuffer);

	setRightLimit(resolucion.width);

}

void Nave::draw(sf::RenderWindow &Window) {
	Window.draw(_sprite);
}

void Nave::act(float deltaTime) {

}

void Nave::processInput(float deltaTime) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->mover(-1, 0, deltaTime);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->mover(1, 0, deltaTime);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
		if (relojDisparo.getElapsedTime().asSeconds() - tiempo > _tiempoDisparo) {
			disparar();
			tiempo = relojDisparo.getElapsedTime().asSeconds();
		}
	}

}

void Nave::mover(float x, float y, float deltaTime) {

	if (_sprite.getPosition().x > 10 && x == -1)
		this->_sprite.move(x * deltaTime * (LIMITE_DERECHA) * 0.3f, 0);

	if (_sprite.getPosition().x < LIMITE_DERECHA - 112 - 10 && x == 1)
		this->_sprite.move(x * deltaTime * (LIMITE_DERECHA) * 0.3f, 0);
}


void Nave::disparar() {
	Disparo *disp = new Disparo();
	disp->setPosition(this->_sprite.getPosition().x + (_width*this->_sprite.getScale().x)/2.0f - disp->getWidth() / 2, this->_sprite.getPosition().y - disp->getHeight() + disp->getHeight()/2);
	vectorDisparos.push_back(*disp);
	sonidoDisparo.play();
}

void Nave::setRightLimit(int width) {
	LIMITE_DERECHA = width;
}

void Nave::setTiempoDisparo(float tiempoDisparo) {
	_tiempoDisparo = tiempoDisparo;
}

float Nave::getTiempoDisparo() {
	return _tiempoDisparo;
}

bool Nave::isAlive(){
	return this->_alive;
}

void Nave::setAlive(bool alive) {
	this->_alive = alive;
}

Nave::~Nave(){

}

