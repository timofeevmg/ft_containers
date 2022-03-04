#ifndef V_ITERATOR_HPP
#define V_ITERATOR_HPP

#include "../utilities.hpp"

///////////////////////////////////////////////////////////////////////////////
//                     RANDOM ACCESS ITERATOR FOR VECTOR                     //
///////////////////////////////////////////////////////////////////////////////
//                               ITERATOR                                    //
///////////////////////////////////////////////////////////////////////////////
template <typename T> class vIterator
{
private:
	T*	ptr;

public:
	typedef	T*														iterator_type;
	typedef typename ft::iterator_traits<T *>::value_type			value_type;
	typedef typename ft::iterator_traits<T *>::difference_type		difference_type;
	typedef typename ft::iterator_traits<T *>::pointer				pointer;
	typedef typename ft::iterator_traits<T *>::reference			reference;
	typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;

	typedef std::size_t												size_type;


	vIterator() : ptr(nullptr) {}
	vIterator(const pointer _ptr) : ptr(_ptr) {}
	vIterator(const vIterator& other) : ptr(other.ptr) {}
	~vIterator() {}

	pointer	getPtr() const { return this->ptr; }

	vIterator&	operator= (const vIterator& other)
	{
		if (this != &other)
			this->ptr = other.ptr;
		return *this;
	}

	reference	operator*() { return *(this->ptr); }
	pointer		operator->() { return this->ptr; }

//prefix
	vIterator&	operator++()
	{
		++this->ptr;
		return *(this);
	}
//postfix
	vIterator	operator++(int)
	{
		vIterator tmp(*this);
		++(this->ptr);
		return tmp;
	}
//prefix
	vIterator&	operator--()
	{
		--this->ptr;
		return *(this);
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

	difference_type	operator-(vIterator other) const { return (this->ptr - other.ptr); }

	friend vIterator	operator+(const difference_type& d, const vIterator& Iter)
	{
		vIterator	tmp(Iter);
		return (tmp += d);
	}

	friend vIterator	operator-(const difference_type& d, const vIterator& Iter)
	{
		vIterator	tmp(Iter);
		return (tmp -= d);
	}

};

template <typename T>
	bool	operator==(const vIterator<T> A, const vIterator<T> B) { return A.getPtr() == B.getPtr(); }

template <typename T>
	bool	operator!=(const vIterator<T> A, const vIterator<T> B) { return A.getPtr() != B.getPtr(); }

template <typename T>
	bool	operator<(const vIterator<T> A, const vIterator<T> B) { return A.getPtr() < B.getPtr(); }

template <typename T>
	bool	operator>(const vIterator<T> A, const vIterator<T> B) { return A.getPtr() > B.getPtr(); }

template <typename T>
	bool	operator<=(const vIterator<T> A, const vIterator<T> B) { return A.getPtr() <= B.getPtr(); }

template <typename T>
	bool	operator>=(const vIterator<T> A, const vIterator<T> B) { return A.getPtr() >= B.getPtr(); }

///////////////////////////////////////////////////////////////////////////////
//                            CONST_ITERATOR                                 //
///////////////////////////////////////////////////////////////////////////////

template <typename T> class const_vIterator
{
private:
	const T*	ptr;

public:
	typedef typename ft::iterator_traits<const T *>::value_type			value_type;
	typedef typename ft::iterator_traits<const T *>::difference_type	difference_type;
	typedef typename ft::iterator_traits<const T *>::pointer			pointer;
	typedef typename ft::iterator_traits<const T *>::reference			reference;
	typedef typename ft::iterator_traits<const T *>::iterator_category	iterator_category;

	typedef size_t	size_type;


	const_vIterator() : ptr(nullptr) {}
	const_vIterator(const pointer _ptr) : ptr(_ptr) {}
	const_vIterator(const vIterator<T>& other) : ptr(other.ptr) {}
	const_vIterator(const const_vIterator<T>& other) : ptr(other.ptr) {}
	~const_vIterator() {}

	pointer	getPtr() const { return this->ptr; }

	const_vIterator&	operator= (const const_vIterator& other)
	{
		if (!this != &other)
			this->ptr = other.ptr;
		return *this;
	}

	reference	operator*() { return *(this->ptr); }
	pointer		operator->() { return this->ptr; }

//prefix
	const_vIterator&	operator++()
	{
		++this->ptr;
		return *(this);
	}
//postfix
	const_vIterator	operator++(int)
	{
		const_vIterator tmp(*this);
		++(this->ptr);
		return tmp;
	}
//prefix
	const_vIterator&	operator--()
	{
		--this->ptr;
		return *(this);
	}
//postfix
	const_vIterator	operator--(int)
	{
		const_vIterator tmp(*this);
		--(this->ptr);
		return tmp;
	}

	const_vIterator	operator+(const difference_type& d) const 
	{
		const_vIterator	tmp(this->ptr + d);
		return tmp;
	}
	const_vIterator	operator-(const difference_type& d) const 
	{
		const_vIterator	tmp(this->ptr - d);
		return tmp;
	}
	const_vIterator&	operator+=(const difference_type& d)
	{
		this->ptr += d;
		return *this;
	}
	const_vIterator&	operator-=(const difference_type& d)
	{
		this->ptr -= d;
		return *this;
	}

	reference	operator[](const difference_type& d) const { return *(this->ptr + d); }


	friend const_vIterator	operator+(const difference_type& d, const const_vIterator& Iter)
	{
		const_vIterator	tmp(Iter);
		return (tmp += d);
	}

	friend const_vIterator	operator-(const difference_type& d, const const_vIterator& Iter)
	{
		const_vIterator	tmp(Iter);
		return (tmp -= d);
	}
};

template <typename T>
	bool	operator==(const const_vIterator<T> A, const const_vIterator<T> B) { return A.getPtr() == B.getPtr(); }

template <typename T>
	bool	operator!=(const const_vIterator<T> A, const const_vIterator<T> B) { return A.getPtr() != B.getPtr(); }

template <typename T>
	bool	operator<(const const_vIterator<T> A, const const_vIterator<T> B) { return A.getPtr() < B.getPtr(); }

template <typename T>
	bool	operator>(const const_vIterator<T> A, const const_vIterator<T> B) { return A.getPtr() > B.getPtr(); }

template <typename T>
	bool	operator<=(const const_vIterator<T> A, const const_vIterator<T> B) { return A.getPtr() <= B.getPtr(); }

template <typename T>
	bool	operator>=(const const_vIterator<T> A, const const_vIterator<T> B) { return A.getPtr() >= B.getPtr(); }

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
	typedef typename ft::iterator_traits<vIterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<vIterator>::pointer			pointer;
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

	~vRevIterator() {}

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
