#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Nave.h"
#include "Constantes.h"
#include "TextureManager.h"
#include "Entidad.h"
#include "Enemigo.h"
#include <string>
#include <stdlib.h>
#include <time.h>

void inicializar();
void gameLoop();
void inputProcessor();

void generarMarcianos(float nivel);

 sf::VideoMode resolucion = _1600x900;
 sf::Uint32 modoVentana = sf::Style::Default;

 sf::RenderWindow GameWindow;
 sf::Clock Reloj;
 sf::Time deltaTime;

 sf::Sprite fondo;

 sf::Font fuenteKenVector_Future;
 sf::Text txtPuntos;
 sf::Text txtPausa;

 int puntos = 0;
 int nivel = 1;
 bool cambiarNivel = false;

 sf::Texture tempTextur;

 sf::SoundBuffer buffer1;
 sf::SoundBuffer buffer2;


 typedef struct {	
	 static const int FILAS = 5;
	 static const int COLUMNAS = 6;
	 static const int MAX_NAVES = FILAS * COLUMNAS;
	 std::vector<Enemigo> enemigos[FILAS];	 
	 int limDcha;
	 int limIzda = 0;
	 float velocidad;
	 int numNaves;
	 sf::Sound sonidoExplosion;
	 sf::Sound sonidoDisparo;
 } Enemigos;

 Enemigos enemigos;

 Nave *nave = new Nave(resolucion);

 sf::Event Event;

 bool pausa = false;

int main() {
	inicializar();
	gameLoop();
}

void inicializar() {
	std::srand(time(NULL));

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
	nave->setWidth(112.0f);
	nave->setHeight(75.0f);
	nave->setSize(GameWindow.getSize().x / 1920.0f, GameWindow.getSize().y / 1080.0f);

	/* ----- DISPAROS ----- */
	TextureManager::loadTexture("disparoAzul", "res/PNG/Lasers/laserBlue07.png");
	TextureManager::loadTexture("disparoRojo", "res/PNG/Lasers/laserRed07.png");
	
	/* ----- FUEGOS-NAVE ----- */

	/* ----- ENEMIGOS -----	*/

	for (int i = 1; i <= 5; i++) {
		TextureManager::loadTexture("enemigoRojo" + std::to_string(i), "res/PNG/Enemies/enemyRed" + std::to_string(i) + ".png");
	}

	buffer1.loadFromFile("res/Bonus/DeathFlash.wav");
	enemigos.sonidoExplosion.setBuffer(buffer1);
	enemigos.sonidoExplosion.setVolume(10.0f);

	buffer2.loadFromFile("res/Bonus/sfx_laser1.ogg");
	enemigos.sonidoDisparo.setBuffer(buffer2);
	enemigos.sonidoDisparo.setVolume(22.0f);

	generarMarcianos((float)nivel);

	/* ----- TEXTOS ----- */
	if (!fuenteKenVector_Future.loadFromFile("res/Bonus/kenvector_future.ttf"))
		std::cout << "No se ha podido cargar la fuente" << std::endl;

	txtPuntos.setFont(fuenteKenVector_Future);
	txtPuntos.setString("Puntuación: " + std::to_string(puntos));
	txtPuntos.setCharacterSize(20);
	txtPuntos.setPosition(10, 10);

	txtPausa.setFont(fuenteKenVector_Future);
	txtPausa.setString("PAUSA");
	txtPausa.setCharacterSize(60);
	txtPausa.setPosition((float)GameWindow.getSize().x / 2.0f - 121.0f, (float)GameWindow.getSize().y / 2.0f - 20.0f);

}



bool flag = true;
float tiempoX;

void gameLoop() {int sentido = 1;  while (GameWindow.isOpen()) { // Bucle principal del juego

	deltaTime = Reloj.restart();
	inputProcessor();

	if (cambiarNivel) {
		if (tiempoX < 2.0f) {
			tiempoX += deltaTime.asSeconds();
			std::cout << tiempoX << std::endl;
		}
		else {
			nivel++;
			generarMarcianos(nivel);
			cambiarNivel = false;
		}

	}

	if (!pausa && !cambiarNivel) {

		nave->processInput(deltaTime.asSeconds());

		/* Se mueven todos los disparos generados por la nave del jugador. */
		for (int i = 0; i < (int)nave->vectorDisparos.size(); i++)
			nave->vectorDisparos[i].mover(deltaTime.asSeconds());


		/* Todo el código de movimiento y colisiones de los enemigos. Se ejecuta mientras quede al menos una nave sin destruir. */
		if (enemigos.numNaves > 0) {

			/* Se mueven todos los disparos generados por las naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					for (int k = 0; k < (int)enemigos.enemigos[j][i].vectorDisparos.size(); k++)
						enemigos.enemigos[j][i].vectorDisparos[k].mover(deltaTime.asSeconds());
				}
			}
				
			/* Comprobar el límite derecho del conjunto de naves enemigas. */
			for (int i = 0; i < enemigos.FILAS && flag; i++) {
				if (enemigos.enemigos[i][enemigos.limDcha].isAlive())
					flag = false;
			}
			if (flag)
				enemigos.limDcha--;

			flag = true;

			/* Comprobar el límite izquierdo del conjunto de naves enemigas. */
			for (int i = 0; i < enemigos.FILAS && flag; i++) {
				if (enemigos.enemigos[i][enemigos.limIzda].isAlive())
					flag = false;
			}

			if (flag)
				enemigos.limIzda++;

			flag = true;

			/* Se cambia el sentido de las naves enemigas dependiendo de la posición de las naves que están en los límites. */
			for (int k = 0; k < enemigos.FILAS; k++) {

				if (sentido==1 && enemigos.enemigos[k][enemigos.limDcha].isAlive() && enemigos.enemigos[k][enemigos.limDcha].getPosition().x + enemigos.enemigos[k][enemigos.limDcha].getWidth() + 20 >= GameWindow.getSize().x) {
					sentido = -1;
					for (int j = 0; j < enemigos.FILAS; j++) {
						for (int i = 0; i < enemigos.COLUMNAS; i++)
							enemigos.enemigos[j][i].mover(0, GameWindow.getSize().y / 35.0f);
					}
				}
				else if (sentido == -1 && enemigos.enemigos[k][enemigos.limIzda].isAlive() && enemigos.enemigos[k][enemigos.limIzda].getPosition().x <= 20) {
					sentido = 1;
					for (int j = 0; j < enemigos.FILAS; j++) {
						for (int i = 0; i < enemigos.COLUMNAS; i++)
							enemigos.enemigos[j][i].mover(0, GameWindow.getSize().y / 35.0f);
					}
				}
			}

			/* Se mueve todo el conjunto de naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					enemigos.enemigos[j][i].mover(sentido * enemigos.velocidad * deltaTime.asSeconds(), 0);
				}
			}

			/* Comprobación de colisiones de los disparos con todas las naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					for (int k = 0; k < (int)nave->vectorDisparos.size(); k++) {
						if (nave->vectorDisparos[k].getSprite().getGlobalBounds().intersects(enemigos.enemigos[j][i].getSprite().getGlobalBounds())) {
							//enemigos.enemigos[j][i].explosion();
							enemigos.enemigos[j][i].setAlive(false);
							enemigos.enemigos[j][i].setPosition(-1000, -1000);
							nave->vectorDisparos[k].setAlive(false);
							nave->vectorDisparos[k].setPosition(-2000, -1000);
							//nave->tiempo = 0.0f;
							enemigos.velocidad *= 1.05f;
							enemigos.numNaves--;
							txtPuntos.setString("Puntuación: " + std::to_string(puntos += 100));

							std::cout << enemigos.limDcha << "," << enemigos.limIzda << std::endl;
						}
					}
				}
			}

			/* Comprobación de colisiones de todos los disparos de las naves enemigas con la nave del jugador. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					for (int k = 0; k < (int)enemigos.enemigos[j][i].vectorDisparos.size(); k++) {
						if (enemigos.enemigos[j][i].vectorDisparos[k].getSprite().getGlobalBounds().intersects(nave->getSprite().getGlobalBounds())) {
							nave->setAlive(false);
							std::cout << "Has perdido" << std::endl;
						}
					}
				}
			}

			/* Comprobar colisiones de las naves enemigas con la nave del jugador. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					if (enemigos.enemigos[j][i].getSprite().getGlobalBounds().intersects(nave->getSprite().getGlobalBounds())) {
						nave->setAlive(false);
						std::cout << "Has perdido" << std::endl; 
					}
						
				}
			}

			/* Disparos aleatorios de las naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					if (enemigos.enemigos[j][i].isAlive()) {
						if (j < enemigos.FILAS - 1 && !enemigos.enemigos[j + 1][i].isAlive()) {
							if (rand() % 1001 >= 999) {
								enemigos.enemigos[j][i].disparar();
								enemigos.sonidoDisparo.play();
							}
						}
						else if (j == enemigos.FILAS - 1) {
							if (rand() % 1001 >= 999) {
								enemigos.enemigos[j][i].disparar();
								enemigos.sonidoDisparo.play();
							}
						}
					}
				}
			}
		}

		if (enemigos.numNaves == 0) {
			cambiarNivel = true;
			tiempoX = 0;
		}
	}

	
	
	GameWindow.clear();

	GameWindow.draw(fondo);

	GameWindow.draw(txtPuntos);	

	nave->draw(GameWindow);

	/* Dibujar los disparos de la nave del jugador. */
	for (int i = 0; i < (int)nave->vectorDisparos.size(); i++)
		if(nave->vectorDisparos[i].isAlive())
			nave->vectorDisparos[i].draw(GameWindow);

	/* Se dibujan todas las naves enemigas mientras quede alguna sin destruir. */
	if (enemigos.numNaves > 0) {
		for (int j = 0; j < enemigos.FILAS; j++) {
			for (int i = 0; i < enemigos.COLUMNAS; i++) {
				if (enemigos.enemigos[j][i].isAlive()) {
					enemigos.enemigos[j][i].draw(GameWindow);
					//std::cout << "ID: " << enemigos.enemigos[j][i].getID() << std::endl;
				}
			}
		}	

		/* Se dibujan los disparos de las naves enemigas. */
		for (int j = 0; j < enemigos.FILAS; j++) {
			for (int i = 0; i < enemigos.COLUMNAS; i++) {
				for (int k = 0; k < (int)enemigos.enemigos[j][i].vectorDisparos.size(); k++)
					enemigos.enemigos[j][i].vectorDisparos[k].draw(GameWindow);
			}
		}
	}

	/* Mostrar el texto "PAUSA" si la partida está pausada. */
	if (pausa)
		GameWindow.draw(txtPausa);

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
	case sf::Event::KeyReleased:
		switch (Event.key.code) {
		case sf::Keyboard::P:
		case sf::Keyboard::Pause:
			pausa = !pausa;
			std::cout << pausa << " PAUSA" << std::endl;
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
		GameWindow.setPosition(sf::Vector2i(0, 0));
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


void generarMarcianos(float nivel) {
	/* ----- ENEMIGOS ----- */
	float x, y = GameWindow.getSize().y / 1080.0f * 60.0f * nivel * 0.1 + 10;
	static int id = 0;
	int num = 5;

	enemigos.velocidad = 250.0f;
	enemigos.limDcha = enemigos.COLUMNAS - 1;
	enemigos.limIzda = 0;
	enemigos.numNaves = enemigos.FILAS * enemigos.COLUMNAS;

	if (nivel == 1) {
		for (int j = 0; j < enemigos.FILAS; j++) {
			x = GameWindow.getSize().x / 1920.0f * 60.0f;
			for (int i = 0; i < enemigos.COLUMNAS; i++) {
				Enemigo *enemigo = new Enemigo();
				enemigo->setTexture(*TextureManager::getTexture("enemigoRojo" + std::to_string(num)));
				enemigo->setSize(GameWindow.getSize().x / 1920.0f, GameWindow.getSize().y / 1080.0f);
				switch (num) {
				case 5:
					enemigo->setWidth(97.0f);
					break;
				case 4:
					enemigo->setWidth(82.0f);
					break;
				case 3:
					enemigo->setWidth(103.0f);
					break;
				case 2:
					enemigo->setWidth(104.0f);
					break;
				case 1:
					enemigo->setWidth(93.0f);
					break;
				}
				enemigo->setHeight(84.0f);
				enemigo->setPosition(x, y);
				enemigo->setID(id++);
				enemigo->setSound(enemigos.sonidoExplosion);
				enemigos.enemigos[j].push_back(*enemigo);
				std::cout << "ID: " << enemigo->getID() << std::endl;
				x += 110.0f;
			}
			y += 90.0f;
			num--;
		}
	}
	else {
		nave->vectorDisparos.clear();
		for (int j = 0; j < enemigos.FILAS; j++) {
			x = GameWindow.getSize().x / 1920.0f * 60.0f;
			for (int i = 0; i < enemigos.COLUMNAS; i++) {
				enemigos.enemigos[j][i].setAlive(true);
				enemigos.enemigos[j][i].setPosition(x, y);
				x += 110.0f;
			}
			y += 90.0f;
		}
	}
	

}

