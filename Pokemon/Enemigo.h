#pragma once
#include "Entidad.h"

class Enemigo : public Entidad{
public:
	Enemigo();
	~Enemigo();

	void draw(sf::RenderWindow &window);

	bool isAlive();
	void setAlive(bool alive);

private:
	bool _alive = true;
};

