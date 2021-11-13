#include "main.h"



void Grafos::Eventos() {
    while (pantalla->pollEvent(*evento)) {
        switch (evento->type)
        {
        case Event::Closed:
            pantalla->close();
            exit(0);
            break;
        case Event::MouseButtonPressed:
            if (agregarArista == true) {
                Vector2i posicionMouse = Mouse::getPosition(*pantalla);
                posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
                lista_vertices->set(new Vertice(posicionMouse.x, posicionMouse.y, 20, 20, n));


                textoAristas[n] = new Text(to_string(n), *fuente, 16);
                textoAristas[n]->setFillColor(Color::Black);
                textoAristas[n]->setPosition(posicionMouse.x + 2, posicionMouse.y - 1);
                n++;
                agregarArista = false;
            }
            switch (ColisionMouse())
            {
            case 1:
                agregarArista = true;
                break;
            case 2:
                break;

            case 3:
               Dijkstra(selec[0], selec[1]);
                break;
            case 4:
                Warshall(selec[0], selec[1]);

            case 5:
                Prim();
                break;
            case 6:
                Kruskal();
                break;
            default:
                break;
            }
            if (ColisionMouse() == 3) {
                
            }
        }

    }
}

int Grafos::colisionVertices(Vertice* send) {
    static bool s=true;
    if (s) {
        selec[0] = send;
    }
    else
    {
        selec[1] = send;
    }
    s = (s ? false : true);

    return 0;
}

int Grafos::ColisionMouse() {
    Vector2i posicionMouse = Mouse::getPosition(*pantalla);
    posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
    FloatRect hitboxMouse = Rect<float>::Rect(posicionMouse.x, posicionMouse.y, 1, 1); 

    if (boton[0].getGlobalBounds().intersects(hitboxMouse)) {
        return 1; 
    }
    if (boton[1].getGlobalBounds().intersects(hitboxMouse)) {
        return 2; 
    }



    // btnDijkstra
    if (boton[2].getGlobalBounds().intersects(hitboxMouse)) {
        return 3; 
    }
    // warkshall
    if (boton[3].getGlobalBounds().intersects(hitboxMouse)) {
        return 4;
    }
    // Prim
    if (boton[4].getGlobalBounds().intersects(hitboxMouse)) {
        return 5;
    }
    // Kruskal:
    if (boton[5].getGlobalBounds().intersects(hitboxMouse)) {
        return 6;
    }
    for (int i = 0; i < lista_vertices->getSize(); i++) {
        if (lista_vertices->get(i)->getGlobalBounds().intersects(hitboxMouse)) {
            return colisionVertices(lista_vertices->get(i));
        }
    }
}

// =================== algoritmos ===============================
void Grafos::Dijkstra(Vertice* from, Vertice* to) {

}
void Grafos::Warshall(Vertice* from, Vertice* to) {

}
void Grafos::Prim() {

}
void Grafos::Kruskal() {

}