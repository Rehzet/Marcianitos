#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Nave.h"
#include "Constantes.h"
#include "TextureManager.h"
#include "Entidad.h"
#include "Enemigo.h"
#include <string>

void inicializar();
void gameLoop();
void inputProcessor();

 sf::VideoMode resolucion = _1600x900;
 sf::Uint32 modoVentana = sf::Style::Default;

 sf::RenderWindow GameWindow;
 sf::Clock Reloj;
 sf::Clock Reloj2;
 sf::Time deltaTime;

 sf::Sprite fondo;

 sf::Font fuenteKenVector_Future;
 sf::Text txtPuntos;
 int puntos = 0;

 sf::Texture tempTextur;

 sf::SoundBuffer buffer;

 typedef struct {
	 std::vector<Enemigo> enemigos[3];
	 int limDcha = 5;
	 int limIzda = 0;
	 float velocidad = 300;
	 int numNaves = 18;
	 sf::Sound sonidoExplosion;
 } Enemigos;

 Enemigos enemigos;

 Nave *nave = new Nave(resolucion);

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
	GameWindow.setPosition(sf::Vector2i(0, 0));

	/* ----- FONDO ----- */
	TextureManager::loadTexture("fondo_azul", "res/Backgrounds/blue.png");
	tempTextur = *TextureManager::getTexture("fondo_azul");
	tempTextur.setRepeated(true);

	fondo.setTexture(tempTextur);
	fondo.setScale(0.5f, 0.5f);
	fondo.setTextureRect({ 0, 0, (int)GameWindow.getSize().x * 2, (int)GameWindow.getSize().y * 2 });

	/* ----- NAVE ----- */
	TextureManager::loadTexture("nave", "res/PNG/playerShip2_red.png");
	nave->setTexture(*TextureManager::getTexture("nave"));
	nave->setRightLimit(resolucion.width);
	nave->setWidth(112);
	nave->setHeight(75);

	/* ----- DISPARO-NAVE ----- */
	TextureManager::loadTexture("disparo", "res/PNG/Lasers/laserBlue01.png");
	
	/* ----- FUEGOS-NAVE ----- */

	/* ----- ENEMIGOS ----- */
	float x, y = 60;
	int id = 0;	
	int num = 3;
	std::string color = "Red";
	TextureManager::loadTexture("enemigo", "res/PNG/Enemies/enemy" + color + std::to_string(num) + ".png");

	for (int j = 0; j < 3; j++) {
		x = 100;		
		for (int i = 0; i < 6; i++) {
			Enemigo *enemigo = new Enemigo();			
			enemigo->setTexture(*TextureManager::getTexture("enemigo"));
			enemigo->setPosition(x, y);
			enemigo->setID(id++);		
			enemigos.enemigos[j].push_back(*enemigo);
			std::cout << "ID: " << enemigo->getID() << std::endl;
			x += 150;
		}
		y += 110;
		num--;
	}
	buffer.loadFromFile("res/Bonus/DeathFlash.wav");
	enemigos.sonidoExplosion.setBuffer(buffer);
	enemigos.sonidoExplosion.setVolume(50);

	/* ----- TIPO DE LETRA ----- */
	if (!fuenteKenVector_Future.loadFromFile("res/Bonus/kenvector_future.ttf"))
		std::cout << "No se ha podido cargar la fuente" << std::endl;

	txtPuntos.setFont(fuenteKenVector_Future);
	txtPuntos.setString("Puntuación: " + std::to_string(puntos));
	txtPuntos.setCharacterSize(20);
	txtPuntos.setPosition(10, 10);

}

void gameLoop() {int sentido = 1;  while (GameWindow.isOpen()) { // Bucle principal del juego

	deltaTime = Reloj.restart();

	inputProcessor();
	nave->processInput(deltaTime.asSeconds());

	/* Se mueven todos los disparos generados por la nave del jugador. */
	for (int i = 0; i < (int)nave->vectorDisparos.size(); i++)
		nave->vectorDisparos[i].mover(deltaTime.asSeconds());

	/* Todo el código de movimiento y colisiones de los enemigos. Se ejecuta mientras quede al menos una nave sin destruir. */
	if (enemigos.numNaves > -1) {
		/* Comprobar el límite derecho del conjunto de naves enemigas. */
		if (!enemigos.enemigos[0][enemigos.limDcha].isAlive() && !enemigos.enemigos[1][enemigos.limDcha].isAlive()
			&& !enemigos.enemigos[2][enemigos.limDcha].isAlive())
			enemigos.limDcha--;

		/* Comprobar el límite izquierdo del conjunto de naves enemigas. */
		if (!enemigos.enemigos[0][enemigos.limIzda].isAlive() && !enemigos.enemigos[1][enemigos.limIzda].isAlive()
			&& !enemigos.enemigos[2][enemigos.limIzda].isAlive())
			enemigos.limIzda++;

		/* Se cambia el sentido de las naves enemigas dependiendo de la posición de las naves que están en los límites. */
		if ((enemigos.enemigos[0][enemigos.limDcha].isAlive() && enemigos.enemigos[0][enemigos.limDcha].getSprite().getPosition().x + 93 + 20 >= GameWindow.getSize().x)
			|| (enemigos.enemigos[1][enemigos.limDcha].isAlive() && enemigos.enemigos[1][enemigos.limDcha].getSprite().getPosition().x + 93 + 20 >= GameWindow.getSize().x)
			|| (enemigos.enemigos[2][enemigos.limDcha].isAlive() && enemigos.enemigos[2][enemigos.limDcha].getSprite().getPosition().x + 93 + 20 >= GameWindow.getSize().x))
		{
			sentido = -1;
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 6; i++) {
					enemigos.enemigos[j][i].mover(0, GameWindow.getSize().y / 30);
				}
			}
		}
		else if ((enemigos.enemigos[0][enemigos.limIzda].isAlive() && enemigos.enemigos[0][enemigos.limIzda].getSprite().getPosition().x <= 20)
			|| (enemigos.enemigos[1][enemigos.limIzda].isAlive() && enemigos.enemigos[1][enemigos.limIzda].getSprite().getPosition().x <= 20)
			|| (enemigos.enemigos[2][enemigos.limIzda].isAlive() && enemigos.enemigos[2][enemigos.limIzda].getSprite().getPosition().x <= 20))
		{
			sentido = 1;
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 6; i++) {
					enemigos.enemigos[j][i].mover(0, GameWindow.getSize().y / 30);
				}
			}
		}

		/* Se mueve todo el conjunto de naves enemigas. */
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				enemigos.enemigos[j][i].mover(sentido * enemigos.velocidad * deltaTime.asSeconds(), 0);
			}
		}

		/* Comprobación de colisiones de los disparos con todas las naves enemigas. */
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < (int)nave->vectorDisparos.size(); k++) {
					if (nave->vectorDisparos[k].getSprite().getGlobalBounds().intersects(enemigos.enemigos[j][i].getSprite().getGlobalBounds())) {
						enemigos.sonidoExplosion.play();
						enemigos.enemigos[j][i].setAlive(false);
						enemigos.enemigos[j][i].setPosition(-1000, -1000);
						nave->vectorDisparos[k].setAlive(false);
						nave->vectorDisparos[k].setPosition(-2000, -1000);
						enemigos.velocidad *= 1.077f;
						enemigos.numNaves--;
						txtPuntos.setString("Puntuación: " + std::to_string(puntos += 100));
						std::cout << "Colision" << std::endl;
					}
				}
			}
		}
	}

	GameWindow.clear(sf::Color::Black);

	GameWindow.draw(fondo);
	GameWindow.draw(txtPuntos);

	nave->draw(GameWindow);

	for (int i = 0; i < (int)nave->vectorDisparos.size(); i++)
		if(nave->vectorDisparos[i].isAlive())
			nave->vectorDisparos[i].draw(GameWindow);

	/* Se dibujan todas las naves enemigas mientras quede alguna sin destruir. */
	if (enemigos.numNaves > -1) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 6; i++) {
				if (enemigos.enemigos[j][i].isAlive()) {
					enemigos.enemigos[j][i].draw(GameWindow);
					//std::cout << "ID: " << enemigos.enemigos[j][i].getID() << std::endl;
				}
			}
		}
	}

	GameWindow.display();
}}

void inputProcessor() {	static bool moverDcha = false;	static bool moverIzda = false; while (GameWindow.pollEvent(Event)) {
   
	/* Controles teclado. */
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

		nave->setSize(GameWindow.getSize().x / 1920.0f, GameWindow.getSize().y / 1080.0f);
		nave->setPosition((float)GameWindow.getSize().x / 2 - 56, (float)GameWindow.getSize().y - 100);
		nave->setRightLimit(GameWindow.getSize().x);

		for (int j = 0; j < 3; j++) 
			for (int i = 0; i < 6; i++) 
				enemigos.enemigos[j][i].setSize(GameWindow.getSize().x / 1920.0f, GameWindow.getSize().y / 1080.0f);
			
		

		fondo.setTextureRect({ 0, 0, (int)GameWindow.getSize().x * 2, (int)GameWindow.getSize().y * 2 });

		std::cout << GameWindow.getSize().x << ", " << GameWindow.getSize().y << std::endl;


		

		GameWindow.create(sf::VideoMode(GameWindow.getSize().x, GameWindow.getSize().y, 32), "Marcianitos", modoVentana);
		break;
	}

	/* Controles del mando XBOX 360. */
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
		nave->mover(1, 0, deltaTime.asSeconds());
	if (moverIzda)
		nave->mover(-1, 0, deltaTime.asSeconds());

	
	

}



