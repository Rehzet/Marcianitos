#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {

	// Mapa de las texturas cargadas.
	static std::map<std::string, sf::Texture*> textures;

	// Manually keep track of the order in which textures were loaded, so you can get by index.
	static std::vector<std::string> order;

public:
	// El constructor no se va a usar.
	TextureManager();

	// Destructor que elimina las texturas cargadas previamente.
	~TextureManager();

	static int getLength();
	
	// Devuelve una textura con un nombre específico.
	static sf::Texture *getTexture(std::string nombre);

	// Devuelve una textura situada en el índice indicado.
	static sf::Texture *getTexture(int index);

	// Carga la textura y devuelve un puntero hacia ella.
	// Si ya está cargada, la función simplemente devuelve la textura.
	// Si no se puede encontrar el archivo, devuelve NULL.
	static sf::Texture *loadTexture(std::string nombre, std::string ruta);

};

