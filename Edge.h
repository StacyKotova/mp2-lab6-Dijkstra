#ifndef EDGE_H
#define EDGE_H

// Структура "ребро графа"
struct Edge
{
	int begin; // Номера вершин 
	int end; // Номера вершин 
	double weight; // Вес

	// Конструктор
	Edge(int begin, int end, double weight)
	{
		this->begin = begin;
		this->end = end;
		this->weight = weight;
	}
};

#endif /* EDGE_H */ 