#pragma once
#include "Disparo.h"
#include "Entidad.h"

class Nave : public Entidad{
public:
	Nave(sf::VideoMode resolucion);
	~Nave();

	void processInput(float deltaTime);
	void draw(sf::RenderWindow &Window);
	void act(float deltaTime);

	void setRightLimit(int width);
	void mover(float x, float y, float deltaTime);
	void disparar();

	std::vector<Disparo> vectorDisparos;

private:

	const float TIEMPO_DISPARO = 0.5f;

	bool alive = true;

	int LIMITE_DERECHA;
	float tiempo;

	sf::Clock relojDisparo;
	sf::SoundBuffer soundBuffer;
	sf::Sound sonidoDisparo;
	
	
};


