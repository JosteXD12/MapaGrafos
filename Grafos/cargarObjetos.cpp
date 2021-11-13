#include "main.h"

void Grafos::CargarObjetos() {
	fuente->loadFromFile("Imagenes/arial.ttf");
	mapa->loadFromFile("Imagenes/mapaAmerica.png");
	fondo->setTexture(*mapa);
	fondo->setPosition(Vector2f(365, 20)); 

	textoBtn[0] = new Text("Vertice", *fuente, 24);
	textoBtn[0]->setFillColor(Color(52, 91, 99));

	textoBtn[1] = new Text("Peso", *fuente, 24);
	textoBtn[1]->setFillColor(Color(52, 91, 99));

	textoBtn[2] = new Text("Dijkstra", *fuente, 24);
	textoBtn[2]->setFillColor(Color(52, 91, 99));

	textoBtn[3] = new Text("Warshall", *fuente, 24);
	textoBtn[3]->setFillColor(Color(52, 91, 99));

	textoBtn[4] = new Text("Prim", *fuente, 24);
	textoBtn[4]->setFillColor(Color(52, 91, 99));

	textoBtn[5] = new Text("Kruskal", *fuente, 24);
	textoBtn[5]->setFillColor(Color(52, 91, 99));

	box = setRectangulo(128,32,16,208);
	box_txt.setPosition(16, 208);
	box_txt.setFont(*fuente);
	box_txt.setCharacterSize(18);
	box_txt.setFillColor(Color::Black);

	//============== Botones ========================

	// Agregar
	boton[0] = setRectangulo(128, 32, 16, 112); 
	boton[0].setFillColor(Color(165, 225, 173));
	boton[0].setOutlineColor(Color(100, 175, 99));
	boton[0].setOutlineThickness(4);
	textoBtn[0]->setPosition(48, 112);

	// agregar peso
	boton[1] = setRectangulo(128, 32, 16, 160);
	boton[1].setFillColor(Color(165, 225, 173));
	boton[1].setOutlineColor(Color(100, 175, 99));
	boton[1].setOutlineThickness(4);
	textoBtn[1]->setPosition(48, 160);

	//Dijkstra
	boton[2] = setRectangulo(128, 32, 1222, 112);
	boton[2].setFillColor(Color(165, 225, 173));
	boton[2].setOutlineColor(Color(100, 175, 99));
	boton[2].setOutlineThickness(4);
	textoBtn[2]->setPosition(1238, 112);

	// Warshall
	boton[3] = setRectangulo(128, 32, 1222, 160);
	boton[3].setFillColor(Color(165, 225, 173));
	boton[3].setOutlineColor(Color(100, 175, 99));
	boton[3].setOutlineThickness(4);
	textoBtn[3]->setPosition(1238, 160);

	// Prim
	boton[4] = setRectangulo(128, 32, 1222, 208);
	boton[4].setFillColor(Color(165, 225, 173));
	boton[4].setOutlineColor(Color(100, 175, 99));
	boton[4].setOutlineThickness(4);
	textoBtn[4]->setPosition(1254, 208);

	//Kruskal:
	boton[5] = setRectangulo(128, 32, 1222, 256);
	boton[5].setFillColor(Color(165, 225, 173));
	boton[5].setOutlineColor(Color(100, 175, 99));
	boton[5].setOutlineThickness(4);
	textoBtn[5]->setPosition(1238, 256);
}