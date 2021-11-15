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
				lista_vertices->set(new Vertice(posicionMouse.x, posicionMouse.y, 20, 20, 'A' + n));
				string ss = "";
				ss += 'A' + n;
				textoVertices[n] = new Text(ss, *fuente, 16);
				textoVertices[n]->setFillColor(Color::Black);
				textoVertices[n]->setPosition(posicionMouse.x + 2, posicionMouse.y - 1);

				if (select_grafo != nullptr)
				{
					select_grafo->getAristas()->set(new Arista(select_grafo->getPosition().x + 10, select_grafo->getPosition().y + 10, lista_vertices->get(n)->getPosition().x + 10, lista_vertices->get(n)->getPosition().y + 10, 0, select_grafo, lista_vertices->get(n)));
				}
				else
				{
					if (selec_algorit[0] == nullptr)
					{
						cout << "entro1" << endl;
						selec_algorit[0] = lista_vertices->get(n);
						selec_algorit[0]->setFillColor(Color::Yellow);
					}
					else if (selec_algorit[1] == nullptr)
					{
						cout << "entro2" << endl;
						selec_algorit[1] = lista_vertices->get(n);

						selec_algorit[0]->getAristas()->set(new Arista(selec_algorit[0]->getPosition().x + 10, selec_algorit[0]->getPosition().y + 10, selec_algorit[1]->getPosition().x + 10, selec_algorit[1]->getPosition().y + 10, 0, selec_algorit[0], selec_algorit[1]));
						selec_algorit[1]->setFillColor(Color::Yellow);
						activarTexbox = true;
					}
					agregarVertice = false;
				}
				n++;

			}
			//============= Selecciona 2 vertices ====================
			if (seleccionarVertice == true) {
				verticesSeleccionados();
				if (selec_algorit[1] != nullptr) {
					seleccionarVertice = false;
					selec_algorit[0]->getAristas()->set(new Arista(selec_algorit[0]->getPosition().x + 10, selec_algorit[0]->getPosition().y + 10, selec_algorit[1]->getPosition().x + 10, selec_algorit[1]->getPosition().y + 10, 0, selec_algorit[0], selec_algorit[1]));
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
				Dijkstra(selec_algorit[0], selec_algorit[1]);
				break;
			case 4:
				Warshall(selec_algorit[0], selec_algorit[1]);

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
				box.setOutlineColor(Color::Yellow);
				if (char(evento->text.unicode) == '1' || char(evento->text.unicode) == '2' || char(evento->text.unicode) == '3'
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
					if (lista_vertices->get(i) == selec_algorit[0]) {

					}
				}

				if (selec_algorit[1] != nullptr) {
					int Ipeso;
					istringstream(box_txt.getString()) >> Ipeso;
					selec_algorit[0]->getAristas()->get(0)->setPeso(Ipeso);
				}

				// ==========    vaciar   ====================
				y = "";
				box_txt.setString(y);
				selec_algorit[0] = nullptr;
				selec_algorit[1] = nullptr;
				activarTexbox = false;
				select_grafo = nullptr;
				box.setOutlineColor(Color(100, 175, 99));
			}
		}
	}
}

int Grafos::colisionVertices(Vertice* send) {
	static bool s = true;
	if (s) {
		selec_algorit[0] = send;
	}
	else
	{
		selec_algorit[1] = send;
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
			select_grafo = lista_vertices->get(i);
			return colisionVertices(lista_vertices->get(i));
		}
	}
}

// =================== algoritmos ===============================
void Grafos::Dijkstra(Vertice* from, Vertice* to) {
	static Vertice* act;
	static Etiqueta* temp;
	static Arista* element;
	ruta_principal = "";
	act = from;
	static string ruta;
	static ArrayList<Vertice*>* etiquetas;
	etiquetas = new ArrayList<Vertice*>();
	static Vertice* lowest;
	lowest = nullptr;
	act->setEtiqueta(new Etiqueta{ 0, nullptr, 0 });
	etiquetas->set(act);
	while (true)
	{
		act->setVisitado(true);
		for (int i = 0; i < act->getAristas()->getSize(); i++)
		{
			temp = nullptr;
			element = act->getAristas()->get(i);
			if (element->getTo()->isVisitado()) continue;
			if (element->getTo()->getEtiqueta() != nullptr)
			{
				temp = new Etiqueta{ element->getPeso() + act->getEtiqueta()->dist, act, act->getEtiqueta()->iter + 1 };
				if (element->getTo()->getEtiqueta()->dist >= temp->dist)
				{
					element->getTo()->setEtiqueta(temp);
				}
			}
			else
			{
				element->getTo()->setEtiqueta(new Etiqueta{ element->getPeso() + act->getEtiqueta()->dist, act, act->getEtiqueta()->iter + 1 });
				etiquetas->set(element->getTo());
			}
		}
		for (int i = 0; i < etiquetas->getSize(); i++)
		{
			if (etiquetas->get(i)->isVisitado()) continue;
			if (lowest == nullptr) lowest = etiquetas->get(i);
			else
			{
				lowest = (etiquetas->get(i)->getEtiqueta()->dist <= lowest->getEtiqueta()->dist ? etiquetas->get(i) : lowest);
			}
		}

		if (lowest == nullptr) break;
		act = lowest;
		lowest = nullptr;
	}
	static string ss;
	ss = "";
	ruta = "";
	for (int i = 1; i < etiquetas->getSize(); i++)
	{
		act = etiquetas->get(i);
		while (act != from)
		{
			ruta += act->getId();
			ruta += '-';
			act = act->getEtiqueta()->from;
		}
		ruta += act->getId();
		for (int j = ruta.length() - 1; j >= 0; j--)
		{
			ss += ruta[j];
		}
		rutas_cortas->set(ss);
		ruta = "";
		ss = "";
	}
	ruta = "";
	ss = "";
	act = to;
	while (act != from)
	{
		ruta_principal += act->getId();
		ruta_principal += '-';
		act = act->getEtiqueta()->from;
	}
	ruta_principal += act->getId();
	for (int j = ruta_principal.length() - 1; j >= 0; j--)
	{
		ss += ruta_principal[j];
	}
	ruta_principal = ss;
}
void Grafos::Warshall(Vertice* from, Vertice* to) {

}
void Grafos::Prim() {
	return Kruskal();
}
void Grafos::Kruskal() {


	ArrayList<Arista*>* AuxList = new ArrayList<Arista*>();
	ArrayList<Vertice*>* A = new ArrayList<Vertice*>();
	ArrayList<Vertice*>* B = new ArrayList<Vertice*>();
	ArrayList<Arista*>* result = new ArrayList<Arista*>();
	Arista* obtArista = nullptr;
	Arista* baja = nullptr;


	lista_aristas->clear();
	for (int i = 0; i < lista_vertices->getSize();i++) {
		for (int j = 0; j < lista_vertices->get(i)->getAristas()->getSize(); j++) {
			lista_aristas->set(lista_vertices->get(i)->getAristas()->get(j));
		}
	}

	A->set(lista_vertices->get(0));
	lista_vertices->get(0)->setGrupo('A');
	lista_vertices->get(0)->setVisitado(true);

	for (int i = 1; i < lista_vertices->getSize(); i++) {
		B->set(lista_vertices->get(i));
	}

	while (true) {

		AuxList->clear();
		for (int i = 0; i < lista_aristas->getSize(); i++) {
			obtArista = lista_aristas->get(i);
			if (obtArista->getFrom()->getGrupo() != obtArista->getTo()->getGrupo()) {
				AuxList->set(obtArista);
			}
		}
		baja = nullptr;
		for (int i = 0; i < AuxList->getSize(); i++) {
			if (AuxList->get(i)->getFrom()->isVisitado()) {
				continue;
			}

			if (baja == nullptr) {
				baja = AuxList->get(i);
			}

			if (AuxList->get(i)->getPeso() <= baja->getPeso()) {
				baja = AuxList->get(i);
			}
		}
		if (baja == nullptr) {
			break;
		}
		baja->getFrom()->setGrupo('A');
		baja->setVistado(true);
	}
	for (int i = 0; i < lista_vertices->getSize(); i++) {
		for (int j = 0; j < lista_vertices->get(i)->getAristas()->getSize(); j++) {
			if (lista_vertices->get(i)->getAristas()->get(j)->getFrom()->getGrupo() == lista_vertices->get(i)->getAristas()->get(j)->getTo()->getGrupo()) {
				result->set(lista_vertices->get(i)->getAristas()->get(j));
			}
		}
	}
}