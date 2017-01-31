#include "Ovni.h"


Ovni::Ovni(){	
}

void Ovni::draw(sf::RenderWindow &window) {
	window.draw(_sprite);
}

void Ovni::mover() {

}

void Ovni::soltarPowerUp() {

}

void Ovni::generarPowerUp() {
	powerUp = rand() % 5 + 1;

	switch (powerUp) {

	}
}

void Ovni::aparecer(float width) {
	_sprite.setPosition(width + 300.0f, 50.0f);
}


Ovni::~Ovni(){

}
