#include "TextureManager.h"

// Constructor. No se usa
TextureManager::TextureManager() {}

std::map<char*, sf::Texture*> TextureManager::textures;
std::vector<char*> TextureManager::order;


// Devuelve la longitud del array de texturas
int TextureManager::getLength() {
	return textures.size();
}


sf::Texture *TextureManager::getTexture(char* nombre) {

	// Comprobamos si la textura se había cargado previamente.
	if (textures.find(nombre) != textures.end())
		return textures[nombre];
	else
		return NULL;
}


sf::Texture *TextureManager::getTexture(int index) {
	// Stay DRY and reuse get by name, but get string name from vector with index.
	return getTexture(order.at(index));
}

// Asigna un nombre y una ruta a una textura.
sf::Texture *TextureManager::loadTexture(char* nombre, char* ruta) {

	// Si no se ha creado todavía, se hace ahora.
	sf::Texture *texture = new sf::Texture;

	if (texture->loadFromFile(ruta)) {
		textures[nombre] = texture;

		// Push to vector the order in which items were loaded into map, for accessing via index.
		order.push_back(nombre);
		return textures[nombre];
	}
	else {
		// Si no se ha podido cargar el archivo.
		delete texture;
		return NULL;
	}
}

TextureManager::~TextureManager() {

	// Elimina todas las texturas que se han utilizado.
	sf::Texture *texture;
	std::map<char*, sf::Texture*>::iterator it = textures.begin();
	while (it != textures.end()) {
		texture = it->second;
		delete texture;
		it++;
	}
}