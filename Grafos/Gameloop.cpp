#include "main.h"

Grafos::Grafos(int resolX, int resolY, string titulo)
{
    pantalla = new RenderWindow(VideoMode(resolX, resolY), titulo);
	evento = new Event;
	fondo = new Sprite;
	mapa = new Texture;
	CargarObjetos();
	Gameloop();
}
void Grafos::Gameloop() {
	while (pantalla->isOpen())
	{
		dibujarPantalla();
		Eventos();
	}
}