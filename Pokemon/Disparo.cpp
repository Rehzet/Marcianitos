#include "Disparo.h"

Disparo::Disparo(float x, float y){
	_sprite.setTexture(*TextureManager::getTexture("disparo"));
	this->_sprite.setPosition(x, y);
}

void Disparo::mover(float deltaTime) {
	_sprite.move(0, -1200 * deltaTime);
}

sf::Sprite Disparo::getSprite() {
	return _sprite;
}

Disparo::~Disparo() {

}
