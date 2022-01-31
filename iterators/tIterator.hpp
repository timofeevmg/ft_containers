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
		typedef ft::Node<T>*									nodePtr;
		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef T											value_type;
		typedef value_type&									reference;
		typedef value_type*									pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

	private:
		nodePtr		n;

/**
 * SUCCESSOR(послед. элемент)
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
			{
				this->n = other.n;
			}
			return *this;
		}

		nodePtr		getNodePtr() const { return this->n; }

		reference	operator*() { return this->n; }
		pointer		operator->() { return &this->n; }

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
	bool	operator==(const tIterator<T> A, const tIterator<T> B) { return A.getNodePtr() == B.getNodePtr(); }

template <typename T>
	bool	operator!=(const tIterator<T> A, const tIterator<T> B) { return A.getNodePtr() != B.getNodePtr(); }

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
	tRevIterator() : base_iterator() { ;}
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

	tRevIterator	operator+(difference_type n) const 
	{
		return vRevIterator(this->base_iterator - n);
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

	tRevIterator&	operator+=(difference_type n)
	{
		this->base_iterator -= n;
		return *this;
	}

	tRevIterator	operator-(difference_type n) const
	{
		return tRevIterator(this->base_iterator + n);
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

	tRevIterator&	operator-=(difference_type n)
	{
		this->base_iterator += n;
		return *this;
	}

	pointer				operator->() const 
	{
		iterator_type	tmp = this->base_iterator;
		return &(--tmp);
	}

	reference			operator[](difference_type n) const { return this->base_iterator[-n - 1]; }

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