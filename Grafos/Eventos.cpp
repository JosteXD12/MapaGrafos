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
            if (ColisionMouse() == 0) {
                return;
            }
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
            if (ColisionMouse() == 1) {
                agregarArista = true;
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
    if (boton[3].getGlobalBounds().intersects(hitboxMouse)) {
        return 4;
    }
    if (boton[4].getGlobalBounds().intersects(hitboxMouse)) {
        return 5;
    }
    if (boton[5].getGlobalBounds().intersects(hitboxMouse)) {
        return 6;
    }
    for (int i = 0; i < lista_vertices->getSize(); i++) {
        if (lista_vertices->get(i)->getGlobalBounds().intersects(hitboxMouse)) {
            return colisionVertices(lista_vertices->get(i));
        }
    }
}