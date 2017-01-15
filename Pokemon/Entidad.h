#pragma once
#include <SFML/Graphics.hpp>

class Entidad {
public:
	/* Constructor */
	Entidad();

	/* Destructor */
	~Entidad();

	/*
	Devuelve el ancho de la entidad, o NULL si no
	se ha modificado o es un valor incorrecto.*/
	int getWidth();

	/*
	Devuelve el alto de la entidad, o NULL si no
	se ha modificado o es un valor incorrecto.*/
	int getHeight();

	/*
	Devuelve la posici�n de la entidad como vector de dos componentes flotantes.*/
	sf::Vector2f getPosition();

	/*
	Devuelve la textura de la entidad.*/
	sf::Texture getTexture();

	/*
	Devuelve el Sprite de la entidad.*/
	sf::Sprite getSprite();

	// Setter

	/*
	Se establece el ancho de la entidad con el par�metro width pasado.*/
	void setWidth(int width);

	/*
	Se establece el alto de la entidad con el par�metro height pasado.*/
	void setHeight(int height);

	/*
	Se cambia la posici�n de la entidad utilizando un vector de dos componentes flotantes.*/
	void setPosition(sf::Vector2f posicion);

	/*
	Se cambia la posici�n de la entidad utilizando las dos coordenadas pasadas por par�metros.*/
	void setPosition(float x, float y);

	/*
	Se cambia la textura de la entidad por una nueva.*/
	void setTexture(sf::Texture &texture);

	/*
	Se cambia el Sprite de la entidad por uno nuevo.*/
	void setSprite(sf::Sprite sprite);

	/*
	Se cambia el tama�o del sprite utilizando la funci�n setScale(float x, float y) de sf::Sprite. */
	void setSize(float width, float height);

	/*
	M�todo que se utiliza para escribir toda la l�gica de la entidad.
	- deltaTime: tiempo que transcurre entre cada iteraci�n del bucle principal del juego*/
	virtual void act(float deltaTime);

	/*
	M�todo que se encarga de dibujar los cambios en la pantalla.
	- window: Ventana en la que se van a aplicar los cambios.*/
	virtual void draw(sf::RenderWindow window);


protected:

	/* Ancho de la entidad. Tiene valor NULL por defecto.*/
	int _width = NULL;

	/* Alto de la entidad. Tiene valor NULL por defecto.*/
	int _height = NULL;

	/* Textura de la entidad*/
	sf::Texture _texture;

	/* Sprite de la entidad. Es la parte visible que se va a mostrar por pantalla.*/
	sf::Sprite _sprite;

	/* Guarda el tama�o del sprite. */
	sf::Vector2f _size;

};

