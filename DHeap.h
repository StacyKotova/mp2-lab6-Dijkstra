#ifndef DHEAP_H
#define DHEAP_H

#include <vector>

// D-куча
template<typename T>
class DHeap
{
	int D;
	std::vector<T> data;
	
public:
	// Конструктор
	DHeap(int D = 2, int size = 0)
	{
		this->D = D;
		this->data = std::vector<T>();
	}
	
	DHeap(std::vector<T>& data, int D)
	{
		this->D = D;
		this->data = data;
	}
	
	// Проверка на пустоту
	bool isEmpty()
    {
		return data.size() == 0;
    }
	
	// Ребенок
	size_t child(int i, int k)
    {
        return D * i + k;
    }
	
	// Родитель
	int parent(int index)
    {
        return (index - 1) / D;
    }
	
	// Вставка
	void insert(const T& value)
    {
		data.push_back(value);
        up(data.size() - 1);
    }
	
	// Минимум
	T min()
    {
		return data[0];
    }

	// Удаление
	T remove(T value)
	{
		return _remove(std::find(data.begin(), data.end(), value) - data.begin());
	}
	
	// Удаление
	T _remove(int index)
	{
		T value = data[index];
		data[index] = data[data.size() - 1];
		down(index);
		data.pop_back();
		return value;
	}
	
	void down(int index)
	{
		int c;
		T tmp = data[index];
		while (child(index, 1) < data.size())
		{
			c = minChild(index);
			if (data[c] < tmp)
                data[index] = data[c];
            else
                break;
			index = c;
		}
        data[index] = tmp;
	}
	
	void up(int index)
	{
		T tmp = data[index];
		while (index > 0 && tmp < data[parent(index)])
		{
			data[index] = data[parent(index)];
			index = parent(index);
		}
		data[index] = tmp;
	}
	
	int minChild(int index)
	{
		size_t best = child(index, 1);
		int k = 2;
		size_t cand = child(index, k);
		while ((k <= D) && (cand < data.size()))
		{
			if (data[cand] < data[best])
				best = cand;
			k++;
			cand = child(index, k);
		}
		return best;
	}
};

#endif /* DHEAP_H */ 