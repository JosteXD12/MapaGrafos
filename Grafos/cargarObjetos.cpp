#include "main.h" 

void Grafos::CargarObjetos() {
	mapa->loadFromFile("Imagenes/mapaAmerica.png");
	fondo->setTexture(*mapa);
	fondo->setPosition(Vector2f(365, 20)); 
}