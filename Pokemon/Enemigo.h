#pragma once
#include "Entidad.h"
#include "Disparo.h"
#include <SFML/Audio.hpp>

class Enemigo : public Entidad{
public:
	Enemigo();
	~Enemigo();

	void draw(sf::RenderWindow &window);

	bool isAlive();
	void setAlive(bool alive);

	int getID();
	void setID(int ID);

	void mover(float x, float y);

	void setSound(sf::Sound &sonido);

	void explosion();

	bool disparar();

	std::vector<Disparo> vectorDisparos;

private:
	bool _alive = true;
	int _ID;
	sf::Sound _sonidoExplosion;
	sf::Clock ckDisp;
};

