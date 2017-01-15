#include "Disparo.h"

Disparo::Disparo(float angle){
	if(!angle)
		_sprite.setTexture(*TextureManager::getTexture("disparoAzul"));
	else
		_sprite.setTexture(*TextureManager::getTexture("disparoRojo"));

	_sprite.setRotation(angle);
}

void Disparo::mover(float deltaTime) {
	float sentido;

	if (!this->getSprite().getRotation())
		sentido = -1;
	else
		sentido = 1;

	_sprite.move(0, 1200 * deltaTime * sentido);
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
