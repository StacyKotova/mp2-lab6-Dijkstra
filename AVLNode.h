#ifndef AVLNODE_H
#define AVLNODE_H

// Класс узла АВЛ-дерева
template <typename T>
struct AVLNode 
{
	T data; // Данные узла
    int balance; // Баланс
	AVLNode<T> *left, *right, *parent; // Левый, правый, родитель
	
	// Конструктор
    AVLNode(const T& d, AVLNode<T>* p): data(d), balance(0), parent(p),
		left(0), right(0) {}
 
	// Деструктор
    ~AVLNode()
	{
        delete left;
        delete right;
    }
};

#endif /* AVLNODE_H */