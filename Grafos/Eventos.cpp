#include "main.h"
#include <queue>


bool areSame(string ss1, string ss2)
{
	return ss1.compare(ss2) == 0 ? true : false;
}


Vertice* Grafos::getParent(char id)
{
	for (int i = 0; i < lista_vertices->getSize(); i++)
	{
		if (lista_vertices->get(i)->getId() == id) return lista_vertices->get(i);
	}
}
void Grafos::limpiar()
{
	n = 0;
	lista_vertices->deleteAll();
	boxArista->deleteAll();
	txtArista->deleteAll();

	y = "";
	box_txt.setString(y);
	selec_algorit[0] = nullptr;
	selec_algorit[1] = nullptr;
	agregarVertice = false;
	activarTexbox = false;
	select_grafo = nullptr;
	seleccionarVertice = false;
	seleccionarDijkstra = false;
	seleccionarWarsh = false;
	box.setOutlineColor(Color(100, 175, 99));
	boton[0].setOutlineColor(Color(100, 175, 99));
	boton[1].setOutlineColor(Color(100, 175, 99));
	boton[2].setOutlineColor(Color(100, 175, 99));
	boton[3].setOutlineColor(Color(100, 175, 99));
	boton[4].setOutlineColor(Color(100, 175, 99));
	boton[5].setOutlineColor(Color(100, 175, 99));
	boton[6].setOutlineColor(Color(100, 175, 99));
	//boton[7].setOutlineColor(Color(100, 175, 99));
	rutas_cortas->clear();
	ruta_principal = "";
	strResultados = "";
	resultados.setString(strResultados);
}

void Grafos::Eventos() {
	while (pantalla->pollEvent(*evento)) {
		switch (evento->type)
		{
		case Event::Closed:
			pantalla->close();
			exit(0);
			break;
		case Event::MouseButtonPressed:
			if (agregarVertice == true&&(selec_algorit[0] == nullptr || selec_algorit[1] == nullptr)) {
				Vector2i posicionMouse = Mouse::getPosition(*pantalla);
				posicionMouse = (Vector2i)pantalla->mapPixelToCoords(posicionMouse);
				lista_vertices->set(new Vertice(posicionMouse.x, posicionMouse.y, 20, 20, 'A' + n));
				string ss = "";
				ss += 'A' + n;
				textoVertices[n] = new Text(ss, *fuente, 16);
				textoVertices[n]->setFillColor(Color::Black);
				textoVertices[n]->setPosition(posicionMouse.x + 2, posicionMouse.y - 1);

				if (select_grafo != nullptr&&(seleccionarVertice == true || agregarVertice == true))
				{
					select_grafo->getAristas()->set(new Arista(select_grafo->getPosition().x + 10, select_grafo->getPosition().y + 10, lista_vertices->get(n)->getPosition().x + 10, lista_vertices->get(n)->getPosition().y + 10, 0, select_grafo, lista_vertices->get(n)));
				}
				else
				{
					if (selec_algorit[0] == nullptr && agregarVertice == true)
					{
						cout << "entro1" << endl;
						selec_algorit[0] = lista_vertices->get(n);
						selec_algorit[0]->setFillColor(Color::Yellow);
					}
					else if (selec_algorit[1] == nullptr&& agregarVertice == true)
					{
						cout << "entro2" << endl;
						selec_algorit[1] = lista_vertices->get(n);

						selec_algorit[0]->getAristas()->set(new Arista(selec_algorit[0]->getPosition().x + 10, selec_algorit[0]->getPosition().y + 10, selec_algorit[1]->getPosition().x + 10, selec_algorit[1]->getPosition().y + 10, 0, selec_algorit[0], selec_algorit[1]));
						if (!dirigido) {
							selec_algorit[1]->getAristas()->set(new Arista(selec_algorit[1]->getPosition().x + 10, selec_algorit[1]->getPosition().y + 10, selec_algorit[0]->getPosition().x + 10, selec_algorit[0]->getPosition().y + 10, 0, selec_algorit[1], selec_algorit[0]));
						}
						selec_algorit[1]->setFillColor(Color::Yellow);
						activarTexbox = true;
					}
				}
				n++;

			}
			//============= Selecciona 2 vertices ====================
			if (seleccionarVertice == true) {
				verticesSeleccionados();
				if (selec_algorit[1] != nullptr && selec_algorit[0] != nullptr&& seleccionarVertice) {
					selec_algorit[0]->getAristas()->set(new Arista(selec_algorit[0]->getPosition().x + 10, selec_algorit[0]->getPosition().y + 10, selec_algorit[1]->getPosition().x + 10, selec_algorit[1]->getPosition().y + 10, 0, selec_algorit[0], selec_algorit[1]));
					if (!dirigido) {
						selec_algorit[1]->getAristas()->set(new Arista(selec_algorit[1]->getPosition().x + 10, selec_algorit[1]->getPosition().y + 10, selec_algorit[0]->getPosition().x + 10, selec_algorit[0]->getPosition().y + 10, 0, selec_algorit[1], selec_algorit[0]));
					}
					activarTexbox = true;
				}
			}
			if (seleccionarDijkstra == true) {
				verticesSeleccionados();
				if (selec_algorit[1] != nullptr&& selec_algorit[0] != nullptr&& seleccionarDijkstra) {
					Dijkstra(selec_algorit[0], selec_algorit[1]);
				}

			}
			if (seleccionarWarsh == true) {
				verticesSeleccionados();
				if (selec_algorit[1] != nullptr && selec_algorit[0] != nullptr && seleccionarWarsh) {
					Dijkstra(selec_algorit[0], selec_algorit[1]);
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
				seleccionarDijkstra = true;
				break;
			case 4:
				seleccionarWarsh = true;
				break;

			case 5:
				seleccionarPrim = true;
				Prim();
				break;
			case 6:
				seleccionarPrim = true;
				Prim();
				break;
			case 7:
				limpiar();
				break;

			case 8:
				dirigido = (dirigido ? false : true);
				cout << dirigido << endl;
				if (!dirigido) {
					boton[7].setOutlineColor(Color(100, 175, 99));
				}
				if (dirigido) {
					boton[7].setOutlineColor(Color::Yellow);
				}
				n = 0;
				lista_vertices->deleteAll();
				boxArista->deleteAll();
				txtArista->deleteAll();
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
			if (evento->key.code == Keyboard::C) 
			{
				limpiar();
				FileManager* file= new FileManager(OPERATION::READ, grafo_file);
				file->loadLine();
				dirigido = stoi(file->getThisLine());
				file->loadLine();
				while (!areSame(file->getThisLine(), "$"))
				{
					int x = 0;
					int y = 0;
					char id = file->nextChar();
					string num = "";
					file->nextChar();
					char aux;
					aux= file->nextChar();
					while (aux != '|')
					{
						num += aux;
						aux = file->nextChar();
					}
					x = stoi(num);
					num = "";
					aux = file->nextChar();
					while (aux != '|')
					{
						num += aux;
						aux = file->nextChar();
					}
					y = stoi(num);
					lista_vertices->set(new Vertice(x, y, 20, 20, id));
					textoVertices[n] = new Text(id, *fuente, 16);
					textoVertices[n]->setPosition(x, y);
					textoVertices[n]->setFillColor(Color::Black);
					n++;
					file->loadLine();
				}
				file->loadLine();
				while (!areSame(file->getThisLine(), "$"))
				{
					int peso = 0;
					char id_from = file->nextChar();
					file->nextChar();
					char id_to = file->nextChar();
					char aux;
					file->nextChar();
					aux = file->nextChar();
					string num = "";
					while (aux != '|')
					{
						num += aux;
						aux = file->nextChar();
					}
					peso = stoi(num);
					Vertice* from = getParent(id_from);
					Vertice* to = getParent(id_to);
					from->getAristas()->set(new Arista(from->getPosition().x + 10, from->getPosition().y + 10, to->getPosition().x + 10, to->getPosition().y + 10, peso, from, to));
					Arista* aux_arista = from->getAristas()->get(from->getAristas()->getSize() - 1);
					txtArista->set(new Text(to_string(peso), *fuente, 25));
					txtArista->get(txtArista->getSize() - 1)->setPosition((aux_arista->getIni_x() + aux_arista->getEnd_x()) / 2 , (aux_arista->getIni_y() + aux_arista->getEnd_y()) / 2);
					txtArista->get(txtArista->getSize() - 1)->setFillColor(Color::Yellow);
					if (dirigido)
					{
						boxArista->set(new RectangleShape(Vector2f(8, 8)));
						int xb = (from->getPosition().x + to->getPosition().x) / 2;
						int yb = (from->getPosition().y + to->getPosition().y) / 2;
						xb = (xb + to->getPosition().x) / 2;
						yb = (yb + to->getPosition().y) / 2;
						xb = (xb + to->getPosition().x) / 2;
						yb = (yb + to->getPosition().y) / 2;
						boxArista->get(boxArista->getSize() - 1)->setPosition(xb, yb);
					}
					file->loadLine();
				}
				cout << n << endl;
			}
			if (evento->key.code == Keyboard::G) 
			{
				FileManager::clearFile(grafo_file);
 				FileManager* file = new FileManager(OPERATION::WRITE, grafo_file);
				file->pushLine((dirigido ? "1" : "0"));
				lista_vertices->foreach([file](Vertice* vertice) -> void
				{
					file->pushLine(vertice->toString());
				});
				file->pushLine("$");
				lista_vertices->foreach([file](Vertice* vertice) -> void
				{
					vertice->getAristas()->foreach([file](Arista* arista) -> void
					{
							file->pushLine(arista->toString());
					});
				});
				file->pushLine("$");
				file->end();
			}

			if (evento->key.code == Keyboard::Enter) {
				int a, b;
				for (int i = 0; i < n; i++) {
					lista_vertices->get(i)->setFillColor(Color::White);
				}

				for (int i = 0; i < n; i++) {
					if (lista_vertices->get(i) == selec_algorit[0]) {

					}
				}

				if (selec_algorit[1] != nullptr&& selec_algorit[0] != nullptr) {
					if (seleccionarVertice==true || agregarVertice==true) {
						int Ipeso;
						istringstream(box_txt.getString()) >> Ipeso;
						selec_algorit[0]->getAristas()->get(selec_algorit[0]->getAristas()->getSize() - 1)->setPeso(Ipeso);
						if (!dirigido) {
							selec_algorit[1]->getAristas()->get(selec_algorit[1]->getAristas()->getSize() - 1)->setPeso(Ipeso);
						}
					}
					if (dirigido) {
						boxArista->set(new RectangleShape(Vector2f(8, 8)));
						int x = (selec_algorit[0]->getPosition().x + selec_algorit[1]->getPosition().x) / 2;
						int y = (selec_algorit[0]->getPosition().y + selec_algorit[1]->getPosition().y) / 2;
						x = (x + selec_algorit[1]->getPosition().x) / 2;
						y = (y + selec_algorit[1]->getPosition().y) / 2;
						x = (x + selec_algorit[1]->getPosition().x) / 2;
						y = (y + selec_algorit[1]->getPosition().y) / 2;

						boxArista->get(boxArista->getSize() - 1)->setPosition(x, y);
					}
					if (seleccionarVertice == true || agregarVertice == true) {
						txtArista->set(new Text(to_string(selec_algorit[0]->getAristas()->get(selec_algorit[0]->getAristas()->getSize() - 1)->getPeso()), *fuente, 25));
						txtArista->get(txtArista->getSize() - 1)->setPosition((selec_algorit[0]->getPosition().x + selec_algorit[1]->getPosition().x) / 2, (selec_algorit[0]->getPosition().y + selec_algorit[1]->getPosition().y) / 2);
						txtArista->get(txtArista->getSize() - 1)->setFillColor(Color::Yellow);
					}
				}
				if (seleccionarDijkstra || seleccionarWarsh || seleccionarPrim) {
					n = 0;
					lista_vertices->deleteAll();
					boxArista->deleteAll();
					txtArista->deleteAll();
				}

				// ==========    vaciar   ====================
				y = "";
				box_txt.setString(y);
				selec_algorit[0] = nullptr;
				selec_algorit[1] = nullptr;
				agregarVertice = false;
				activarTexbox = false;
				select_grafo = nullptr;
				seleccionarVertice = false;
				seleccionarDijkstra = false;
				seleccionarWarsh = false;
				box.setOutlineColor(Color(100, 175, 99));
				boton[0].setOutlineColor(Color(100, 175, 99));
				boton[1].setOutlineColor(Color(100, 175, 99));
				boton[2].setOutlineColor(Color(100, 175, 99));
				boton[3].setOutlineColor(Color(100, 175, 99));
				boton[4].setOutlineColor(Color(100, 175, 99));
				boton[5].setOutlineColor(Color(100, 175, 99));
				boton[6].setOutlineColor(Color(100, 175, 99));
				//boton[7].setOutlineColor(Color(100, 175, 99));
				rutas_cortas->clear();
				ruta_principal = "";
				strResultados = "";
				resultados.setString(strResultados);
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
		boton[0].setOutlineColor(Color::Yellow);
		return 1;
	}
	if (boton[1].getGlobalBounds().intersects(hitboxMouse)) {
		boton[1].setOutlineColor(Color::Yellow);
		return 2;
	}



	// btnDijkstra
	if (boton[2].getGlobalBounds().intersects(hitboxMouse)) {
		boton[2].setOutlineColor(Color::Yellow);
		return 3;
	}
	// warkshall
	if (boton[3].getGlobalBounds().intersects(hitboxMouse)) {
		boton[3].setOutlineColor(Color::Yellow);
		return 4;
	}
	// Prim
	if (boton[4].getGlobalBounds().intersects(hitboxMouse)) {
		boton[4].setOutlineColor(Color::Yellow);
		return 5;
	}
	// Kruskal:
	if (boton[5].getGlobalBounds().intersects(hitboxMouse)) {
		boton[5].setOutlineColor(Color::Yellow);
		return 6;
	}
	if (boton[6].getGlobalBounds().intersects(hitboxMouse)) {
		boton[6].setOutlineColor(Color::Yellow);
		return 7;
	}
	if (boton[7].getGlobalBounds().intersects(hitboxMouse)) {
		return 8;
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
		if (!seleccionarDijkstra) {
			ruta_principal += '-';
		}
		if (seleccionarDijkstra) {
			act->setFillColor(Color::Yellow);
		}
		act = act->getEtiqueta()->from;
	}
	ruta_principal += act->getId();
	for (int j = ruta_principal.length() - 1; j >= 0; j--)
	{
		ss += ruta_principal[j];
	}

	ruta_principal = ss;

	if (seleccionarDijkstra) {
		strResultados = "Rutas cortas: ";
	}
	else {
		strResultados = respuestaDijkstra() + ruta_principal;
	}
	for (int i = 0; i < rutas_cortas->getSize(); i++) {
		cout << rutas_cortas->get(i) << endl;
		if (seleccionarDijkstra) {
			strResultados += rutas_cortas->get(i) + " || ";
		}
	}
	if (!seleccionarDijkstra) {

	}
	cout << "=========" << endl;
	cout << ruta_principal << endl;

	resultados.setString(strResultados);
}



void Grafos::Warshall(Vertice* from, Vertice* to) 
{
	int llenar= 0;
	ArrayList<Arista*>* auxArista = new ArrayList<Arista*>();
	ArrayList<Vertice*>* auxlist = new ArrayList<Vertice*>();
	matriz = new int* [n];
	lista_aristas->clear();
	for (int i = 0; i < n; i++) {
		matriz[i] = new int[i];
	}
	for (int i = 0; i < lista_vertices->getSize(); i++) {
		if (matriz[i][i] < 0) {
			matriz[i][i] = INF;
			llenar = matriz[i][i];
		}
	}
	for (int i = 0; i < lista_vertices->getSize(); i++) {
		for (int j = 0; j < lista_vertices->getSize(); j++) {
			if (lista_vertices->get(i)->getAristas()->getSize() != 0) {
				matriz[i][j] = lista_vertices->get(i)->getAristas()->get(j)->getPeso();
			}
		}
	}
	for (int i = 0; i < lista_vertices->getSize(); i++) {
		for (int j = 0; j < lista_vertices->getSize(); j++) {
			for (int k = 0; k < lista_vertices->getSize(); k++) {

				if (matriz[i][j] > (matriz[i][k] + matriz[k][j]) && (matriz[k][j] != INF && matriz[i][k] != INF)) {
					matriz[i][j] = matriz[i][k] + matriz[k][j];
				}

			}
		}
	}
	for (int i = 0; i < lista_vertices->getSize(); i++) {
		for (int j = 0; j < lista_vertices->getSize(); j++) {
			if (matriz[i][j] != INF && i != j) {
				auxArista->set(lista_vertices->get(i)->getAristas()->get(j));
				auxlist->set(auxArista->get(i)->getFrom());
			}
		}
	}
	strResultados = "Si existe camino -> ";
	for (int i = 0; i < auxArista->getSize(); i++) {
		strResultados += auxArista->get(i)->getFrom()->getId() + "-";
	}
	resultados.setString(strResultados);
}


void Grafos::Prim()
{
	static Vertice* start_node;
	static priority_queue<pair<int, Vertice*>> ordered_list;
	static pair<int, Vertice*> current;
	static ArrayList<Arista*>* prim_result;
	prim_result = result;
	static int sum;
	sum = 0;
	start_node= lista_vertices->get(0);
	ordered_list = priority_queue<pair<int, Vertice*>>();
	ordered_list.push({ 0, start_node });
	while (!ordered_list.empty())
	{
		current = ordered_list.top();
		ordered_list.pop();
		if (current.second->isVisitado()) continue;
		cout << "{ " << (current.first) * -1 << " | " << current.second->getId() << " }" << endl;
		strResultados += to_string(current.first) + " | " + current.second->getId() + " || ";

		current.second->setVisitado(true);
		sum -= current.first;
		current.second->getAristas()->foreach([](Arista* element) -> void
		{
			ordered_list.push({ (element->getPeso()) * -1, element->getTo() });
		});
	}
	strResultados += "Coste Minimo: " + to_string(sum);
	resultados.setString(strResultados);
}



void Grafos::Kruskal() {
	ArrayList<Arista*>* AuxList = new ArrayList<Arista*>();
	ArrayList<Vertice*>* A = new ArrayList<Vertice*>();
	ArrayList<Vertice*>* B = new ArrayList<Vertice*>();
	
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
	for (int i = 1; i < lista_vertices->getSize(); i++) {
		B->set(lista_vertices->get(i));
		lista_vertices->get(i)->setGrupo('B');
	}

	while (true) {

		AuxList->clear();
		for (int i = 0; i < lista_aristas->getSize(); i++) {
			obtArista = lista_aristas->get(i);
			if (obtArista->isBorrado()) continue;
			if (obtArista->isVisitado()) continue;
			if (obtArista->getFrom()->getGrupo() == 'A' && obtArista->getTo()->getGrupo() == 'B') {
				AuxList->set(obtArista);
			}
		}
		if (AuxList->isEmpty()) break;
		baja = nullptr;
		for (int i = 0; i < AuxList->getSize(); i++) {
			if (baja == nullptr) {
				baja = AuxList->get(i);
			}

			if (AuxList->get(i)->getPeso() <= baja->getPeso()) {
				baja = AuxList->get(i);
			}
		}
		baja->getFrom()->setVisitado(true);
		baja->getFrom()->setGrupo('A');
		baja->getTo()->setGrupo('A');
		baja->setVistado(true);
		for (int i = 0; i < baja->getTo()->getAristas()->getSize(); i++)
		{
			if (baja->getTo()->getAristas()->get(i)->Equals(baja))
			{
				baja->getTo()->getAristas()->get(i)->setVistado(true);
				break;
			}
		}
		for (int i = 0; i < baja->getFrom()->getAristas()->getSize(); i++)
		{
			if (baja->getFrom()->getAristas()->get(i)->getTo()->getGrupo() == 'A' && !baja->getFrom()->getAristas()->get(i)->isVisitado())
			{
				baja->getFrom()->getAristas()->get(i)->setBorrado(true);
				for (int h = 0; h < baja->getFrom()->getAristas()->get(i)->getTo()->getAristas()->getSize(); h++)
				{
					if (baja->getFrom()->getAristas()->get(i)->Equals(baja->getFrom()->getAristas()->get(i)->getTo()->getAristas()->get(h)))
					{
						baja->getFrom()->getAristas()->get(i)->getTo()->getAristas()->get(h)->setBorrado(true);
						break;
					}
				}
			}
			for (int j = 0; j < baja->getFrom()->getAristas()->get(i)->getTo()->getAristas()->getSize(); j++)
			{
				Vertice* aux = baja->getFrom()->getAristas()->get(i)->getTo();
				if (aux->getAristas()->get(j)->getTo()->getGrupo() == 'A' && !aux->getAristas()->get(j)->isVisitado() && aux->getAristas()->get(j)->getTo()!=baja->getFrom())
				{
					aux->getAristas()->get(j)->setBorrado(true);
					for (int u = 0; u < aux->getAristas()->get(j)->getTo()->getAristas()->getSize(); u++)
					{
						if (aux->getAristas()->get(j)->getTo()->getAristas()->get(u)->Equals(aux->getAristas()->get(j)))
						{
							aux->getAristas()->get(j)->getTo()->getAristas()->get(u)->setBorrado(true);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < lista_vertices->getSize(); i++) {
		for (int j = 0; j < lista_vertices->get(i)->getAristas()->getSize(); j++) {
			if (lista_vertices->get(i)->getAristas()->get(j)->isBorrado()) continue;
			result->set(lista_vertices->get(i)->getAristas()->get(j));
			break;
		}
	}
	for (int i = 0; i < result->getSize(); i++) {
		cout << result->get(i)->getFrom()->getId() << " - " << result->get(i)->getTo()->getId() << endl;
	}
}