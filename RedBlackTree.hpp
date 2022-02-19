#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <memory>
#include "utilities.hpp"
#include "iterators/tIterator.hpp"


template <class V, class Compare = std::less<V>, class Allocator = std::allocator<V> > 
	class RedBlackTree
{
public:
	typedef V					value_type;
	typedef Compare				value_compare;
	typedef Allocator			allocator_type;

	typedef	ft::Node<V>											Node;
	typedef	Node*												nodePtr;
	typedef typename Allocator::template rebind<Node>::other	nodeAlloc;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t		difference_type;
	typedef std::size_t			size_type;

	typedef tIterator<value_type>						iterator;
	typedef tIterator<const value_type>					const_iterator;
	typedef tRevIterator<iterator>						reverse_iterator;
	typedef tRevIterator<const_iterator>				const_reverse_iterator;

private:
	nodePtr			root;
	// nodePtr			_begin; ???
	nodePtr			nil;
	size_type		tree_size;
	value_compare	comp;
	nodeAlloc		nodeA;

public:
/**
 * CONSTRUCTOR
 */
	// RedBlackTree() : root(nullptr), 
	// 				// _begin(nullptr), ???
	// 				nil(nullptr), 
	// 				tree_size(0), 
	// 				comp(), 
	// 				nodeA()
	// { initNilRoot(); }

	RedBlackTree(const value_compare& compare = value_compare()) : 
					root(nullptr),
					// _begin(nullptr), ???
					nil(nullptr), 
					tree_size(0), 
					comp(compare), 
					nodeA()
	{ initNilRoot(); }

	template <class InputIterator>
		RedBlackTree(InputIterator first, InputIterator last, 
					const value_compare& compare = value_compare()) : 
						root(nullptr),
						// _begin(nullptr), ???
						nil(nullptr), 
						tree_size(0), 
						comp(compare), 
						nodeA()
		{
			initNilRoot();
			for(; first != last; ++first)
				this->insert((*first).value);
		}

	RedBlackTree(const RedBlackTree& other) : RedBlackTree(other.compare)
	{
		*this = other;
	}

/**
 * DESTRUCTOR
 */
	~RedBlackTree()
	{
		this->clear();
		nodeA.destroy(nil);
		nodeA.deallocate(nil, 1);
	}

/**
 * =
 */
	RedBlackTree&	operator=(const RedBlackTree& other)
	{
		if (this == &other)
			return *this;
		this->clear();
		if (!other.empty())
		{
			iterator	itb = other.begin();
			iterator	ite = other.end();
			for (; itb != ite; ++itb)
				this->insert(*itb);
		}
	}

/**
 * BEGIN, END, RBEGIN, REND
 */
		iterator	begin() { return empty() ? iterator(nil) : iterator(treeMin(root)); }
		// const_iterator begin() const;
		iterator	end() { return iterator(nil); }
		// const_iterator end() const;
		reverse_iterator rbegin() { return reverse_iterator(empty() ? iterator(nil) : iterator(treeMax(root))); }
		// const_reverse_iterator rbegin() const;
		reverse_iterator rend() { return reverse_iterator(iterator(nil)); }
		// const_reverse_iterator rend() const;


/**
 * SIZE, MAX_SIZE, EMPTY
 */
		size_type	size() { return tree_size; }
		size_type	max_size() { return nodeA.max_size(); }
		bool		empty() { return (!tree_size); }

/**
 * VALUE_COMP
 */
		value_compare	value_comp() { return comp; }

/**
 * INSERT
 */
	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		nodePtr	existNode = searchNode(val);
		if (existNode != nil)
			return ft::pair<iterator, bool>(iterator(existNode), false);
		
		nodePtr	newNode = nodeA.allocate(1);
		nodeA.construct(newNode, Node(val));
		newNode->left = nil;
		newNode->right = nil;
		insertNode(newNode);
		++tree_size;
		return ft::make_pair(iterator(newNode), true);
	}

	iterator	insert(iterator position, const value_type& val)
	{
		(void)position; /////////////////////////////try to optimize with hint
		return this->insert(val).first;
	}

	template <class InputIterator>
		void	insert (InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				this->insert((*first).value);
		}

/**
 * ERASE
 */
		// void		erase(iterator position)
		// {
		// 	deleteNode(*position);
		// 	--tree_size;
		// }
		// size_type	erase(const value_type& val)
		// {
		// 	nodePtr	n = searchNode(val);
		// 	if (n == nil)
		// 		return 0;
		// 	erase(iterator(n));
		// 	return 1;
		// }
		// void		erase(iterator first, iterator last);

/**
 * CLEAR
 */
		void	clear()
		{
			deleteBranch(this->root);
			this->tree_size = 0;
			this->root = this->nil;
		}

private:
	void	initNilRoot()
	{
		nil = nodeA.allocate(1);
		nodeA.construct(nil, Node());
		nil->isNIL = true;
		nil->color = BLACK;
		nil->left = nullptr;
		nil->right = nullptr;
		nil->parent = nullptr;
		root = nil;
	}

/**
 * *----------------- RBT methods --------------------*
 */
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
 * SEARCH_NODE
 */
	nodePtr	searchNode(int key)
	{
		nodePtr	x = this->root;
		while (x != nil && key != x->value)
		{
			if (comp(key,x->value))
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
 * INSERT
 */
	void	insertNode(nodePtr Node)
	{
		nodePtr	y = this->nil;
		nodePtr	x = this->root;
		while (x != this->nil)
		{
			y = x;
			if (comp(Node->value, x->value))
				x = x->left;
			else
				x = x->right;
		}

		Node->parent = y;
		if (y == this->nil)
			this->root = Node;
		else if (comp(Node->value, y->value))
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
		while (Node->parent->color == RED)
		{
			if (Node->parent == Node->parent->parent->left)
			{
				nodePtr	u = Node->parent->parent->right;
				if (u->color == RED)
				{
					Node->parent->color = BLACK;
					u->color = BLACK;
					Node->parent->parent->color = RED;
					Node = Node->parent->parent;
				}
				else
				{
					if (Node == Node->parent->right)
					{
						Node = Node->parent;
						leftRotate(Node);
					}
					Node->parent->color = BLACK;
					Node->parent->parent->color = RED;
					rightRotate(Node->parent->parent);
				}
			}
			else
			{
				nodePtr	u = Node->parent->parent->left;
				if (u->color == RED)
				{
					Node->parent->color = BLACK;
					u->color = BLACK;
					Node->parent->parent->color = RED;
					Node = Node->parent->parent;
				}
				else
				{
					if (Node == Node->parent->left)
					{
						Node = Node->parent;
						rightRotate(Node);
					}
					Node->parent->color = BLACK;
					Node->parent->parent->color = RED;
					leftRotate(Node->parent->parent);
				}
			}
		}
		this->root->color = BLACK;
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
		bool	orig_color = y->color;

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
			orig_color = y->color;
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
			y->isBlack = Node->color;
		}
		if (orig_color == BLACK)
			deleteFix(x);
	}

/**
 * DELETE_FIXUP
 */
	void	deleteFix(nodePtr x)
	{
		if (x == nullptr)
			return ;
		while (x != this->root && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				nodePtr	w = x->parent->right;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = this->root;
				}
			}
			else
			{
				nodePtr	w = x->parent->left;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->isBlack;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = this->root;
				}
			}
		}
		x->color = BLACK;
	}

/**
 * DELETE_BRANCH (recursive clear nodes)
 */
	void	deleteBranch(nodePtr x)
	{
		if (x && x != nil)
		{
			deleteBranch(x->left);
			deleteBranch(x->right);
			nodeA.destroy(x);
			nodeA.deallocate(x, 1);
		}
	}

};

#endif

/*
	* перегрузить оператор сравнения двух pair по ключам
	* rebind аллокатор с T на pair
*/