#include "Nave.h"

Nave::Nave(sf::VideoMode resolucion) {

	figura.setPointCount(8);

	figura.setPoint(0, sf::Vector2f(52, 0));
	figura.setPoint(1, sf::Vector2f(60, 0));
	figura.setPoint(2, sf::Vector2f(67, 19));
	figura.setPoint(3, sf::Vector2f(112, 43));
	figura.setPoint(4, sf::Vector2f(112, 75));
	figura.setPoint(5, sf::Vector2f(0, 75));
	figura.setPoint(6, sf::Vector2f(0, 43));
	figura.setPoint(7, sf::Vector2f(46, 19));
	
	figura.setPosition((float)resolucion.width / 2 - 56, (float)resolucion.height - 100);

	if (!soundBuffer.loadFromFile("res/Bonus/sfx_laser2.ogg"))
		std::cout << "No se ha podido cargar el sonido del disparo 1" << std::endl;
	sonidoDisparo.setBuffer(soundBuffer);

	setRightLimit(resolucion.width);

}

void Nave::draw(sf::RenderWindow &Window) {
	//Window.draw(_sprite);
	Window.draw(figura);
}

void Nave::act(float deltaTime) {

}

void Nave::processInput(float deltaTime) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->mover(-1, 0, deltaTime);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->mover(1, 0, deltaTime);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(0, sf::Joystick::X)) {
		if (relojDisparo.getElapsedTime().asSeconds() - tiempo > _tiempoDisparo) {
			disparar();
			tiempo = relojDisparo.getElapsedTime().asSeconds();
		}
	}

}

void Nave::mover(float x, float y, float deltaTime) {

	if (figura.getPosition().x > 10 && x == -1)
		this->figura.move(x * deltaTime * (LIMITE_DERECHA) * 0.3f, 0);

	if (figura.getPosition().x < LIMITE_DERECHA - 112 - 10 && x == 1)
		this->figura.move(x * deltaTime * (LIMITE_DERECHA) * 0.3f, 0);
}


void Nave::disparar() {
	Disparo *disp = new Disparo();
	disp->setPosition(this->figura.getPosition().x + (_width*this->figura.getScale().x)/2.0f - disp->getWidth() / 2, this->figura.getPosition().y - disp->getHeight() + disp->getHeight()/2);
	vectorDisparos.push_back(*disp);
	sonidoDisparo.play();
}

void Nave::setRightLimit(int width) {
	LIMITE_DERECHA = width;
}

void Nave::setTiempoDisparo(float tiempoDisparo) {
	_tiempoDisparo = tiempoDisparo;
}

float Nave::getTiempoDisparo() {
	return _tiempoDisparo;
}

bool Nave::isAlive(){
	return this->_alive;
}

void Nave::setAlive(bool alive) {
	this->_alive = alive;
}

void Nave::setVidas(int vidas) {
	_vidas = vidas;
}

int Nave::getVidas() {
	return _vidas;
}

Nave::~Nave(){

}

