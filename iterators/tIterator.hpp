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
		typedef ft::Node<T>*												nodePtr;
		typedef typename std::bidirectional_iterator_tag					iterator_category;
		typedef typename ft::iterator_traits<nodePtr>::value_type			value_type;
		typedef typename ft::iterator_traits<nodePtr>::difference_type		difference_type;
		typedef typename ft::iterator_traits<nodePtr>::pointer				pointer;
		typedef typename ft::iterator_traits<nodePtr>::reference			reference;
		typedef std::size_t													size_type;

	private:
		nodePtr		n;

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
		tIterator() : n(nullptr) {}
		tIterator(const nodePtr _n) : n(_n) {}
		tIterator(const tIterator& other) : n(other.n) {}

		~tIterator() {}

		tIterator&	operator=(const tIterator& other)
		{
			if (this != &other)
				this->n = other.n;
			return *this;
		}

		reference	operator*() const { return *(this->n); }
		pointer		operator->() const { return this->n; }

		tIterator&	operator++()
		{
			this->n = successor(n);
			return *this;
		}

		tIterator	operator++(int)
		{
			tIterator tmp(*this);
			this->n = successor(n);
			return tmp;
		}

		tIterator&	operator--()
		{
			this->n = predecessor(n);
			return *this;
		}

		tIterator	operator--(int)
		{
			tIterator tmp(*this);
			this->n = predecessor(n);
			return tmp;
		}
};

template <typename T>
	bool	operator==(const tIterator<T> A, const tIterator<T> B) 
			{ return (*A) == (*B); }

template <typename T>
	bool	operator!=(const tIterator<T> A, const tIterator<T> B) 
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
	tRevIterator() : base_iterator() { ; }
	// INITIALIZATION
	explicit tRevIterator (iterator_type it) : base_iterator(it) { ;}
	// COPY
	template <class Iterator>
		tRevIterator (const tRevIterator<Iterator>& rev_it)
	{
		this->base_iterator = rev_it.base_iterator;
	}

	~tRevIterator() {}

// BASE
	iterator_type	base() const { return this->base_iterator; }

	reference			operator*() const
	{
		iterator_type	tmp = this->base_iterator;
		return (*--tmp);
	}

	pointer				operator->() const 
	{
		iterator_type	tmp = this->base_iterator;
		return &(--tmp);
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
