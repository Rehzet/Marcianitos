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

Disparo::~Disparo() {

}
