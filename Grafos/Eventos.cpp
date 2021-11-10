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
            Vector2i posicionMouse = Mouse::getPosition(*pantalla);
            posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
            arista[n].setSize(Vector2f(16, 16));
            arista[n].setPosition(posicionMouse.x, posicionMouse.y);
            n++;
        }
    }
}

//int Grafos::ColisionMouse() {
//    Vector2i posicionMouse = Mouse::getPosition(*pantalla);
//    posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
//    FloatRect hitboxMouse = Rect<float>::Rect(posicionMouse.x, posicionMouse.y, 1, 1);
//
//}