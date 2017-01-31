#pragma once
#include "Entidad.h"
#include <iostream>

class Ovni : public Entidad{

public:
	Ovni();

	void draw(sf::RenderWindow &Window);

	void mover();

	void soltarPowerUp();

	void generarPowerUp();

	void aparecer(float width);

	~Ovni();

private:
	int powerUp;
};

