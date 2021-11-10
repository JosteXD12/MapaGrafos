#include "main.h" 

void Grafos::dibujarPantalla(){
	int contador =0;
	pantalla->clear();
	pantalla->draw(*fondo);
	while (contador < n) {
		pantalla->draw(arista[contador]);
		contador++;
	}
	pantalla->display();
}