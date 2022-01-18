#ifndef V_ITERATOR_HPP
#define V_ITERATOR_HPP

#include "utilities.hpp"

///////////////////////////////////////////////////////////////////////////////
//                     RANDOM ACCESS ITERATOR FOR VECTOR                     //
///////////////////////////////////////////////////////////////////////////////
//                              ITERATOR                                     //
///////////////////////////////////////////////////////////////////////////////
template <typename P> class vIterator
{
private:
	P*	ptr;

public:
	typedef typename ft::iterator_traits<P *>::value_type			value_type;
	typedef typename ft::iterator_traits<P *>::difference_type		difference_type;
	typedef typename ft::iterator_traits<P *>::pointer				pointer;
	typedef typename ft::iterator_traits<P *>::reference			reference;
	typedef typename ft::iterator_traits<P *>::iterator_category	iterator_category;

	vIterator() : ptr(nullptr) {}
	vIterator(pointer _ptr) : ptr(_ptr) {}
	vIterator(const vIterator& other) : ptr(other.ptr) {}
	~vIterator() {}

	vIterator&	operator= (const vIterator& other)
	{
		this->ptr = other.ptr;
		return *this;
	}

	reference	operator*() { return *(this->ptr); }
	pointer		operator->() { return this->ptr; }

//prefix
	reference	operator++()
	{
		++this->ptr;
		return *(this->ptr);
	}
//postfix
	vIterator	operator++(int)
	{
		vIterator tmp(*this);
		++(this->ptr);
		return tmp;
	}
//prefix
	reference	operator--()
	{
		--this->ptr;
		return *(this->ptr);
	}
//postfix
	vIterator	operator--(int)
	{
		vIterator tmp(*this);
		--(this->ptr);
		return tmp;
	}

	vIterator	operator+(const difference_type& d) const 
	{
		vIterator	tmp(this->ptr + d);
		return tmp;
	}
	vIterator	operator-(const difference_type& d) const 
	{
		vIterator	tmp(this->ptr - d);
		return tmp;
	}
	vIterator&	operator+=(const difference_type& d)
	{
		this->ptr += d;
		return *this;
	}
	vIterator&	operator-=(const difference_type& d)
	{
		this->ptr -= d;
		return *this;
	}

	reference	operator[](const difference_type& d) const { return *(this->ptr + d); }

};

template <typename P>
	bool	operator==(const vIterator<P> A, const vIterator<P> B) { return A.ptr == B.ptr; }

template <typename P>
	bool	operator!=(const vIterator<P> A, const vIterator<P> B) { return A.ptr != B.ptr; }

template <typename P>
	bool	operator<(const vIterator<P> A, const vIterator<P> B) { return A.ptr < B.ptr; }

template <typename P>
	bool	operator>(const vIterator<P> A, const vIterator<P> B) { return A.ptr > B.ptr; }

template <typename P>
	bool	operator<=(const vIterator<P> A, const vIterator<P> B) { return A.ptr <= B.ptr; }

template <typename P>
	bool	operator>=(const vIterator<P> A, const vIterator<P> B) { return A.ptr >= B.ptr; }

///////////////////////////////////////////////////////////////////////////////
//                             CONST_ITERATOR                                //
///////////////////////////////////////////////////////////////////////////////
template <typename P> class const_iterator
{
private:
	const P*	ptr;

public:
	typedef typename iterator_traits<P*>::value_type		value_type;
	typedef typename iterator_traits<P*>::difference_type	difference_type;
	typedef const typename iterator_traits<P*>::pointer		pointer;
	typedef const typename iterator_traits<P*>::reference	reference;
	typedef typename iterator_traits<P*>::iterator_category	iterator_category;

	const_iterator() : ptr(nullptr) {;}
	// const_iterator(pointer _ptr) : ptr(_ptr) {}
	// const_iterator(const iterator& iter)
	const_iterator(const const_iterator& other) : ptr(other.ptr) {;}
	~const_iterator() {;}
	const_iterator&	operator= (const const_iterator& other)
	{
		this->ptr = other.ptr;
		return *this;
	}

	friend bool	operator==(const const_iterator A, const const_iterator B) { return A.ptr == B.ptr; }
	friend bool operator!=(const const_iterator A, const const_iterator B) { return A.ptr != B.ptr; }
	friend bool operator<(const const_iterator A, const const_iterator B) { return A.ptr < B.ptr; }
	friend bool operator>(const const_iterator A, const const_iterator B) { return A.ptr > B.ptr; }
	friend bool operator<=(const const_iterator A, const const_iterator B) { return A.ptr <= B.ptr; }
	friend bool operator>=(const const_iterator A, const const_iterator B) { return A.ptr >= B.ptr; }

	reference	operator*() { return *(this->ptr); }
	pointer		operator->() { return this->ptr; }

//prefix
	reference	operator++()
	{
		++this->ptr;
		return *(this->ptr);
	}
//postfix
	const_iterator	operator++(int)
	{
		const_iterator tmp(*this);
		++(this->ptr);
		return tmp;
	}
//prefix
	reference	operator--()
	{
		--this->ptr;
		return *(this->ptr);
	}
//postfix
	const_iterator	operator--(int)
	{
		const_iterator tmp(*this);
		--(this->ptr);
		return tmp;
	}

	const_iterator	operator+(const difference_type& d) const 
	{
		const_iterator	tmp(this->ptr + d);
		return tmp;
	}
	const_iterator	operator-(const difference_type& d) const 
	{
		const_iterator	tmp(this->ptr - d);
		return tmp;
	}
	const_iterator&	operator+=(const difference_type& d)
	{
		this->ptr += d;
		return *this;
	}
	const_iterator&	operator-=(const difference_type& d)
	{
		this->ptr -= d;
		return *this;
	}

	reference	operator[](const difference_type& d) const { return *(this->ptr + d); }

};

///////////////////////////////////////////////////////////////////////////////
//                           REVERSE_ITERATOR                                //
///////////////////////////////////////////////////////////////////////////////
//                           MEMBER FUNCTIONS                                //
///////////////////////////////////////////////////////////////////////////////
template <class vIterator> class vRevIterator
{
private:
	vIterator	base_iterator;

public:
	typedef vIterator													iterator_type;
	typedef typename ft::iterator_traits<vIterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<vIterator>::value_type			value_type;
	typedef typename ft::iterator_traits<vIterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<vIterator>::pointer				pointer;
	typedef typename ft::iterator_traits<vIterator>::reference			reference;

// CONSTRUCTOR
	// DEFAULT
	vRevIterator() : base_iterator() { ;}
	// INITIALIZATION
	explicit vRevIterator (iterator_type it) : base_iterator(it) { ;}
	// COPY
	template <class Iterator>
		vRevIterator (const vRevIterator<Iterator>& rev_it)
	{
		this->base_iterator = rev_it.base_iterator;
	}

// BASE
	iterator_type	base() const { return this->base_iterator; }

	reference			operator*() const
	{
		iterator_type	tmp = this->base_iterator;
		return (*--tmp);
	}

	vRevIterator	operator+(difference_type n) const 
	{
		return vRevIterator(this->base_iterator - n);
	}

	vRevIterator&	operator++() 
	{
		--this->base_iterator;
		return *this;
	}

	vRevIterator	operator++(int) 
	{
		vRevIterator	tmp = *this;
		--this->base_iterator;
		return tmp;
	}

	vRevIterator&	operator+=(difference_type n)
	{
		this->base_iterator -= n;
		return *this;
	}

	vRevIterator	operator-(difference_type n) const
	{
		return vRevIterator(this->base_iterator + n);
	}

	vRevIterator&	operator--() 
	{
		++this->base_iterator;
		return *this;
	}

	vRevIterator	operator--(int) 
	{
		vRevIterator	tmp = *this;
		++this->base_iterator;
		return tmp;
	}

	vRevIterator&	operator-=(difference_type n)
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
template <class vIterator>
	bool	operator== (const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

template <class vIterator>
	bool	operator!= (const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

template <class vIterator>
	bool	operator<  (const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

template <class vIterator>
	bool	operator<= (const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

template <class vIterator>
	bool	operator>  (const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

template <class vIterator>
	bool	operator>= (const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

// +
template <class vIterator> 
	vRevIterator<vIterator>	operator+ (
		typename vRevIterator<vIterator>::difference_type n, const vRevIterator<vIterator>& rev_it)
		{
			return (vRevIterator<vIterator>(rev_it.base() - n));
		}

// -
template <class vIterator>
	typename vRevIterator<vIterator>::difference_type	operator- (
		const vRevIterator<vIterator>& lhs, const vRevIterator<vIterator>& rhs)
		{
			return (rhs.base() - lhs.base());
		}


#endif
