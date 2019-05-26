#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <algorithm>
#include <iostream>

template <typename T>
class AVLTree
{
	AVLNode<T>* root; // Корень
	
	// Левое движение
	AVLNode<T>* rotateLeft(AVLNode<T>* a)
	{
		AVLNode<T> *b = a->right;
		b->parent = a->parent;
		a->right = b->left;
	 
		if (a->right != 0)
			a->right->parent = a;
	 
		b->left = a;
		a->parent = b;
	 
		if (b->parent != 0)
		{
			if (b->parent->right == a)
				b->parent->right = b;
			else
				b->parent->left = b;
		}
	 
		setBalance(a);
		setBalance(b);
		return b;
	}
	
	// Правое движение
	AVLNode<T>* rotateRight(AVLNode<T> *a)
	{
		AVLNode<T> *b = a->left;
		b->parent = a->parent;
		a->left = b->right;
	 
		if (a->left != 0)
			a->left->parent = a;
	 
		b->right = a;
		a->parent = b;
	 
		if (b->parent != 0)
		{
			if (b->parent->right == a)
				b->parent->right = b;
			else
				b->parent->left = b;
		}
	 
		setBalance(a);
		setBalance(b);
		return b;
	}
 
	// Левое, затем правое движение
	AVLNode<T>* rotateLeftRight(AVLNode<T> *n)
	{
		n->left = rotateLeft(n->left);
		return rotateRight(n);
	}
 
	// Левое, затем левое движение
	AVLNode<T>* rotateRightLeft(AVLNode<T> *n)
	{
		n->right = rotateRight(n->right);
		return rotateLeft(n);
	}
	
	// Изменение баланса во всем дереве
	void rebalance(AVLNode<T> *n)
	{
		setBalance(n);
	 
		if (n->balance == -2)
		{
			if (height(n->left->left) >= height(n->left->right))
				n = rotateRight(n);
			else
				n = rotateLeftRight(n);
		}
		else if (n->balance == 2)
		{
			if (height(n->right->right) >= height(n->right->left))
				n = rotateLeft(n);
			else
				n = rotateRightLeft(n);
		}
	 
		if (n->parent != 0)
			rebalance(n->parent);
		else
			root = n;
	}
	
	// Высота дерева
	int height(AVLNode<T> *n)
	{
		if (n == 0)
			return -1;
		return 1 + std::max(height(n->left), height(n->right));
	}
	
	// Изменение баланса в узле
	void setBalance(AVLNode<T> *n)
	{
		n->balance = height(n->right) - height(n->left);
	}
	
	// Минимум в дереве, начиная с узла n
	T& min(AVLNode<T> *n)
	{
		if (n->left)
			return min(n->left);
		else
			return n->data;
	}
	
	// Печать дерева, начиная с узла n
	void print(AVLNode<T> *n)
	{
		if (n->left)
			print(n->left);
		std::cout << n->data << std::endl;
		if (n->right)
			print(n->right);
	}
	
public:
	// Конструктор
    AVLTree(int D = 0)
	{
		root = 0;
	}
	
	// Деструктор
    ~AVLTree()
	{
		delete root;
	}

	// Проверка на пустоту
	bool isEmpty()
	{
		return root == 0;
	}
	
	// Добавление значения value в дереве
    bool insert(const T& value)
	{
		if (root == 0)
			root = new AVLNode<T>(value, 0);
		else 
		{
			AVLNode<T> *n = root, *parent;
 
			while (true)
			{
				if (n->data == value)
					return false;
 
				parent = n;
 
				bool isLeft = n->data > value;
				n = isLeft ? n->left : n->right;
 
				if (n == 0)
				{
					if (isLeft)
						parent->left = new AVLNode<T>(value, parent);
					else
						parent->right = new AVLNode<T>(value, parent);
 
					rebalance(parent);
					break;
				}
            }
        }
 
		return true;
	}

	// Удаление значения value из дерева
    void remove(const T& value)
	{		
		if (root == 0)
			return;
 
		AVLNode<T> *n, *parent, *remNode, *child;
		n = parent = child = root;
		remNode = 0;
 
		while (child != 0)
		{
			parent = n;
			n = child;
			child = value >= n->data ? n->right : n->left;
			if (value == n->data)
				remNode = n;
		}
 
		if (remNode != 0)
		{
			remNode->data = n->data;
 
			child = n->left != 0 ? n->left : n->right;
 
			if (root->data == value)
				root = child;
			else 
			{
				if (parent->left == n)
					parent->left = child;
				else
					parent->right = child;
 
				rebalance(parent);
			}
        }
    }

	// Минимум в дереве
	T& min()
	{
		return min(root);
	}
	
	// Печать на экран дерева
	void print()
	{
		print(root);
	}
};

#endif /* AVLTRRE_H */