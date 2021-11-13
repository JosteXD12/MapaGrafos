
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
                arista[n].setSize(Vector2f(20, 20));
                arista[n].setPosition(posicionMouse.x, posicionMouse.y);

                textoAristas[n] = new Text(to_string(n), *fuente, 16);
                textoAristas[n]->setFillColor(Color::Black);
                textoAristas[n]->setPosition(posicionMouse.x+2, posicionMouse.y-1);
                n++;
                agregarArista = false;
            }
            if (ColisionMouse() == 1) {
                agregarArista = true;       
            }
            
        }

    }
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


}