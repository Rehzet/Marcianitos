#include "Disparo.h"

Disparo::Disparo(){
	_sprite.setTexture(*TextureManager::getTexture("disparo"));
}

void Disparo::mover(float deltaTime) {
	_sprite.move(0, -1200 * deltaTime);
}

void Disparo::draw(sf::RenderWindow &window) {
	window.draw(_sprite);
}

bool Disparo::isAlive() {
	return _alive;
}

void Disparo::setAlive(bool alive) {
	_alive = alive;
}

Disparo::~Disparo() {

}
