// ������� � �����������
template <typename T, template <typename> class Tree> 
class PriorityQueue
{
	Tree<T> tree; // ������
public:
	// �����������
	PriorityQueue(int D = 2)
	{
		tree = Tree<T>(D);
	}

	// �������� �� �������
	bool isEmpty()
	{
		return tree.isEmpty();
	}

	// �������
	void insert(const T& value)
	{
		tree.insert(value);
	}
	
	// ���������� ��������
	T extractMin()
	{
		T min = tree.min();
		tree.remove(min);
		return min;
	}
};