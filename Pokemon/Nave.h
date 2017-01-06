#pragma once
#include "Disparo.h"


class Nave {
public:
	Nave(sf::VideoMode resolucion);
	~Nave();

	void processInput(float deltaTime);
	void setTexture(sf::Texture &textura);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void draw(sf::RenderWindow &Window, float deltaTime);
	void setRightLimit(int width);
	void mover(float x, float y, float deltaTime);
	void disparar();

	sf::Sprite getSprite();

	std::vector<Disparo> vectorDisparos;

private:
	const float TIEMPO_DISPARO = 0.3f;

	
	

	sf::Sprite _sprite;
	sf::Texture texturaDisparo;
	sf::Clock relojDisparo;
	sf::SoundBuffer soundBuffer;
	sf::Sound sonidoDisparo;

	int LIMITE_DERECHA;
	float tiempo;
	
	
};


