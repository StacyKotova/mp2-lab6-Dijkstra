#ifndef EDGE_H
#define EDGE_H

// ��������� "����� �����"
struct Edge
{
	int begin; // ������ ������ 
	int end; // ������ ������ 
	double weight; // ���

	// �����������
	Edge(int begin, int end, double weight)
	{
		this->begin = begin;
		this->end = end;
		this->weight = weight;
	}
};

#endif /* EDGE_H */ 