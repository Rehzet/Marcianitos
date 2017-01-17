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
#include <Windows.h>
#include <cmath>

void inicializar();
void gameLoop();
void inputProcessor();

void generarMarcianos(float nivel);
void recolocarMarcianos(float nivel);

 // sf::VideoMode resolucion = _1600x900;
sf::VideoMode resolucion;


 sf::Uint32 modoVentana = sf::Style::None;

 sf::RenderWindow GameWindow;
 sf::Clock Reloj;
 sf::Time deltaTime;

 sf::Sprite fondo;

 sf::Font fuenteKenVector_Future;
 sf::Text txtPuntos;
 sf::Text txtPausa;
 sf::Text txtVidas;
 sf::Text txtNivel;

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
	 int sentido;
 } Enemigos;

 Enemigos enemigos;

 Nave *nave;
 sf::Sprite spriteVidas;

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
	resolucion.width = GetSystemMetrics(SM_CXSCREEN);
	resolucion.height = GetSystemMetrics(SM_CYSCREEN);
	std::cout << resolucion.width << "x" << resolucion.height << std::endl;

	GameWindow.create(resolucion, "Marcianitos", modoVentana, settings);
	GameWindow.setVerticalSyncEnabled(true);
	GameWindow.setPosition(sf::Vector2i(0, 0));
	GameWindow.setMouseCursorVisible(false);

	/* ----- FONDO ----- */
	TextureManager::loadTexture("fondo_azul", "res/Backgrounds/blue.png");
	tempTextur = *TextureManager::getTexture("fondo_azul");
	tempTextur.setRepeated(true);

	fondo.setTexture(tempTextur);
	fondo.setScale(0.5f, 0.5f);
	fondo.setTextureRect({ 0, 0, (int)GameWindow.getSize().x * 2, (int)GameWindow.getSize().y * 2 });

	/* ----- NAVE ----- */
	nave = new Nave(resolucion);
	TextureManager::loadTexture("nave", "res/PNG/playerShip2_red.png");
	nave->figura.setTexture(TextureManager::getTexture("nave"));
	nave->setRightLimit(resolucion.width);
	nave->setWidth(112.0f);
	nave->setHeight(75.0f);
	nave->figura.setScale(GameWindow.getSize().x / 1920.0f, GameWindow.getSize().y / 1080.0f);

	/* ----- VIDAS ----- */
	TextureManager::loadTexture("vida", "res/PNG/UI/playerLife2_red.png");
	spriteVidas.setTexture(*TextureManager::getTexture("vida"));
	spriteVidas.setPosition(40, GameWindow.getSize().y - txtVidas.getCharacterSize() - 5);

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

	txtVidas.setFont(fuenteKenVector_Future);
	txtVidas.setString(std::to_string(nave->getVidas()));
	txtVidas.setCharacterSize(30);
	txtVidas.setPosition(10, GameWindow.getSize().y - txtVidas.getCharacterSize() - 10);

	txtNivel.setFont(fuenteKenVector_Future);
	txtNivel.setCharacterSize(60);
	txtNivel.setPosition((float)GameWindow.getSize().x / 2.0f - 121.0f, (float)GameWindow.getSize().y / 2.0f - 20.0f);

}



bool flag = true;
float tiempoX, parpadeo = 0.0f;
bool alcanzado = false;


void gameLoop() { while (GameWindow.isOpen()) { // Bucle principal del juego

	deltaTime = Reloj.restart();
	inputProcessor();

	if (cambiarNivel) {
		if (tiempoX < 2.0f) {
			tiempoX += deltaTime.asSeconds();
			std::cout << tiempoX << std::endl;			
		}
		else {		
			nivel++;
			generarMarcianos((float)nivel);
			cambiarNivel = false;
		}

	}
	else if(!alcanzado){
		tiempoX = 0;
	}

	if (!pausa && !cambiarNivel && !alcanzado && nave->isAlive()) {

		nave->processInput(deltaTime.asSeconds());

		/* Se mueven todos los disparos generados por la nave del jugador. */
		for (int i = 0; i < (int)nave->vectorDisparos.size(); i++)
			if(nave->vectorDisparos[i].isAlive())
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

				if (enemigos.sentido==1 && enemigos.enemigos[k][enemigos.limDcha].isAlive() && enemigos.enemigos[k][enemigos.limDcha].getPosition().x + enemigos.enemigos[k][enemigos.limDcha].getWidth() + 20 >= GameWindow.getSize().x) {
					enemigos.sentido = -1;
					for (int j = 0; j < enemigos.FILAS; j++) {
						for (int i = 0; i < enemigos.COLUMNAS; i++)
							if (enemigos.enemigos[j][i].isAlive())
								enemigos.enemigos[j][i].mover(0, GameWindow.getSize().y / 35.0f);
					}
				}
				else if (enemigos.sentido == -1 && enemigos.enemigos[k][enemigos.limIzda].isAlive() && enemigos.enemigos[k][enemigos.limIzda].getPosition().x <= 20) {
					enemigos.sentido = 1;
					for (int j = 0; j < enemigos.FILAS; j++) {
						for (int i = 0; i < enemigos.COLUMNAS; i++)
							if (enemigos.enemigos[j][i].isAlive())
								enemigos.enemigos[j][i].mover(0, GameWindow.getSize().y / 35.0f);
					}
				}
			}

			/* Se mueve todo el conjunto de naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					if(enemigos.enemigos[j][i].isAlive())
						enemigos.enemigos[j][i].mover(enemigos.sentido * enemigos.velocidad * deltaTime.asSeconds(), 0.0f);
				}
			}

			/* Comprobación de colisiones de los disparos con todas las naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					for (int k = 0; k < (int)nave->vectorDisparos.size(); k++) {
						if (nave->vectorDisparos[k].isAlive() && nave->vectorDisparos[k].getSprite().getGlobalBounds().intersects(enemigos.enemigos[j][i].getSprite().getGlobalBounds())) {
							//enemigos.enemigos[j][i].explosion();
							enemigos.enemigos[j][i].setAlive(false);
							enemigos.enemigos[j][i].setPosition(-5000.0f, -1000.0f);
							nave->vectorDisparos[k].setAlive(false);
							nave->vectorDisparos[k].setPosition(-2000.0f, -1000.0f);
							//nave->tiempo = 0.0f;
							enemigos.velocidad += 4*log(enemigos.velocidad); 
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
						if (enemigos.enemigos[j][i].vectorDisparos[k].isAlive() && enemigos.enemigos[j][i].vectorDisparos[k].getSprite().getGlobalBounds().intersects(nave->figura.getGlobalBounds())) {
							nave->setVidas(nave->getVidas() - 1);
							enemigos.enemigos[j][i].vectorDisparos[k].setAlive(false);
							enemigos.enemigos[j][i].vectorDisparos[k].setPosition(-2000.0f, -1000.0f);
							alcanzado = true;
						}
					}
				}
			}

			/* Comprobar colisiones de las naves enemigas con la nave del jugador. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					if (enemigos.enemigos[j][i].getSprite().getGlobalBounds().intersects(nave->figura.getGlobalBounds())) {
						nave->setVidas(nave->getVidas() - 1);
						alcanzado = true;
					}						
				}
			}

			/* Disparos aleatorios de las naves enemigas. */
			for (int j = 0; j < enemigos.FILAS; j++) {
				for (int i = 0; i < enemigos.COLUMNAS; i++) {
					if (enemigos.enemigos[j][i].isAlive()) {
						if (j < enemigos.FILAS - 1 && !enemigos.enemigos[j + 1][i].isAlive()) {
							if (rand() % 1001 >= 998) {
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
		if (enemigos.numNaves == 0) 
			cambiarNivel = true;

		if (nave->getVidas() <= 0)
			nave->setAlive(false);
	}

	GameWindow.clear();
	GameWindow.draw(fondo);

	/* Parpadeo de la nave del jugador cuando le alcanza un enemigo. */
	if(!alcanzado)
		nave->draw(GameWindow);
	else {
		if (tiempoX < 2.0f) {
			tiempoX += deltaTime.asSeconds();
			parpadeo += deltaTime.asSeconds();
			if (parpadeo > 0.7f) {
				parpadeo = 0.0f;
			}
			else if(parpadeo <=0.35f){
				nave->draw(GameWindow);
			}				
		}
		else {
			alcanzado = false;
			parpadeo = 0.0f;
			recolocarMarcianos(nivel);
		}
		
	}

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
					if(enemigos.enemigos[j][i].vectorDisparos[k].isAlive())
						enemigos.enemigos[j][i].vectorDisparos[k].draw(GameWindow);
			}
		}

	}

	/* Mostrar el texto "PAUSA" si la partida está pausada. */
	if (pausa)
		GameWindow.draw(txtPausa);

	if (cambiarNivel) {
		txtNivel.setString("Nivel " + std::to_string(nivel+1));
		GameWindow.draw(txtNivel);
	}

	/* Dibujar las vidas. */
	txtVidas.setString(std::to_string(nave->getVidas()));
	GameWindow.draw(txtVidas);
	GameWindow.draw(spriteVidas);

	/* Mostrar texto de puntuación. */
	GameWindow.draw(txtPuntos);

	GameWindow.display();
}}





void inputProcessor() {	static bool moverDcha = false;	static bool moverIzda = false; while (GameWindow.pollEvent(Event)) {
   
	/* Controles teclado. */
	switch (Event.type) {

	case sf::Event::Closed:
		GameWindow.setMouseCursorVisible(true);
		GameWindow.close();		
		break;
	case  sf::Event::KeyPressed:
		switch (Event.key.code) {
		case sf::Keyboard::Escape:
			GameWindow.setMouseCursorVisible(true);
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

		nave->figura.setScale(GameWindow.getSize().x / 1920.0f, GameWindow.getSize().y / 1080.0f);
		nave->figura.setPosition((float)GameWindow.getSize().x / 2 - 56, (float)GameWindow.getSize().y - 100);
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
	float x, y = GameWindow.getSize().y / 1080.0f * 60.0f * nivel * 0.1f + 10.0f;
	static int id = 0;
	int num = 5;

	enemigos.sentido = 1;
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
				x += GameWindow.getSize().x / 1920.0f * 130.0f;
			}
			y += GameWindow.getSize().y / 1080.0f * 100.0f;
			num--;
		}
	}
	else {
		for (int j = 0; j < enemigos.FILAS; j++) {
			for (int i = 0; i < enemigos.COLUMNAS; i++) {
				enemigos.enemigos[j][i].setAlive(true);
			}
		}
		recolocarMarcianos(nivel);
	}
	

}

void recolocarMarcianos(float nivel) {

	float x, y = GameWindow.getSize().y / 1080.0f * 60.0f * nivel * 0.1f + 10.0f;

	nave->vectorDisparos.clear();

	for (int j = 0; j < enemigos.FILAS; j++) {
		for (int i = 0; i < enemigos.COLUMNAS; i++) {
			enemigos.enemigos[j][i].vectorDisparos.clear();
		}
	}

	for (int j = 0; j < enemigos.FILAS; j++) {
		x = GameWindow.getSize().x / 1920.0f * 60.0f;
		for (int i = 0; i < enemigos.COLUMNAS; i++) {
			if(enemigos.enemigos[j][i].isAlive())
				enemigos.enemigos[j][i].setPosition(x, y);
			x += GameWindow.getSize().x / 1920.0f * 130.0f;
		}
		y += GameWindow.getSize().y / 1080.0f * 100.0f;
	}
}