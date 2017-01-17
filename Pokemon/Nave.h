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

	void setTiempoDisparo(float tiempo);
	float getTiempoDisparo();

	float tiempo = 0.0f;

	bool isAlive();
	void setAlive(bool alive);

private:

	float _tiempoDisparo = 0.3f;

	bool _alive = true;

	int LIMITE_DERECHA;
	

	sf::Clock relojDisparo;
	sf::SoundBuffer soundBuffer;
	sf::Sound sonidoDisparo;
	
	
};


