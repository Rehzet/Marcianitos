#pragma once
#include "Entidad.h"
#include <iostream>
#include "TextureManager.h"

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

