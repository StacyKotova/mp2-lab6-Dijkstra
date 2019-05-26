#ifndef AVLNODE_H
#define AVLNODE_H

// ����� ���� ���-������
template <typename T>
struct AVLNode 
{
	T data; // ������ ����
    int balance; // ������
	AVLNode<T> *left, *right, *parent; // �����, ������, ��������
	
	// �����������
    AVLNode(const T& d, AVLNode<T>* p): data(d), balance(0), parent(p),
		left(0), right(0) {}
 
	// ����������
    ~AVLNode()
	{
        delete left;
        delete right;
    }
};

#endif /* AVLNODE_H */