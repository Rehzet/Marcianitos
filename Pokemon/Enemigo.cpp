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

Enemigo::~Enemigo() {

}
