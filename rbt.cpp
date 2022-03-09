#include <cstddef>
#include <iostream>

struct	Node
{
	int		data;
	Node	*left;
	Node	*right;
	Node	*parent;
	bool	isBlack;
};

typedef Node*	nodePtr;

class RBTree
{
private:
	nodePtr	root;
	nodePtr	nil;

	void	initNewNode(nodePtr Node, int key)
	{
		Node->data = key;
		Node->isBlack = false;
		Node->left = nil;
		Node->right = nil;
		Node->parent = nil;
	}

/**
 * INSERT
 */
	void	insertNode(nodePtr Node)
	{
		nodePtr	y = this->nil;
		nodePtr	x = this->root;
		while (x != this->nil)
		{
			y = x;
			if (Node->data < x->data)
				x = x->left;
			else
				x = x->right;
		}

		Node->parent = y;
		if (y == this->nil)
			this->root = Node;
		else if (Node->data < y->data)
			y->left = Node;
		else
			y->right = Node;

		insertFix(Node);
	}

/**
 * INSERT_FIXUP
 */
	void	insertFix(nodePtr Node)
	{
		while (Node->parent->isBlack == false)
		{
			if (Node->parent == Node->parent->parent->left)
			{
				nodePtr	u = Node->parent->parent->right;
				if (u->isBlack == false)
				{
					Node->parent->isBlack = true;
					u->isBlack = true;
					Node->parent->parent->isBlack = false;
					Node = Node->parent->parent;
				}
				else
				{
					if (Node == Node->parent->right)
					{
						Node = Node->parent;
						leftRotate(Node);
					}
					Node->parent->isBlack = true;
					Node->parent->parent->isBlack = false;
					rightRotate(Node->parent->parent);
				}
			}
			else
			{
				nodePtr	u = Node->parent->parent->left;
				if (u->isBlack == false)
				{
					Node->parent->isBlack = true;
					u->isBlack = true;
					Node->parent->parent->isBlack = false;
					Node = Node->parent->parent;
				}
				else
				{
					if (Node == Node->parent->left)
					{
						Node = Node->parent;
						rightRotate(Node);
					}
					Node->parent->isBlack = true;
					Node->parent->parent->isBlack = false;
					leftRotate(Node->parent->parent);
				}
			}
		}
		this->root->isBlack = true;
	}

/**
 * LEFT_ROTATE
 */
	void	leftRotate(nodePtr x)
	{
		nodePtr	y = x->right;
		x->right = y->left;
		if (y->left != nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			this->root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

/**
 * RIGHT_ROTATE
 */
	void	rightRotate(nodePtr x)
	{
		nodePtr	y = x->left;
		x->left = y->right;
		if (y->right != nil)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			this->root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

/**
 * TRANSPLANT
 */
	void	transplantNode(nodePtr u, nodePtr v)
	{
		if (u->parent == nil)
			this->root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

/**
 * TREE_MINIMUM
 */
	nodePtr	treeMin(nodePtr x)
	{
		if (x != nullptr)
		{
			while (x->left != nil)
				x = x->left;
		}
		return x;
	}

/**
 * TREE_MAXIMUM
 */
	nodePtr	treeMax(nodePtr x)
	{
		if (x != nullptr)
		{
			while (x->right != nil)
				x = x->right;
		}
		return x;
	}

/**
 * DELETE
 */
	void	deleteNode(nodePtr Node)
	{
		if (Node == nullptr)
			return ;
		nodePtr	y = Node;
		nodePtr x = nullptr;
		bool	orig_color = y->isBlack;

		if (Node->left == nil)
		{
			x = Node->right;
			transplantNode(Node, Node->right);
		}
		else if (Node->right == nil)
		{
			x = Node->left;
			transplantNode(Node, Node->left);
		}
		else
		{
			y = treeMin(Node->right);
			orig_color = y->isBlack;
			x = y->right;
			if (y->parent == Node)
				x->parent = y;
			else
			{
				transplantNode(y, y->right);
				y->right = Node->right;
				y->right->parent = y;
			}
			transplantNode(Node, y);
			y->left = Node->left;
			y->left->parent = y;
			y->isBlack = Node->isBlack;
		}
		if (orig_color == true)
			deleteFix(x);
	}

/**
 * DELETE_FIXUP
 */
	void	deleteFix(nodePtr x)
	{
		if (x == nullptr)
			return ;
		while (x != this->root && x->isBlack == true)
		{
			if (x == x->parent->left)
			{
				nodePtr	w = x->parent->right;
				if (w->isBlack == false)
				{
					w->isBlack = true;
					x->parent->isBlack = false;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->isBlack == true && w->right->isBlack == true)
				{
					w->isBlack = false;
					x = x->parent;
				}
				else
				{
					if (w->right->isBlack == true)
					{
						w->left->isBlack = true;
						w->isBlack = false;
						rightRotate(w);
						w = x->parent->right;
					}
					w->isBlack = x->parent->isBlack;
					x->parent->isBlack = true;
					w->right->isBlack = true;
					leftRotate(x->parent);
					x = this->root;
				}
			}
			else
			{
				nodePtr	w = x->parent->left;
				if (w->isBlack == false)
				{
					w->isBlack = true;
					x->parent->isBlack = false;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->isBlack == true && w->left->isBlack == true)
				{
					w->isBlack = false;
					x = x->parent;
				}
				else
				{
					if (w->left->isBlack == true)
					{
						w->right->isBlack = true;
						w->isBlack = false;
						leftRotate(w);
						w = x->parent->left;
					}
					w->isBlack = x->parent->isBlack;
					x->parent->isBlack = true;
					w->left->isBlack = true;
					rightRotate(x->parent);
					x = this->root;
				}
			}
		}
		x->isBlack = true;
	}

/**
 * SEARCH_NODE
 */
	nodePtr	searchNode(int key)
	{
		nodePtr	x = this->root;
		while (x != nil && key != x->data)
		{
			if (key < x->data)
				x = x->left;
			else
				x = x->right;
		}
		return x;
	}

/**
 * INORDER_WALK
 */
	void	inorderWalk(nodePtr x)
	{
		if (x == nullptr)
			return ;
		if (x != nil)
		{
			inorderWalk(x->left);
			inorderWalk(x->right);
		}
	}

/**
 * SUCCESSOR(послед. элемент)
 */
	nodePtr	successor(nodePtr x)
	{
		if (x == nullptr)
			return nullptr;
		if (x->right != nil)
			return treeMin(x->right);
		nodePtr	y = x->parent;
		while (y != nil && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

/**
 * PREDECESSOR(пред. элемент)
 */
	nodePtr	predecessor(nodePtr x)
	{
		if (x == nullptr)
			return nullptr;
		if (x->left != nil)
			return treeMax(x->left);
		nodePtr	y = x->parent;
		while (y != nil && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

/**
 * PRINT
 */
	void	printOut(nodePtr Node)
	{
		if (Node != nil)
		{
			std::string	color = (Node->isBlack) ? "B" : "R";
			std::cout << Node->data << "(" << color << ")" << "	|";
			printOut(Node->left);
			printOut(Node->right);
		}
	}

public:
	RBTree()
	{
		this->nil = new Node;
		nil->data = 0;
		nil->isBlack = true;
		nil->left = nullptr;
		nil->right = nullptr;
		nil->parent = nullptr;
		this->root = nil;
	}

	void	insert(int key)
	{
		nodePtr	newNode = new Node;
		initNewNode(newNode, key);
		insertNode(newNode);
		printOut(this->root);
		std::cout << std::endl;
	}

	void	deleteByKey(int key)
	{
		nodePtr	n = searchNode(key);
		if (n != nullptr && n != nil)
			deleteNode(n);
		printOut(this->root);
		std::cout << std::endl;
	}
};

int		main()
{
	RBTree rbt;
	rbt.insert(55);
	rbt.insert(40);
	rbt.insert(65);
	rbt.insert(60);
	rbt.insert(75);
	rbt.insert(57);
	rbt.deleteByKey(40);
};
