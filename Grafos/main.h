#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include <stack>
#include <queue>
#include <fstream>
using namespace std;
using namespace sf;

class Grafos {
public:
	Grafos(int resolX, int ResolY, string titulo);
	void Gameloop();
	void Eventos();
	int ColisionMouse();
	void CargarObjetos();
	void dibujarPantalla();

	bool agregarArista;

	RectangleShape setRectangulo(float ancho, float alto, float x, float y)
	{ //crea un rectangulo
		RectangleShape rectangulo(Vector2f(ancho, alto));
		rectangulo.setPosition(x, y);
		return rectangulo;
	}
	~Grafos();
private:
	RenderWindow* pantalla;
	Event* evento;
	RectangleShape boton[8];
	RectangleShape arista[100];
	Text* textoAristas[100];
	Font* fuente;
	Text* textoBtn[8];
	Sprite *fondo;
	Texture *mapa;
	int n = 0;
};