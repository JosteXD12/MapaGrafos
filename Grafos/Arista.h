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
	Vertice* vertice;
public:
	Arista(float ini_x, float ini_y, float end_x, float end_y, int peso, Vertice* vertice);

	float getIni_x();
	float getIni_y();
	float getEnd_x();
	float getEnd_y();
	int getPeso();
	Vertice* getVertice();

	void setIni_x(float ini_x);
	void setIni_y(float ini_y);
	void setEnd_x(float end_x);
	void setEnd_y(float end_y);
	void setPeso(int peso);
	void setVertice(Vertice* vertice);
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
	int id;
	bool visitado;
	ArrayList<Arista*>* aristas;
	Etiqueta* etiqueta;
public:
	Vertice(float xpos, float ypos, float width, float height, int id);
	int getId();
	bool isVisitado();
	void setVisitado(bool visit);
	ArrayList<Arista*>* getAristas();
	void setEtiqueta(Etiqueta* etiqueta);
	Etiqueta* getEtiqueta();
};

