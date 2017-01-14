#pragma once
#include "Entidad.h"

class Enemigo : public Entidad{
public:
	Enemigo();
	~Enemigo();

	void draw(sf::RenderWindow &window);

	bool isAlive();
	void setAlive(bool alive);

	int getID();
	void setID(int ID);

	void mover(int x, int y);

private:
	bool _alive = true;
	int _ID;
};

