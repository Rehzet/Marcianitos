#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Nave.h"
#include "Constantes.h"
#include "TextureManager.h"

void inicializar();
void gameLoop();
void inputProcessor();

 sf::VideoMode resolucion = _1920x1080;
 sf::Uint32 modoVentana = sf::Style::Fullscreen;

 sf::RenderWindow GameWindow;

 sf::Clock Reloj;
 sf::Clock Reloj2;
 sf::Time deltaTime;

 sf::Sprite fondo;

 sf::Font fuenteKenVector_Future;
 sf::Text txtPuntos;

 sf::Texture tempTextur;

 Nave nave(resolucion);

 sf::Event Event;

int main() {
	inicializar();
	gameLoop();
}

void inicializar() {
	
	// https://www.youtube.com/watch?v=cGXlkOJ6SzQ Añadir o quitar la consola del proyecto. Debe añadirse el archivo sfml-main-d.lib a los Linkers

	/* ----- CONFIGS -----*/

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	/* ----- VENTANA ----- */
	GameWindow.create(resolucion, "Marcianitos", modoVentana, settings);
	GameWindow.setVerticalSyncEnabled(true);

	/* ----- FONDO ----- */
	TextureManager::loadTexture("fondo_azul", "res/Backgrounds/blue.png");
	tempTextur = *TextureManager::getTexture("fondo_azul");
	tempTextur.setRepeated(true);

	fondo.setTexture(tempTextur);
	fondo.setScale(0.5f, 0.5f);
	fondo.setTextureRect({ 0, 0, (int)GameWindow.getSize().x * 2, (int)GameWindow.getSize().y * 2 });

	/* ----- NAVE ----- */
	TextureManager::loadTexture("nave", "res/PNG/playerShip2_red.png");
	nave.setTexture(*TextureManager::getTexture("nave"));
	nave.setRightLimit(resolucion.width);

	/* ----- DISPARO-NAVE ----- */
	TextureManager::loadTexture("disparo", "res/PNG/Lasers/laserBlue01.png");
	
	/* ----- TIPO DE LETRA ----- */
	if (!fuenteKenVector_Future.loadFromFile("res/Bonus/kenvector_future.ttf"))
		std::cout << "No se ha podido cargar la fuente" << std::endl;

	txtPuntos.setFont(fuenteKenVector_Future);
	txtPuntos.setString("Puntuación: 0");
	txtPuntos.setCharacterSize(20);
	txtPuntos.setPosition(10, 10);


	
	GameWindow.pollEvent(Event);

	
}
bool a = true;

void gameLoop() {while (GameWindow.isOpen()){ // Bucle principal del juego
	deltaTime = Reloj.restart();

	inputProcessor();
	nave.processInput(deltaTime.asSeconds());
	

	if (nave.getPosition().x <= 10) {
		Reloj2.restart();
		a = true;
	}
	
	if (nave.getPosition().x + 112 >= (int)GameWindow.getSize().x-10 && a) {
		std::cout << Reloj2.getElapsedTime().asSeconds() << std::endl;
		a = false;
	}

	GameWindow.clear(sf::Color::Black);

	GameWindow.draw(fondo);
	GameWindow.draw(txtPuntos);

	nave.draw(GameWindow, deltaTime.asSeconds());

	for (int i = 0; i < (int)nave.vectorDisparos.size(); i++) 
		GameWindow.draw(nave.vectorDisparos[i].getSprite());
	
	for (int i = 0; i < (int)nave.vectorDisparos.size(); i++)
		nave.vectorDisparos[i].mover(deltaTime.asSeconds());
	
	
	GameWindow.display();

}}

void inputProcessor() {	static bool moverDcha = false;	static bool moverIzda = false; while (GameWindow.pollEvent(Event)) {

	switch (Event.type) {

	case sf::Event::Closed:
		GameWindow.close();
		break;
	case  sf::Event::KeyPressed:
		switch (Event.key.code) {
		case sf::Keyboard::Escape:
			GameWindow.close();
			break;
		}
		break;
	case sf::Event::Resized:
		GameWindow.create(sf::VideoMode(GameWindow.getSize().x, GameWindow.getSize().y, 32), "Marcianitos", modoVentana);
		nave.setPosition((float)GameWindow.getSize().x / 2 - 56, (float)GameWindow.getSize().y - 100);
		nave.setRightLimit(GameWindow.getSize().x);
		fondo.setTextureRect({ 0, 0, (int)GameWindow.getSize().x * 2, (int)GameWindow.getSize().y * 2 });
		break;
	}

	if (sf::Event::JoystickMoved) {
		if (Event.joystickMove.axis == DPAD_X) {
			if (Event.joystickMove.position == 100.0f) {
				moverDcha = true;
				moverIzda = false;
			}
			if (Event.joystickMove.position == -100.0f) {
				moverIzda = true;
				moverDcha = false;
			}
			if (Event.joystickMove.position != 100.0f && Event.joystickMove.position != -100.0f) {
				moverDcha = false;
				moverIzda = false;
			}
			std::cout << "Posicion X " << Event.joystickMove.position << std::endl;
		}
	}

	}

	if (moverDcha)
		nave.mover(1, 0, deltaTime.asSeconds());
	if (moverIzda)
		nave.mover(-1, 0, deltaTime.asSeconds());

	
	

}



