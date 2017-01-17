#include "Disparo.h"

Disparo::Disparo(float angle){
	if(!angle)
		_sprite.setTexture(*TextureManager::getTexture("disparoAzul"));
	else
		_sprite.setTexture(*TextureManager::getTexture("disparoRojo"));

	_sprite.setRotation(angle);

	_width = 9.0f;
	_height = 37.0f;
}

void Disparo::mover(float deltaTime) {
	float sentido;

	if (!this->getSprite().getRotation())
		sentido = -1.0f;
	else
		sentido = 1.0f;

	_sprite.move(0.0f, VELOCIDAD * deltaTime * sentido);
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
