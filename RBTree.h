#include "RBNode.h"

template <typename T>
class RBTree
{
    RBNode<T>* root;
	
	void rotateLeft(RBNode<T>* n) 
	{
		RBNode<T> *child = n->right;

		n->right = child->left;
		if (child->left)
			child->left->parent = n;

		if (child)
			child->parent = n->parent;
		
		if (n->parent) 
		{
			if (n == n->parent->left)
				n->parent->left = child;
			else
				n->parent->right = child;
		} 
		else
			root = child;

		child->left = n;
		if (n)
			n->parent = child;
	}
	
	void rotateRight(RBNode<T>* n)
	{
		RBNode<T>* child = n->left;

		n->left = child->right;
		if (child->right)
			child->right->parent = n;
		
		if (child)
			child->parent = n->parent;
		
		if (n->parent)
		{
			if (n == n->parent->right)
				n->parent->right = child;
			else
				n->parent->left = child;
		} 
		else
			root = child;

		child->right = n;
		if (n) 
			n->parent = child;
	}
	
	void _insert(RBNode<T>* n)
	{
		while (n != root && n->parent->color == Red)
		{
			if (n->parent == n->parent->parent->left)
			{
				RBNode<T>* child = n->parent->parent->right;
				if (child && child->color == Red)
				{
					n->parent->color = Black;
					child->color = Black;
					n->parent->parent->color = Red;
					n = n->parent->parent;
				}
				else
				{
					if (n == n->parent->right)
					{
						n = n->parent;
						rotateLeft(n);
					}
					n->parent->color = Black;
					n->parent->parent->color = Red;
					rotateRight(n->parent->parent);
				}
			} 
			else
			{
				RBNode<T>* child = n->parent->parent->left;
				if (child && child->color == Red)
				{
					n->parent->color = Black;
					child->color = Black;
					n->parent->parent->color = Red;
					n = n->parent->parent;
				} 
				else
				{
					if (n == n->parent->left)
					{
						n = n->parent;
						rotateRight(n);
					}
					n->parent->color = Black;
					n->parent->parent->color = Red;
					rotateLeft(n->parent->parent);
				}
			}
		}
		if (root)
			root->color = Black;
	}
	
	void remove(RBNode<T> *n)
	{
		RBNode<T> *a, *b;
		
		if (!n)
			return;
		
		if (!n->left || !n->right)
			b = n;
		else 
		{
			b = n->right;
			while (b->left)
				b = b->left;
		}
		
		if (b->left)
			a = b->left;
		else
			a = b->right;
		
		if (a)
			a->parent = b->parent;
		if (b->parent)
			if (b == b->parent->left)
				b->parent->left = a;
			else
				b->parent->right = a;
		else
			root = a;

		if (b != n)
			n->data = b->data;
		
		if (a && b->color == Black)
			_remove(a);
	}
	
	void _remove(RBNode<T>* child)
	{
		while (child != root && child->color == Black)
		{
			if (child == child->parent->left)
			{
				RBNode<T>* s = child->parent->right;
				if (s->color == Red)
				{
					s->color = Black;
					child->parent->color = Red;
					rotateLeft (child->parent);
					s = child->parent->right;
				}
				
				if (s->left->color == Black && s->right->color == Black)
				{
					s->color = Red;
					child = child->parent;
				} 
				else
				{
					if (s->right->color == Black)
					{
						s->left->color = Black;
						s->color = Red;
						rotateRight (s);
						s = child->parent->right;
					}
					s->color = child->parent->color;
					child->parent->color = Black;
					s->right->color = Black;
					rotateLeft (child->parent);
					child = root;
				}
			} 
			else
			{
				RBNode<T>*s = child->parent->left;
				if (s->color == Red)
				{
					s->color = Black;
					child->parent->color = Red;
					rotateRight (child->parent);
					s = child->parent->left;
				}
				if (s->right->color == Black && s->left->color == Black)
				{
					s->color = Red;
					child = child->parent;
				}
				else
				{
					if (s->left->color == Black)
					{
						s->right->color = Black;
						s->color = Red;
						rotateLeft (s);
						s = child->parent->left;
					}
					s->color = child->parent->color;
					child->parent->color = Black;
					s->left->color = Black;
					rotateRight (child->parent);
					child = root;
				}
			}
		}
		child->color = Black;
	}
	
	T& min(RBNode<T> *n)
	{
		if (n->left)
			return min(n->left);
		else
			return n->data;
	}

	
public:
    RBTree(int D = 0)
    {
		root = 0;
    }

	bool isEmpty()
	{
		return root == 0;
	}
	
	void insert(const T& value)
	{
		RBNode<T> *cur = root, *parent = 0;
		while (cur)
		{
			if (value == cur->data)
				return;
			parent = cur;
			cur = (value < cur->data) ? cur->left : cur->right;
		}

		RBNode<T> *child = new RBNode<T>(value, parent);

		if (parent)
		{
			if (value < parent->data)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			root = child;

		_insert(child);
	}
	
	RBNode<T>* find(const T& value)
	{
		RBNode<T>* cur = root;
		while (cur)
		{
			if (value == cur->data)
				return cur;
			else
				cur = (value < cur->data) ? cur->left : cur->right;
		}
		return 0;
	}
	
	void remove(const T& value)
	{
		RBNode<T> *n = root;
		while (n->data != value)
		{
			if (n->data > value)
				n = n->left;
			else
				n = n->right;
		}
		remove(n);
	}
	
	T& min()
	{
		return min(root);
	}
};