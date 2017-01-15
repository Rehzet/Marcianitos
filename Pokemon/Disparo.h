#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "TextureManager.h"
#include "Entidad.h"

class Disparo : public Entidad{
public:

	/* Se crea un disparo con el par�metro opcional del �ngulo. Si no se pone, ser� 0 por defecto. */
	Disparo(float angle = 0);
	~Disparo();

	void draw(sf::RenderWindow &Window);
	void mover(float deltaTime);

	bool isAlive();
	void setAlive(bool alive);

private:
	bool _alive = true;
};

