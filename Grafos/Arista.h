#pragma once

class Arista;
class Vertice;

class Arista
{
private:

	float ini_x;
	float ini_y;
	float end_x;
	float end_y;
	int peso;
	Vertice* from;
	Vertice* to;
	bool visitado;
	bool borrado;
public:
	Arista(float ini_x, float ini_y, float end_x, float end_y, int peso, Vertice* from, Vertice* to);

	float getIni_x();
	float getIni_y();
	float getEnd_x();
	float getEnd_y();
	int getPeso();
	Vertice* getFrom();
	Vertice* getTo();
	void setFrom(Vertice* from);
	void setTo(Vertice* to);

	void setIni_x(float ini_x);
	void setIni_y(float ini_y);
	void setEnd_x(float end_x);
	void setEnd_y(float end_y);
	void setPeso(int peso);
	void setVistado(bool visitado);
	bool isVisitado();
	bool isBorrado();
	void setBorrado(bool borrado);
};

struct Etiqueta
{
	int dist;
	Vertice* from;
	int iter;
};
class Vertice : public RectangleShape
{
private:
	char id;
	bool visitado;
	ArrayList<Arista*>* aristas;
	Etiqueta* etiqueta;
	char grupo;
public:
	Vertice(float xpos, float ypos, float width, float height, char id);
	char getId();
	bool isVisitado();
	void setVisitado(bool visit);
	ArrayList<Arista*>* getAristas();
	void setEtiqueta(Etiqueta* etiqueta);
	Etiqueta* getEtiqueta();
	char getGrupo();
	void setGrupo(char grupo);
};

