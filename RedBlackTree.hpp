#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <memory>
#include "utilities.hpp"
#include "iterators/tIterator.hpp"


template <class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> > 
	class RedBlackTree
{
public:
	typedef Value			value_type;
	typedef Compare			value_compare;
	typedef Alloc			allocator_type;

	typedef typename Alloc::template rebind<ft::Node<value_type> >::other	nodeAlloc;
	typedef typename nodeAlloc::pointer										nodePtr;

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
	nodePtr			_root;
	// nodePtr			_begin; ???
	nodePtr			_nil;
	size_type		_size;
	value_compare	_compare;
	allocator_type	_valA;
	nodeAlloc		_nodeA;

public:
/**
 * CONSTRUCTOR
 */
	// RedBlackTree() : 
	// 				_root(nullptr), 
	// 				// _begin(nullptr), ???
	// 				_nil(nullptr), 
	// 				_size(0), 
	// 				_compare(), 
	// 				_valA(), 
	// 				_nodeA() 
	// { initNilRoot(); }

	RedBlackTree(const value_compare& c, const allocator_type& alloc = allocator_type()) : 
					_root(nullptr),
					// _begin(nullptr), ???
					_nil(nullptr), 
					_size(0), 
					_compare(c), 
					_valA(alloc), 
					_nodeA(nodeAlloc())
	{ initNilRoot(); }

	template <class InputIterator>
		RedBlackTree(InputIterator first, InputIterator last, 
					const value_compare& c, const allocator_type& alloc = allocator_type()) : 
						_root(nullptr),
						// _begin(nullptr), ???
						_nil(nullptr), 
						_size(0), 
						_compare(c), 
						_valA(alloc), 
						_nodeA(nodeAlloc())
		{
			initNilRoot();
			for(; first != last; ++first)
				this->insert(*first);
		}

	RedBlackTree(const RedBlackTree& other) : 
					_root(nullptr),
					// _begin(nullptr), ???
					_nil(nullptr), 
					_size(0), 
					_compare(other._compare)
	{
		initNilRoot();
		*this = other;
	}

/**
 * DESTRUCTOR
 */
	~RedBlackTree()
	{
		this->clear();
		_nodeA.destroy(_nil);
		_nodeA.deallocate(_nil, 1);
	}

/**
 * =
 */
	RedBlackTree&	operator=(const RedBlackTree& other) ////////don`t forget to change _size
	{
		if (this == &other)
			return *this;
		this->clear();
		_compare = other._compare;
		_nodeA = other._nodeA;
		_valA = other._valA;
		if (!other.empty())
			this->insert(other.begin(), other.end());
		return *this;
	}

/**
 * BEGIN, END, RBEGIN, REND
 */
		iterator		begin() { return empty() ? iterator(_nil) : iterator(treeMin(_root)); }
		const_iterator	begin() const { return empty() ? const_iterator(_nil) : const_iterator(treeMin(_root)); }
		iterator		end() { return iterator(_nil); }
		const_iterator	end() const { return const_iterator(_nil); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const  { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }


/**
 * SIZE, MAX_SIZE, EMPTY
 */
		size_type	size() const { return _size; }
		size_type	max_size() const { return _nodeA.max_size(); }
		bool		empty() const { return (!_size); }

/**
 * INSERT
 */
	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		nodePtr	existNode = searchNode(val);
		if (existNode != _nil)
			return ft::pair<iterator, bool>(iterator(existNode), false);
		
		nodePtr	newNode = _nodeA.allocate(1);
		_nodeA.construct(newNode, ft::Node<value_type>(createValue(val)));
		newNode->left = _nil;
		newNode->right = _nil;
		insertNode(newNode);
		++_size;
		_nil->parent = treeMax(_root); //////////////////////ADDED
		return ft::make_pair(iterator(newNode), true);
	}

	iterator	insert(iterator position, const value_type& val)
	{
		(void)position; /////////////////////////////try to optimize with hint
		return this->insert(val);
	}

	template <class InputIterator>
		void	insert(InputIterator first, InputIterator last, 
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			for (; first != last; ++first)
				this->insert(*first);
		}

/**
 * ERASE
 */
	void		erase(iterator position)
	{
		deleteNode(position.base());
		--_size;
		if (!this->empty())
		{
			_nil->parent = treeMax(_root); //////////////////////ADDED
		}
	}
	
	size_type	erase(const value_type& val)
	{
		nodePtr	n = searchNode(val);
		if (n->isNIL)
			return 0;
		this->erase(iterator(n));
		return 1;
	}

	template <class InputIterator>
		void		erase(InputIterator first, InputIterator last, 
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			for (; first != last; ++first)
				this->erase(first);
		}

/**
 * SWAP
 */
	void	swap(RedBlackTree& other)
	{
		std::swap(this->_root, other._root);
		std::swap(this->_nil, other._nil);
		std::swap(this->_size, other._size);
		std::swap(this->_compare, other._compare);
		std::swap(this->_valA, other._valA);
		std::swap(this->_nodeA, other._nodeA);
	}

/**
 * CLEAR
 */
	void	clear()
	{
		deleteBranch(_root);
		this->_size = 0;
		this->_root = this->_nil;
		this->_nil->parent = nullptr;
	}

/**
 * VALUE_COMP
 */
	value_compare	value_comp() const { return _compare; }

/**
 * FIND
 */
	iterator	find(const value_type& val)
	{
		nodePtr	n = searchNode(val);
		return (n->isNIL) ? this->end() : iterator(n);
	}

/**
 * COUNT
 */
	size_type	count(const value_type& val) const
	{
		nodePtr	n = searchNode(val);
		return (n->isNIL) ? 0 : 1;
	}

/**
 * LOWER_/UPPER_BOUND
 */
	iterator	lower_bound(const value_type& val)
	{
		iterator	first = begin();
		iterator	last = end();
		for (; first != last; ++first)
		{
			if (!_compare(val, *first))
				return first;
		}
		return last;
	}

	iterator	upper_bound(const value_type& val)
	{
		iterator	first = begin();
		iterator	last = end();
		for (; first != last; ++first)
		{
			if (_compare(val, *first))
				return first;
		}
		return last;
	}


private:
	void	initNilRoot()
	{
		_nil = _nodeA.allocate(1);
		_nodeA.construct(_nil, ft::Node<value_type>());
		_nil->value = nullptr;
		_nil->isNIL = true;
		_nil->color = BLACK;
		_nil->left = nullptr;
		_nil->right = nullptr;
		_nil->parent = nullptr;
		_root = _nil;
	}

	pointer	createValue(const value_type& val)
	{
		pointer	newValue = _valA.allocate(1);
		_valA.construct(newValue, val);
		return newValue;
	}

/**
 * DELETE_BRANCH (recursive clear nodes)
 */
	void	deleteBranch(nodePtr x)
	{
		if (x && !x->isNIL)
		{
			deleteBranch(x->left);
			deleteBranch(x->right);
			_valA.destroy(x->value);
			_valA.deallocate(x->value, 1);
			_nodeA.destroy(x);
			_nodeA.deallocate(x, 1);
		}
	}

/**
 * *----------------- RBT methods --------------------*
 */
/**
 * TREE_MINIMUM
 */
	nodePtr	treeMin(nodePtr x) const
	{
		if (x != nullptr)
		{
			while (x->left != _nil)
				x = x->left;
		}
		return x;
	}

/**
 * TREE_MAXIMUM
 */
	nodePtr	treeMax(nodePtr x) const
	{
		if (x != nullptr)
		{
			while (x->right != _nil)
				x = x->right;
		}
		return x;
	}

/**
 * TRANSPLANT
 */
	void	transplantNode(nodePtr u, nodePtr v)
	{
		if (u->parent == _nil)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

/**
 * SEARCH_NODE
 */
	nodePtr	searchNode(const value_type& val) const
	{
		nodePtr	x = _root;
		while (!x->isNIL && val.first != (*x->value).first) ////////////ADDED FOR KEY COMPARISON
		{
			if (_compare(val, *x->value))
				x = x->left;
			else
				x = x->right;
		}
		return x;
	}

/**
 * INORDER_WALK
 */
	void	inorderWalk(nodePtr x) const
	{
		if (x == nullptr)
			return ;
		if (!x->isNIL)
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
		if (x->right != _nil)
			return treeMin(x->right);
		nodePtr	y = x->parent;
		while (y != _nil && x == y->right)
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
		if (x->left != _nil)
			return treeMax(x->left);
		nodePtr	y = x->parent;
		while (y != _nil && x == y->left)
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
		if (y->left != _nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == _nil)
			_root = y;
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
		if (y->right != _nil)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == _nil)
			_root = y;
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
		nodePtr	y = _nil;
		nodePtr	x = _root;
		while (x != _nil)
		{
			y = x;
			if (_compare(*Node->value, *x->value))
				x = x->left;
			else
				x = x->right;
		}

		Node->parent = y;
		if (y == _nil)
			_root = Node;
		else if (_compare(*Node->value, *y->value))
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
		_root->color = BLACK;
	}

/**
 * DELETE_NODE
 */
	void	deleteNode(nodePtr Node)
	{
		if (Node == nullptr)
			return ;
		nodePtr	y = Node;
		nodePtr x = nullptr;
		bool	orig_color = y->color;

		if (Node->left == _nil)
		{
			x = Node->right;
			transplantNode(Node, Node->right);
		}
		else if (Node->right == _nil)
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
			y->color = Node->color;
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
		while (x != _root && x->color == BLACK)
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
					x = _root;
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
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = _root;
				}
			}
		}
		x->color = BLACK;
	}

};

#endif
