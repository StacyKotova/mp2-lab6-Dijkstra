// Очередь с приоритетом
template <typename T, template <typename> class Tree> 
class PriorityQueue
{
	Tree<T> tree; // Дерево
public:
	// Конструктор
	PriorityQueue(int D = 2)
	{
		tree = Tree<T>(D);
	}

	// Проверка на пустоту
	bool isEmpty()
	{
		return tree.isEmpty();
	}

	// Вставка
	void insert(const T& value)
	{
		tree.insert(value);
	}
	
	// Извлечение минимума
	T extractMin()
	{
		T min = tree.min();
		tree.remove(min);
		return min;
	}
};