#include "Entidad.h"

Entidad::Entidad() {

}


Entidad::~Entidad() {

}

void Entidad::act(float deltaTime) {

}

void Entidad::draw(sf::RenderWindow window) {

}

int Entidad::getWidth() {
	return _width;
}

int Entidad::getHeight() {
	return _height;
}

sf::Vector2f Entidad::getPosition() {
	return _position;
}

sf::Texture Entidad::getTexture() {
	return _texture;
}

sf::Sprite Entidad::getSprite() {
	return _sprite;
}

void Entidad::setWidth(int width) {
	if (width > 0)
		_width = width;
	else
		_width = NULL;
}

void Entidad::setHeight(int height) {
	if (height > 0)
		_height = height;
	else
		_height = NULL;
}

void Entidad::setPosition(sf::Vector2f posicion) {
	_sprite.setPosition(posicion);
}

void Entidad::setPosition(float x, float y) {
	_sprite.setPosition(x, y);
}

void Entidad::setTexture(sf::Texture &texture){
	_texture = texture;
	_sprite.setTexture(_texture);
}

void Entidad::setSprite(sf::Sprite sprite) {
	_sprite = sprite;
}

