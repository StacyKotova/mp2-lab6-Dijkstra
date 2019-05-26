#include "Graph.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	while (true)
	{
		int type;
		std::cout << "������� �������: 1 - ������ ���� ����, 2 - ��������� ���������, 0 - �����: ";
		std::cin >> type;
		Graph<int> g;
		if (type == 1)
		{
			while (true)
			{
				int begin, end;
				double weight;
				std::cout << "������� ����� ��������� �������, ����� �������� ������� � ��� �����: ";
				std::cin >> begin >> end >> weight;
				g.addEdge(begin, end, weight);
				std::cout << "���������� ����: 1 - ��, 0 - ���: ";
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
			std::cout << "�������� ��� ��������� ������: 1 - AVL-������, 2 - ������-������ ������, 3 - d-����: ";
			int dsType;
			std::cin >> dsType;

			int start;
			while (true)
			{
				std::cout << "�������� ����� �������: ";
				std::cin >> start;
				if (g.isVertex(start))
					break;
				else
					std::cout << "����� ������� �� ����������, ��������� ����!\n";
			}

			if (dsType == 1)
				g.dijkstra<AVLTree>(start);
			else if (dsType == 2)
				g.dijkstra<RBTree>(start);
			else if (dsType == 3)
			{
				int D;
				std::cout << "�������� �������� D: ";
				std::cin >> D;
				g.dijkstra<DHeap>(start, D);
			}
		}
		else
			std::cout << "���� �� �������!\n";
	}

	return 0;
}