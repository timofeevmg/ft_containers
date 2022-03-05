#ifndef T_ITERATOR_HPP
#define T_ITERATOR_HPP

#include "../utilities.hpp"

///////////////////////////////////////////////////////////////////////////////
//                       BIDIRECTIONAL ITERATOR FOR RBT                      //
///////////////////////////////////////////////////////////////////////////////
//                                 ITERATOR                                  //
///////////////////////////////////////////////////////////////////////////////
template <class T> class tIterator
{
	public:
		typedef typename std::bidirectional_iterator_tag				iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type			value_type;
		typedef typename ft::iterator_traits<T*>::difference_type		difference_type;
		typedef typename ft::iterator_traits<T*>::pointer				pointer;
		typedef typename ft::iterator_traits<T*>::reference				reference;
		typedef std::size_t												size_type;
		typedef ft::Node<value_type>*									nodePtr;

	private:
		nodePtr		_n;

/**
 * TREE_MINIMUM
 */
	nodePtr	treeMin(nodePtr x)
	{
		if (x != nullptr)
		{
			while (x->left->left != nullptr)
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
			while (x->right->right != nullptr)
				x = x->right;
		}
		return x;
	}

/**
 * SUCCESSOR(след. элемент)
 */
	nodePtr	successor(nodePtr x)
	{
		if (x == nullptr)
			return nullptr;
		if (x->right && !x->right->isNIL)
			return treeMin(x->right);
		nodePtr	y = x->parent;
		while (!y->isNIL && x == y->right)
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
		if (x->isNIL)
			return x->parent; //////////////////////////////////ADDED
		if (x->left && !x->left->isNIL)
			return treeMax(x->left);
		nodePtr	y = x->parent;
		while (!y->isNIL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	public:
		tIterator() : _n(nullptr) {}
		tIterator(const nodePtr n) : _n(n) {}
		tIterator(const tIterator& other) : _n(other._n) {}

		~tIterator() {}

		tIterator&	operator=(const tIterator& other)
		{
			if (this != &other)
				_n = other._n;
			return *this;
		}

		nodePtr	base() const
		{
			return _n;
		}

		reference	operator*() const { return *(_n->value); }
		pointer		operator->() const { return _n->value; }

		tIterator&	operator++()
		{
			_n = successor(_n);
			return *this;
		}

		tIterator	operator++(int)
		{
			tIterator tmp(*this);
			_n = successor(_n);
			return tmp;
		}

		tIterator&	operator--()
		{
			_n = predecessor(_n);
			return *this;
		}

		tIterator	operator--(int)
		{
			tIterator tmp(*this);
			_n = predecessor(_n);
			return tmp;
		}
};

template <typename T>
	bool	operator==(const tIterator<T> A, const tIterator<T> B) 
			{ return (A.base() == B.base()); }

template <typename T>
	bool	operator!=(const tIterator<T> A, const tIterator<T> B) 
			{ return !(A == B); }

///////////////////////////////////////////////////////////////////////////////
//                              CONST_ITERATOR                               //
///////////////////////////////////////////////////////////////////////////////
template <class T> class const_tIterator
{
	public:
		typedef typename std::bidirectional_iterator_tag					iterator_category;
		typedef typename ft::iterator_traits<const T*>::value_type			value_type;
		typedef typename ft::iterator_traits<const T*>::difference_type		difference_type;
		typedef typename ft::iterator_traits<const T*>::pointer				pointer;
		typedef typename ft::iterator_traits<const T*>::reference			reference;
		typedef std::size_t													size_type;
		typedef ft::Node<value_type>*										nodePtr;
		typedef const ft::Node<value_type>*									const_nodePtr;

	private:
		nodePtr		_n;

/**
 * TREE_MINIMUM
 */
	nodePtr	treeMin(nodePtr x)
	{
		if (x != nullptr)
		{
			while (x->left->left != nullptr)
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
			while (x->right->right != nullptr)
				x = x->right;
		}
		return x;
	}

/**
 * SUCCESSOR(след. элемент)
 */
	nodePtr	successor(nodePtr x)
	{
		if (x == nullptr)
			return nullptr;
		if (x->right && !x->right->isNIL)
			return treeMin(x->right);
		nodePtr	y = x->parent;
		while (!y->isNIL && x == y->right)
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
		if (x->left && !x->left->isNIL)
			return treeMax(x->left);
		nodePtr	y = x->parent;
		while (!y->isNIL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	public:
		const_tIterator() : _n(nullptr) {}
		const_tIterator(const nodePtr n) : _n(n) {}
		const_tIterator(const const_tIterator& other) : _n(other._n) {}
		const_tIterator(const tIterator<T>& other) : _n(other._n) {}

		~const_tIterator() {}

		const_tIterator&	operator=(const const_tIterator& other)
		{
			if (this != &other)
				_n = other._n;
			return *this;
		}

		nodePtr	base() const
		{
			return _n;
		}

		reference	operator*() const { return *(_n->value); }
		pointer		operator->() const { return _n->value; }

		const_tIterator&	operator++()
		{
			_n = successor(_n);
			return *this;
		}

		const_tIterator	operator++(int)
		{
			const_tIterator tmp(*this);
			_n = successor(_n);
			return tmp;
		}

		const_tIterator&	operator--()
		{
			_n = predecessor(_n);
			return *this;
		}

		const_tIterator	operator--(int)
		{
			const_tIterator tmp(*this);
			_n = predecessor(_n);
			return tmp;
		}
};

template <typename T>
	bool	operator==(const const_tIterator<T> A, const const_tIterator<T> B) 
			{ return (A.base() == B.base()); }

template <typename T>
	bool	operator!=(const const_tIterator<T> A, const const_tIterator<T> B) 
			{ return !(A == B); }

///////////////////////////////////////////////////////////////////////////////
//                            REVERSE ITERATOR                               //
///////////////////////////////////////////////////////////////////////////////
template <class tIterator> class tRevIterator
{
private:
	tIterator	base_iterator;

public:
	typedef tIterator													iterator_type;
	typedef typename ft::iterator_traits<tIterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<tIterator>::value_type			value_type;
	typedef typename ft::iterator_traits<tIterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<tIterator>::pointer			pointer;
	typedef typename ft::iterator_traits<tIterator>::reference			reference;

// CONSTRUCTOR
	// DEFAULT
	tRevIterator() : base_iterator() {}
	// INITIALIZATION
	explicit tRevIterator (iterator_type it) : base_iterator(it) {}
	// COPY
	template <class Iterator>
		tRevIterator (const tRevIterator<Iterator>& rev_it)
	{
		base_iterator = rev_it.base_iterator;
	}

	~tRevIterator() {}

// BASE
	iterator_type	base() const { return base_iterator; }

	reference			operator*() const
	{
		iterator_type	tmp = this->base_iterator;
		return (*--tmp);
	}

	pointer				operator->() const 
	{
		iterator_type	tmp = this->base_iterator;
		return &(*--tmp);
	}

	tRevIterator&	operator++() 
	{
		--this->base_iterator;
		return *this;
	}

	tRevIterator	operator++(int) 
	{
		tRevIterator	tmp = *this;
		--this->base_iterator;
		return tmp;
	}

	tRevIterator&	operator--() 
	{
		++this->base_iterator;
		return *this;
	}

	tRevIterator	operator--(int) 
	{
		tRevIterator	tmp = *this;
		++this->base_iterator;
		return tmp;
	}

};

// RELATIONAL OPERATORS
template <class tIterator>
	bool	operator== (const tRevIterator<tIterator>& lhs, const tRevIterator<tIterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

template <class tIterator>
	bool	operator!= (const tRevIterator<tIterator>& lhs, const tRevIterator<tIterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}


#endif
