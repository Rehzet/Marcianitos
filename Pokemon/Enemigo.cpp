#include "Enemigo.h"

Enemigo::Enemigo() {
	srand(time(NULL));
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

void Enemigo::mover(float x, float y) {
	this->_sprite.move(x, y);
}

void Enemigo::setSound(sf::Sound &sonido) {
	_sonidoExplosion = sonido;
}

void Enemigo::explosion() {
	_sonidoExplosion.play();
}

bool Enemigo::disparar() {
	bool disparado = false;
	if (ckDisp.getElapsedTime().asSeconds() >= rand() % 6 + 3) { // Cada 3-6 segundos hay una probabilidad de disparar del 25%.
		if (int num = rand() % 100 + 1 >= 75) { // Probabilidad de disparo del 25%.
			std::cout << num << std::endl;
			Disparo *disp = new Disparo(180);
			disp->setPosition(this->_sprite.getPosition().x + (_width*this->_sprite.getScale().x) / 2.0f - disp->getWidth() / 2, this->_sprite.getPosition().y + this->_height);
			vectorDisparos.push_back(*disp);
			disparado = true;
		}
		ckDisp.restart();
	}

	return disparado;
}

Enemigo::~Enemigo() {

}
