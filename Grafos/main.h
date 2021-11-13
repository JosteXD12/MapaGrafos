#pragma once
#include "SFML/Graphics.hpp"
#include "ArrayList.h"
#include "Arista.h"


#define INF 0x3f3f3f3f


class Grafos {
public:

	Grafos(int resolX, int ResolY, string titulo);
	void Gameloop();
	void Eventos();
	int ColisionMouse();
	void CargarObjetos();
	void dibujarPantalla();

	bool agregarArista;

	void definirMatriz() {
		matriz = new int* [n];
		for (int i = 0; i < n; i++) {
			matriz[i] = new int[n];
		}
		llenarMatriz();
	}
	void borrarMatriz() {
		for (int i = 0; i < n; i++) {
			delete[] matriz[i];
		}
	}
	void llenarMatriz() {
		for (int i = 0; i < n; i++) {
			if (matriz[i][i] < 0) {
				matriz[i][i] = INF;
			}
		}
	}

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
	ArrayList<Vertice*>* lista_vertices;
	Text* textoAristas[100];
	Font* fuente;
	Text* textoBtn[8];
	Sprite* fondo;
	Texture* mapa;
	int n = 0;
	int** matriz;
};
