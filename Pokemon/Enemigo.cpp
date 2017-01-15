#include "Enemigo.h"

Enemigo::Enemigo() {

}

void Enemigo::draw(sf::RenderWindow &window) {
	window.draw(this->getSprite());
}

bool Enemigo::isAlive() {
	return _alive;
}

void Enemigo::setAlive(bool alive) {
	_alive = alive;
}

int Enemigo::getID() {
	return _ID;
}

void Enemigo::setID(int ID) {
	this->_ID = ID;
}

void Enemigo::mover(int x, int y) {
	this->_sprite.move(x, y);
}

void Enemigo::setSound(sf::Sound &sonido) {
	_sonidoExplosion = sonido;
}

void Enemigo::explosion() {
	_sonidoExplosion.play();
}

void Enemigo::disparar() {
	Disparo *disp = new Disparo(180);
	disp->setPosition(this->_sprite.getPosition().x + 51, this->_sprite.getPosition().y + 84 + 20);
	vectorDisparos.push_back(*disp);
	//sonidoDisparo.play();
}

Enemigo::~Enemigo() {

}
