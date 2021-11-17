#pragma once
#include "SFML/Graphics.hpp"
#include "ArrayList.h"
#include "Arista.h"
#include <sstream>


#define INF 0x3f3f3f3f


class Grafos {
public:

	Grafos(int resolX, int ResolY, string titulo);
	void Gameloop();
	void Eventos();
	int ColisionMouse();
	int colisionVertices(Vertice* send);
	void CargarObjetos();
	void dibujarPantalla();
	void Dijkstra(Vertice* from, Vertice* to);
	void Warshall(Vertice* from, Vertice* to);
	void Prim();
	void Kruskal();
	int verticesSeleccionados();
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
	ArrayList<Vertice*>* lista_vertices=new ArrayList<Vertice*>();
	ArrayList<Arista*>* lista_aristas = new ArrayList<Arista*>();
	Text* textoVertices[100];
	Font* fuente;
	Text* textoBtn[8];
	Sprite* fondo;
	Texture* mapa;
	int n = 0;
	int** matriz;
	Vertice* selec_algorit[2] = {nullptr,nullptr};
	Vertice* select_grafo = nullptr;
	bool agregarVertice=false;
	bool seleccionarVertice=false;
	bool activarTexbox = false;
	bool seleccionarDijkstra = false;
	bool seleccionarPrim = false;
	bool seleccionarWarsh = false;
	bool dirigido = false;
	ArrayList<string>* rutas_cortas= new ArrayList<string>();
	string ruta_principal;
	RectangleShape box;
	Text box_txt;
	String y;

	ArrayList<RectangleShape*>* boxArista= new ArrayList<RectangleShape*>;
	ArrayList<Text*>* txtArista = new ArrayList<Text*>;
	ArrayList<Arista*>* result = new ArrayList<Arista*>();
};
