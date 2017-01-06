#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "TextureManager.h"

class Disparo {
public:
	Disparo(float x, float y);
	~Disparo();

	void mover(float deltaTime);
	sf::Sprite getSprite();

private:
	sf::Sprite _sprite;

	float _x;
	float _y;
};

