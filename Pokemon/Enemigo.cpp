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

Enemigo::~Enemigo() {

}
