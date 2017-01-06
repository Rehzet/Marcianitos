#pragma once
#include <SFML/Graphics.hpp>

class Entidad {
public:
	Entidad();
	~Entidad();


	/// <summary>
	/// Devuelve el ancho del sprite
	/// </summary>
	int getWidth();

	/// <summary>
	/// Devuelve el alto del sprite
	/// </summary>
	int getHeight();

	sf::Vector2f getPosition();
	sf::Texture getTexture();
	sf::Sprite getSprite();

	// Setter
	void setWidth(int width);
	void setHeight(int height);

	void setPosition(sf::Vector2f);
	void setPosition(float x, float y);

	void setTexture(sf::Texture texture);
	void setSprite(sf::Sprite sprite);

	void act(float deltaTime);
	void draw(sf::RenderWindow window);


private:

	int width = NULL;
	int height = NULL;

	sf::Vector2f position;
	sf::Texture _texture;
	sf::Sprite _sprite;

};

