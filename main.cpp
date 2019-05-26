#include "Graph.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	while (true)
	{
		int type;
		std::cout << "Введите команду: 1 - ручной ввод рёбер, 2 - случайная генерация, 0 - выход: ";
		std::cin >> type;
		Graph<int> g;
		if (type == 1)
		{
			while (true)
			{
				int begin, end;
				double weight;
				std::cout << "Введите номер начальной вершины, номер конечной вершины и вес ребра: ";
				std::cin >> begin >> end >> weight;
				g.addEdge(begin, end, weight);
				std::cout << "Продолжить ввод: 1 - да, 0 - нет: ";
				int exit;
				std::cin >> exit;
				if (!exit)
					break;
			}
		}
		else if (type == 2)
			g = Graph<int>::createRandomGraph();
		else
			break;

		g.print();

		if (g.isComponent())
		{
			std::cout << "Выберите тип структуры данных: 1 - AVL-дерево, 2 - красно-черное дерево, 3 - d-куча: ";
			int dsType;
			std::cin >> dsType;

			int start;
			while (true)
			{
				std::cout << "Выберите номер вершины: ";
				std::cin >> start;
				if (g.isVertex(start))
					break;
				else
					std::cout << "Такой вершины не существует, повторите ввод!\n";
			}

			if (dsType == 1)
				g.dijkstra<AVLTree>(start);
			else if (dsType == 2)
				g.dijkstra<RBTree>(start);
			else if (dsType == 3)
			{
				int D;
				std::cout << "Выберите значение D: ";
				std::cin >> D;
				g.dijkstra<DHeap>(start, D);
			}
		}
		else
			std::cout << "Граф не связный!\n";
	}

	return 0;
}