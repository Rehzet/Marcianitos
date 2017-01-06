#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {

	// Mapa de las texturas cargadas.
	static std::map<char*, sf::Texture*> textures;

	// Manually keep track of the order in which textures were loaded, so you can get by index.
	static std::vector<char*> order;

public:
	// El constructor no se va a usar.
	TextureManager();

	// Destructor que elimina las texturas cargadas previamente.
	~TextureManager();

	static int getLength();
	
	// Devuelve una textura con un nombre específico.
	static sf::Texture *getTexture(char* nombre);

	// Devuelve una textura situada en el índice indicado.
	static sf::Texture *getTexture(int index);

	// Carga la textura y devuelve un puntero hacia ella.
	// Si ya está cargada, la función simplemente devuelve la textura.
	// Si no se puede encontrar el archivo, devuelve NULL.
	static sf::Texture *loadTexture(char* nombre, char* ruta);

};

