#include "main.h" 

void Grafos::dibujarPantalla(){
	int contador =0;
	pantalla->clear();
	pantalla->draw(*fondo);
	while (contador < n) {
		pantalla->draw(arista[contador]);
		pantalla->draw(*textoAristas[contador]);
		contador++;
	}
	pantalla->draw(boton[0]);//Dibujar aristas o vertices
	pantalla->draw(boton[1]);// Agregar peso

	pantalla->draw(boton[2]);// btnDijkstra
	pantalla->draw(boton[3]);// btnWarshall
	pantalla->draw(boton[4]);// btnPrim
	pantalla->draw(boton[5]);// btnKruskal:
	pantalla->draw(*textoBtn[0]);
	pantalla->draw(*textoBtn[1]);
	pantalla->draw(*textoBtn[2]);
	pantalla->draw(*textoBtn[3]);
	pantalla->draw(*textoBtn[4]);
	pantalla->draw(*textoBtn[5]);
	pantalla->display();
}