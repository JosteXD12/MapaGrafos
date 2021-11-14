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
            if (agregarVertice == true) {
                Vector2i posicionMouse = Mouse::getPosition(*pantalla);
                posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
                lista_vertices->set(new Vertice(posicionMouse.x, posicionMouse.y, 20, 20, n));


                textoVertices[n] = new Text(to_string(n), *fuente, 16);
                textoVertices[n]->setFillColor(Color::Black);
                textoVertices[n]->setPosition(posicionMouse.x + 2, posicionMouse.y - 1);

                if (n >0) {                   
                    lista_vertices->get(n);
                    lista_vertices->get(n-1);
                }
                n++;
                agregarVertice = false;
            }
            //============= Selecciona 2 vertices ====================
            if (seleccionarVertice == true) {
                verticesSeleccionados();
                if (selec[1] != nullptr) {
                    seleccionarVertice = false;
                    activarTexbox = true;
                }
            }
            //================== Botones ======================
            switch (ColisionMouse())
            {
            case 1:
                agregarVertice = true;
                break;
            case 2:
                seleccionarVertice = true;
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
            //=====================================================

        case Event::TextEntered:
            if (activarTexbox) {
                if (char(evento->text.unicode)=='1' || char(evento->text.unicode) == '2' || char(evento->text.unicode) == '3'
                    || char(evento->text.unicode) == '4' || char(evento->text.unicode) == '5' || char(evento->text.unicode) == '6'
                    || char(evento->text.unicode) == '7' || char(evento->text.unicode) == '8' || char(evento->text.unicode) == '9' || char(evento->text.unicode) == '0') {
                    y += char(evento->text.unicode);
                    box_txt.setString(y);
                }
            }
        case Event::KeyPressed:
            if (evento->key.code == Keyboard::Enter) {
                int a, b;
                for (int i = 0; i < n; i++) {
                    lista_vertices->get(i)->setFillColor(Color::White);
                }

                for (int i = 0; i < n; i++) {
                    if (lista_vertices->get(i) == selec[0]) {
                        
                    }
                }

                y = "";

                box_txt.setString(y);
                activarTexbox = false;
                //selec[0] = nullptr;
                //selec[1] = nullptr;
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
}

// Seleciona 2 vertices y les cambia el color en pantalla
int Grafos::verticesSeleccionados() {
    Vector2i posicionMouse = Mouse::getPosition(*pantalla);
    posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
    FloatRect hitboxMouse = Rect<float>::Rect(posicionMouse.x, posicionMouse.y, 1, 1);

    for (int i = 0; i < lista_vertices->getSize(); i++) {
        if (lista_vertices->get(i)->getGlobalBounds().intersects(hitboxMouse)) {
            lista_vertices->get(i)->setFillColor(Color::Yellow);
            return colisionVertices(lista_vertices->get(i));
        }
    }
}

// =================== algoritmos ===============================
void Grafos::Dijkstra(Vertice* from, Vertice* to) {
    Vertice* act = from;
    ArrayList<Vertice*>* etiquetas;
    Vertice* lowest = nullptr;
    act->setEtiqueta(new Etiqueta{ 0, nullptr, 0 });
    etiquetas->set(act);
    while (act != to)
    {
        act->setVisitado(true);
        for (int i = 0; i < act->getAristas()->getSize(); i++)
        {
            Arista* element = act->getAristas()->get(i);
            if (element->getVertice()->getEtiqueta() != nullptr) continue;
            element->getVertice()->setEtiqueta(new Etiqueta{ element->getPeso() + act->getEtiqueta()->dist, act, act->getEtiqueta()->iter + 1 });
            etiquetas->set(element->getVertice());
        }
        for (int i = 0; i < etiquetas->getSize(); i++)
        {
            if (lowest == nullptr) lowest = etiquetas->get(i);
            else
            {
                lowest = (etiquetas->get(i)->getEtiqueta()->dist <= lowest->getEtiqueta()->dist ? etiquetas->get(i) : lowest);
            }
        }
    }

}
void Grafos::Warshall(Vertice* from, Vertice* to) {

}
void Grafos::Prim() {

}
void Grafos::Kruskal() {

}