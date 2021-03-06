#include "main.h"
#include "Arista.h"

Vertice::Vertice(float xpos, float ypos, float width, float height, char id) : RectangleShape()
{
	this->setSize(Vector2f(width, height));
	this->setPosition(xpos, ypos);
	this->aristas = new ArrayList<Arista*>();
	this->visitado = false;
	this->id = id;
}

char Vertice::getId()
{
	return id;
}

bool Vertice::isVisitado()
{
	return visitado;
}

void Vertice::setVisitado(bool visit)
{
	this->visitado = visit;
}

ArrayList<Arista*>* Vertice::getAristas()
{
	return aristas;
}

void Vertice::setEtiqueta(Etiqueta* etiqueta)
{
	this->etiqueta = etiqueta;
}

Etiqueta* Vertice::getEtiqueta()
{
	return etiqueta;
}

char Vertice::getGrupo()
{
	return grupo;
}

void Vertice::setGrupo(char grupo)
{
	this->grupo = grupo;
}

string Vertice::toString()
{
	int a = (int) this->getPosition().x;
	int b = (int) this->getPosition().y;
	stringstream ssa;
	stringstream ssb;
	ssa << a;
	string str_a = ssa.str();
	ssb << b;
	string str_b = ssb.str();
	string ssr = "";
	ssr += id;
	ssr += "|" + str_a + "|" + str_b + "|";
	return ssr;
}


Arista::Arista(float ini_x, float ini_y, float end_x, float end_y, int peso, Vertice* from, Vertice* to)
{
	this->ini_x = ini_x;
	this->ini_y = ini_y;
	this->end_x = end_x;
	this->end_y = end_y;
	this->peso = peso;
	this->from = from;
	this->to = to;
	borrado = false;
	visitado = false;
}

float Arista::getIni_x()
{
	return ini_x;
}

float Arista::getIni_y()
{
	return ini_y;
}

float Arista::getEnd_x()
{
	return end_x;
}

float Arista::getEnd_y()
{
	return end_y;
}

int Arista::getPeso()
{
	return peso;
}

Vertice* Arista::getFrom()
{
	return from;
}

Vertice* Arista::getTo()
{
	return to;
}

void Arista::setFrom(Vertice* from)
{
	this->from = from;
}

void Arista::setTo(Vertice* to)
{
	this->to = to;
}

bool Arista::Equals(Arista* this_arista)
{
	return (this->from == this->getTo() && this->to == this->getFrom());
}

void Arista::setIni_x(float ini_x)
{
	this->ini_x = ini_x;
}

void Arista::setIni_y(float ini_y)
{
	this->ini_y = ini_y;
}

void Arista::setEnd_x(float end_x)
{
	this->end_x = end_x;
}

void Arista::setEnd_y(float end_y)
{
	this->end_y = end_y;
}

void Arista::setPeso(int peso)
{
	this->peso = peso;
}

void Arista::setVistado(bool visitado)
{
	this->visitado = visitado;
}

bool Arista::isVisitado()
{
	return visitado;
}

bool Arista::isBorrado()
{
	return borrado;
}

string Arista::toString()
{
	stringstream sss;
	sss << peso;
	string str_a = sss.str();
	string ss = "";
	ss += from->getId();
	ss += "-";
	ss += to->getId();
	return ss + "|" + str_a + "|";
}

void Arista::setBorrado(bool borrado)
{
	this->borrado = borrado;
}
