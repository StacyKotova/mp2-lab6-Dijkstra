#include "Edge.h"
#include "AVLTree.h"
#include "DHeap.h"
#include "RBTree.h"
#include "PriorityQueue.h"
#include <limits>
#include <map>
#include <random>
#include <set>
#include <vector>

// Вспомогательная структура
struct Dist
{
	int vertex; // Номер вершины
	double dist; // Расстояние

	// Конструктор
	Dist(int vertex, double dist)
	{
		this->vertex = vertex;
		this->dist = dist;
	}

	/*
		Перегрузка операторов сравнения
	*/

	friend bool operator<(const Dist& x, const Dist& y)
	{
		return x.dist < y.dist;
	}

	friend bool operator>(const Dist& x, const Dist& y)
	{
		return x.dist > y.dist;
	}

	friend bool operator>=(const Dist& x, const Dist& y)
	{
		return x.dist >= y.dist;
	}

	friend bool operator==(const Dist& x, const Dist& y)
	{
		return x.dist == y.dist;
	}

	friend bool operator!=(const Dist& x, const Dist& y)
	{
		return x.dist != y.dist;
	}
	
	friend bool operator<=(const Dist& x, const Dist& y)
	{
		return x.dist <= y.dist;
	}
};

// Класс "граф"
template<typename T>
class Graph
{
	std::vector<Edge*> edges; // Рёбра
 	std::set<int> vertices; // Вершины

public:
	// Конструктор по умолчанию
	Graph(){}

	// Конструктор c параметрами
	Graph(std::vector<Edge*>& edges, std::set<int>& vertices)
	{
		this->edges = edges;
		this->vertices = vertices;
	}

	// Случайная генерация
	static Graph createRandomGraph()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis1(2, 20);
		int count = dis1(gen);
		std::vector<Edge*> _edges;
		std::set<int> _vertices;
		
		// Добавление рёбер и вершин
		for (int i = 0; i < count; i++)
		{
			_vertices.insert(i);
			std::uniform_int_distribution<> dis2(0, 1);
			std::uniform_int_distribution<> dis3(1, 20);
			for (int j = i + 1; j < count; j++)
				if (dis2(gen) == 1)
					_edges.push_back(new Edge(i, j, dis3(gen)));
		}
		return Graph(_edges, _vertices);
	}

	// Проверка на существование вершины в граф
	bool isVertex(int vertex)
	{
		return vertices.find(vertex) != vertices.end();
	}

	// Печать графа на экран
	void print()
	{
		std::cout << "Печать графа на экран:" << std::endl;
		for (Edge* e : edges)
			std::cout << "Ребро: (" << e->begin << ";" << e->end << ") Вес: " << e->weight << std::endl;
	}

	// Добавление ребра
	void addEdge(int begin, int end, double weight)
	{
		edges.push_back(new Edge(begin, end, weight));
		vertices.insert(begin);
		vertices.insert(end);
	}

	// Проверка на связность
	bool isComponent()
	{
		int start = *vertices.begin();
		std::map<int, bool> visited;
		for (int v : vertices)
			visited[v] = false;
		visited[start] = true;

		PriorityQueue<int, AVLTree> q;
		q.insert(start);

		while (!q.isEmpty())
		{
			start = q.extractMin();
			for (Edge* e : edges)
			{
				if (e->begin == start || e->end == start)
				{
					int n = e->begin == start ? e->end : e->begin;
					if (!visited[n])
					{
						visited[n] = true;
						q.insert(n);
					}
				}
			}
		}

		for (auto b : visited)
			if (!b.second)
				return b.second;
		return true;
	}
	
	// Алгоритм Дейкстры
	template<template <typename> class Tree>
	void dijkstra(int start, int D = 2)
	{
		std::map<int, double> dist;
		for (int v : vertices)
			dist[v] = std::numeric_limits<double>::max();
		dist[start] = 0;

		PriorityQueue<Dist, Tree> pq(D);
		pq.insert(Dist(start, 0));
		
		std::set<int> visited;

		while (!pq.isEmpty())
		{
			Dist a = pq.extractMin();
			for (Edge* e : edges)
				if (e->begin == a.vertex || e->end == a.vertex)
				{
					int n = e->begin == a.vertex ? e->end : e->begin;
					if (dist[n] > e->weight + dist[a.vertex])
					{
						dist[n] = e->weight + dist[a.vertex];
						pq.insert(Dist(n, dist[n]));
					}
				}
		}
		for (std::pair<int, double> d : dist)
			std::cout << "Вершина: " << d.first << " Расстояние: " << d.second << std::endl;
	}
};