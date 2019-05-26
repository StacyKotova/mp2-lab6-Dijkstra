enum RBColor { Red = 0, Black = 1 };

template <typename T>
struct RBNode
{
    T data;
	RBColor color;
	RBNode<T> *left, *right, *parent;
	
	RBNode(const T& d, RBNode<T>* p): data(d), color(Red), parent(p),
		left(0), right(0) {}
 
    ~RBNode()
	{
        delete left;
        delete right;
    }
};