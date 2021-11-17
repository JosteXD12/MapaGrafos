#include "main.h"
int indx=0;


void Grafos::dibujarPantalla(){
	indx = 0;
	int contador =0;
	pantalla->clear();
	pantalla->draw(*fondo);
	while (contador < n) {
		for (int i = 0; i < lista_vertices->get(contador)->getAristas()->getSize(); i++)
		{
			static Arista* this_arista;
			if (!seleccionarPrim)
			{
				this_arista = lista_vertices->get(contador)->getAristas()->get(i);
				Vertex line[] =
				{
					Vertex(Vector2f(this_arista->getIni_x(), this_arista->getIni_y())),
					Vertex(Vector2f(this_arista->getEnd_x(), this_arista->getEnd_y()))
				};
				if (seleccionarDijkstra && indx < ruta_principal.length())
				{
					if (this_arista->getFrom()->getId() == ruta_principal[indx] && this_arista->getTo()->getId() == ruta_principal[indx + 1])
					{
						line->color = Color::Yellow;
						indx++;
					}

				}
				pantalla->draw(line, 2, Lines);
			}
			else
			{
				this_arista = lista_vertices->get(contador)->getAristas()->get(i);
				if (prim_result->hasIt(this_arista))
				{
					Vertex line[] =
					{
						Vertex(Vector2f(this_arista->getIni_x(), this_arista->getIni_y())),
						Vertex(Vector2f(this_arista->getEnd_x(), this_arista->getEnd_y()))
					};
					line->color = Color::Yellow;
					pantalla->draw(line, 2, Lines);
				}
			}
		}
		pantalla->draw(*lista_vertices->get(contador));
		pantalla->draw(*textoVertices[contador]);
		contador++;
	}
	for (int i = 0; i < txtArista->getSize(); i++) {
		if (dirigido) {
			pantalla->draw(*boxArista->get(i));
		}
		pantalla->draw(*txtArista->get(i));
	}

	pantalla->draw(boton[0]);//Dibujar aristas o vertices
	pantalla->draw(boton[1]);// Agregar peso

	pantalla->draw(boton[2]);// btnDijkstra
	pantalla->draw(boton[3]);// btnWarshall
	pantalla->draw(boton[4]);// btnPrim
	pantalla->draw(boton[5]);// btnKruskal:
	pantalla->draw(boton[6]);
	pantalla->draw(boton[7]);
	pantalla->draw(*textoBtn[0]);
	pantalla->draw(*textoBtn[1]);
	pantalla->draw(*textoBtn[2]);
	pantalla->draw(*textoBtn[3]);
	pantalla->draw(*textoBtn[4]);
	pantalla->draw(*textoBtn[5]);
	pantalla->draw(*textoBtn[6]);
	pantalla->draw(*textoBtn[7]);
	pantalla->draw(box);
	pantalla->draw(box_txt);
	pantalla->draw(resultados);
	pantalla->draw(*nota);
	pantalla->display();

}