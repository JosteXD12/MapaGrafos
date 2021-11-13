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
};


class Vertice : public RectangleShape
{
private:
	string id;
	bool visitado;
	ArrayList<Arista*>* aristas;
};


