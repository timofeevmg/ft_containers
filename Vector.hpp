#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "utilities.hpp"

namespace ft
{
///////////////////////////////////////////////////////////////////////////////
//                     RANDOM ACCESS ITERATOR FOR VECTOR                     //
///////////////////////////////////////////////////////////////////////////////
//                              ITERATOR                                     //
///////////////////////////////////////////////////////////////////////////////
	template <typename P> class iterator
	{
	public:
		typedef typename iterator_traits<P *>::value_type			value_type;
		typedef typename iterator_traits<P *>::difference_type		difference_type;
		typedef typename iterator_traits<P *>::pointer				pointer;
		typedef typename iterator_traits<P *>::reference			reference;
		typedef typename iterator_traits<P *>::iterator_category	iterator_category;

		iterator() : ptr(nullptr) {}
		iterator(pointer _ptr) : ptr(_ptr) {}
		iterator(const iterator& other) : ptr(other.ptr) {}
		~iterator() {}
		iterator&	operator= (const iterator& other)
		{
			this->ptr = other.ptr;
			return *this;
		}

		friend bool	operator==(const iterator A, const iterator B) { return A.ptr == B.ptr; }
		friend bool operator!=(const iterator A, const iterator B) { return A.ptr != B.ptr; }
		friend bool operator<(const iterator A, const iterator B) { return A.ptr < B.ptr; }
		friend bool operator>(const iterator A, const iterator B) { return A.ptr > B.ptr; }
		friend bool operator<=(const iterator A, const iterator B) { return A.ptr <= B.ptr; }
		friend bool operator>=(const iterator A, const iterator B) { return A.ptr >= B.ptr; }

		reference	operator*() { return *(this->ptr); }
		pointer		operator->() { return this->ptr; }

//prefix
		reference	operator++()
		{
			++this->ptr;
			return *(this->ptr);
		}
//postfix
		iterator	operator++(int)
		{
			iterator tmp(*this);
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
		iterator	operator--(int)
		{
			iterator tmp(*this);
			--(this->ptr);
			return tmp;
		}

		iterator	operator+(const difference_type& d) const 
		{
			iterator	tmp(this->ptr + d);
			return tmp;
		}
		iterator	operator-(const difference_type& d) const 
		{
			iterator	tmp(this->ptr - d);
			return tmp;
		}
		iterator&	operator+=(const difference_type& d)
		{
			this->ptr += d;
			return *this;
		}
		iterator&	operator-=(const difference_type& d)
		{
			this->ptr -= d;
			return *this;
		}

		reference	operator[](const difference_type& d) const { return *(this->ptr + d); }

	private:
		pointer	ptr;
	};

///////////////////////////////////////////////////////////////////////////////
//                             CONST_ITERATOR                                //
///////////////////////////////////////////////////////////////////////////////
// 	template <typename P> class const_iterator
// 	{
// 	public:
// 		typedef typename iterator_traits<P*>::value_type		value_type;
// 		typedef typename iterator_traits<P*>::difference_type	difference_type;
// 		typedef const typename iterator_traits<P*>::pointer		pointer;
// 		typedef const typename iterator_traits<P*>::reference	reference;
// 		typedef typename iterator_traits<P*>::iterator_category	iterator_category;

// 		const_iterator() : ptr(nullptr) {;}
// 		// const_iterator(pointer _ptr) : ptr(_ptr) {}
// 		// const_iterator(const iterator& iter)
// 		const_iterator(const const_iterator& other) : ptr(other.ptr) {;}
// 		~const_iterator() {;}
// 		const_iterator&	operator= (const const_iterator& other)
// 		{
// 			this->ptr = other.ptr;
// 			return *this;
// 		}

// 		friend bool	operator==(const const_iterator A, const const_iterator B) { return A.ptr == B.ptr; }
// 		friend bool operator!=(const const_iterator A, const const_iterator B) { return A.ptr != B.ptr; }
// 		friend bool operator<(const const_iterator A, const const_iterator B) { return A.ptr < B.ptr; }
// 		friend bool operator>(const const_iterator A, const const_iterator B) { return A.ptr > B.ptr; }
// 		friend bool operator<=(const const_iterator A, const const_iterator B) { return A.ptr <= B.ptr; }
// 		friend bool operator>=(const const_iterator A, const const_iterator B) { return A.ptr >= B.ptr; }

// 		reference	operator*() { return *(this->ptr); }
// 		pointer		operator->() { return this->ptr; }

// //prefix
// 		reference	operator++()
// 		{
// 			++this->ptr;
// 			return *(this->ptr);
// 		}
// //postfix
// 		const_iterator	operator++(int)
// 		{
// 			const_iterator tmp(*this);
// 			++(this->ptr);
// 			return tmp;
// 		}
// //prefix
// 		reference	operator--()
// 		{
// 			--this->ptr;
// 			return *(this->ptr);
// 		}
// //postfix
// 		const_iterator	operator--(int)
// 		{
// 			const_iterator tmp(*this);
// 			--(this->ptr);
// 			return tmp;
// 		}

// 		const_iterator	operator+(const difference_type& d) const 
// 		{
// 			const_iterator	tmp(this->ptr + d);
// 			return tmp;
// 		}
// 		const_iterator	operator-(const difference_type& d) const 
// 		{
// 			const_iterator	tmp(this->ptr - d);
// 			return tmp;
// 		}
// 		const_iterator&	operator+=(const difference_type& d)
// 		{
// 			this->ptr += d;
// 			return *this;
// 		}
// 		const_iterator&	operator-=(const difference_type& d)
// 		{
// 			this->ptr -= d;
// 			return *this;
// 		}

// 		reference	operator[](const difference_type& d) const { return *(this->ptr + d);

// 	private:
// 		pointer	ptr;
// 	};

///////////////////////////////////////////////////////////////////////////////
//                           REVERSE_ITERATOR                                //
///////////////////////////////////////////////////////////////////////////////
//                           MEMBER FUNCTIONS                                //
///////////////////////////////////////////////////////////////////////////////
	template <class Iterator> class reverse_iterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

// CONSTRUCTOR
// DEFAULT
		reverse_iterator() : base_iterator() { ;}
// INITIALIZATION
		explicit reverse_iterator (iterator_type it) : base_iterator(it) { ;}
// COPY
		template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it)
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

		reverse_iterator	operator+(difference_type n) const 
		{
			return reverse_iterator(this->base_iterator - n);
		}

		reverse_iterator&	operator++() 
		{
			--this->base_iterator;
			return *this;
		}

		reverse_iterator	operator++(int) 
		{
			reverse_iterator	tmp = *this;
			--this->base_iterator;
			return tmp;
		}

		reverse_iterator&	operator+=(difference_type n)
		{
			this->base_iterator -= n;
			return *this;
		}

		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator(this->base_iterator + n);
		}

		reverse_iterator&	operator--() 
		{
			++this->base_iterator;
			return *this;
		}

		reverse_iterator	operator--(int) 
		{
			reverse_iterator	tmp = *this;
			++this->base_iterator;
			return tmp;
		}

		reverse_iterator&	operator-=(difference_type n)
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

	private:
		iterator_type	base_iterator;
	};

// RELATIONAL OPERATORS
	template <class Iterator>
		friend bool	operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class Iterator>
		friend bool	operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class Iterator>
		friend bool	operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator>
		friend bool	operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator>
		friend bool	operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator>
		friend bool	operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

// +
	template <class Iterator> 
		friend reverse_iterator<Iterator>	operator+ (
			typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
			{
				return (reverse_iterator<Iterator>(rev_it.base() - n));
			}

// -
	template <class Iterator>
		friend typename reverse_iterator<Iterator>::difference_type	operator- (
			const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
			{
				return (rhs.base() - lhs.base());
			}

///////////////////////////////////////////////////////////////////////////////
//                                VECTOR                                     //
///////////////////////////////////////////////////////////////////////////////
	template <typename T, typename Allocator = std::allocator<T> > 
		class vector
	{
	public:
		typedef typename Allocator::value_type		value_type;
		typedef Allocator							allocator_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef iterator<value_type>				iterator;
		typedef iterator<const value_type>			const_iterator;///////////////////////////////
		typedef reverse_iterator<iterator>			reverse_iterator;
		typedef reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef typename Allocator::difference_type	difference_type;
		typedef typename Allocator::size_type		size_type;


///////////////////////////////////////////////////////////////////////////////
//                           MEMBER FUNCTIONS                                //
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
// DEFAULT
		explicit vector (const allocator_type& alloc = allocator_type()) : 
						_begin(nullptr), _size(0), _capacity(0), A(alloc)
		{
			this->_begin = A.allocate(this->_capacity);
		}


// FILL
		explicit vector (size_type n, const value_type& val = value_type(), 
						const allocator_type& alloc = allocator_type()) : 
						_begin(nullptr), _size(n), _capacity(n * 2), A(alloc)
		{
			this->_begin = A.allocate(this->_capacity);

			pointer	p = this->_begin;
			for (size_type i = 0; i < n; ++i)
				A.construct(p + i, val);
		}


// RANGE
		template <class InputIterator>
			vector (InputIterator first, 
					typename enable_if<!is_integral<InputIterator>::value>::type last, 
					const allocator_type& alloc = allocator_type()) : 
					_begin(nullptr), A(alloc)
		{
			this->_size = last - first;
			this->_capacity = this->_size;
			this->_begin = A.allocate(this->_capacity);
			for (difference_type i = 0; i < static_cast<difference_type>(this->_size); ++i)
				A.construct(this->_begin + i, *(first + i));
		}


// COPY
		vector (const vector& other)
		{
			*this = other;
		}


// DESTRUCTOR
		~vector()
		{
			if (this->_size)
			{
				pointer	p = this->_begin + this->_size - 1;
				for (size_type i = 0; i < this->_size; ++i)
					A.destroy(p - i);
			}
			if (this->_capacity)
				A.deallocate(this->_begin, this->_capacity);
		}


// OPERATOR=
		vector&	operator= (const vector& other)
		{
			if (this == &other)
				return *this;
			if (this->_size)
			{
				pointer	p = this->_begin + this->_size - 1;
				for (size_type i = 0; i < this->_size; ++i)
					A.destroy(p - i);
			}
			if (this->_capacity)
				A.deallocate(this->_begin, this->_capacity);
			this->_size = other.size();
			this->_capacity = other.capacity();
			A.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				A.construct(this->_begin + i, other[i]);
			return *this;
		}


// ITERATORS
		iterator				begin() { return iterator(this->_begin); }
		const_iterator			begin() const { return const_iterator(this->_begin); }
		iterator				end() { return iterator(this->_begin + this->_size); }
		const_iterator			end() const { return const_iterator(this->_begin + this->_size); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }


// CAPACITY
		size_type	size() const { return this->_size; }
		size_type	max_size() const { return (A.max_size());}
		void		resize (size_type n, value_type val = value_type())
		{
			if (n < this->_size)
			{
				for (size_type i = n; i < this->_size; ++i)
					A.destroy(this->_begin + i);
				this->_size = n;
				this->reserve(n * 2);
			}
			else if (n > this->_size)
			{
				if (n > this->_capacity)
					this->reserve(n);
				for (size_type i = this->_size; i < n; ++i)
					A.construct(this->_begin + i, val);
				this->_size = n;
			}
		}
		size_type	capacity() const { return this->_capacity; }
		bool		empty() const { return !this->_size; }
		void		reserve (size_type n)//allocator may throw exceptions => clear allocated
		{
			if (n < this->_capacity)
				return;
			pointer	arr = A.allocate(n);// allocate memory for new array
			for (size_type i = 0; i < this->_size; ++i)
				A.construct(arr + i, *(this->_begin + i));
			for (size_type i = 0; i < this->_size; ++i)
				A.destroy(this->_begin + i);
			if (this->_capacity)
				A.deallocate(this->_begin, this->_capacity);
			this->_capacity = n;
			this->_begin = arr;
		};


// ELEMEN ACCESS
		reference		operator[] (size_type n) { return *(this->_begin + n); }
		const_reference	operator[] (size_type n) const { return *(this->_begin + n); }
		reference		at (size_type n)
		{
			if (n >= this->_size)
				throw (std::out_of_range("out of range"));
			return *(this->_begin + n);
		}
		const_reference	at (size_type n) const
		{
			if (n >= this->_size)
				throw (std::out_of_range("out of range"));
			return *(this->_begin + n);
		}
		reference		front() { return *(this->_begin); }
		const_reference	front() const { return *(this->_begin); }
		reference		back() { return *(this->_begin + this->_size - 1); }
		const_reference	back() const { return *(this->_begin + this->_size - 1); }


// MODIFIERS
// ASSIGN
// RANGE
		template <class InputIterator>
			void	assign (InputIterator first, 
							typename enable_if<!is_integral<InputIterator>::value>::type last)
		{
			if (first > last)
				return;
			this->clear();
			this->_size = last - first;
			if (this->_capacity < this->_size)
				this->reserve(this->_size);
			for (difference_type i = 0; i < static_cast<difference_type>(this->_size); ++i)
				A.construct(this->_begin + i, *(first + i));
		}

// FILL
		void		assign (size_type n, const value_type& val)
		{
			if (this->_size)
			{
				pointer	p = this->_begin + this->_size - 1;
				for (size_type i = 0; i < this->_size; ++i)
					A.destroy(p - i);
			}
			if (this->_capacity < n)
			{
				A.deallocate(this->_begin, this->_capacity);
				this->_capacity = n;
				this->_begin = A.allocate(this->_capacity);
			}
			this->_size = n;
			for (size_type i = 0; i < this->_size; ++i)
				A.construct(this->_begin + i, val);
		}
		void		push_back (const value_type& val)
		{
			if (this->_capacity < this->_size + 1)
				this->reserve(this->_size * 2);
			A.construct(this->_begin + this->_size, val);
			++this->_size;
		}
		void		pop_back()
		{
			if (this->_size)
			{
				A.destroy(this->_begin + this->_size - 1);
				--this->_size;
			}
		}

// INSERT
// SINGLE ELEMENT
		iterator	insert (iterator position, const value_type& val)
		{
			size_type	new_capacity = (this->_size + 1) > this->_capacity ? (this->_size + 1) : this->_capacity;
			pointer		tmp = A.allocate(new_capacity);
			iterator	start = this->begin();
			iterator	end = this->end();
			size_type	i = 0;
			for (; i < position - start; ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i);
			}
			A.construct(tmp + i, val);
			++i;
			for (; i < end - position; ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i - 1);
			}
			A.deallocate(this->_begin, this->_capacity);
			this->_begin = tmp;
			++this->_size;
			this->_capacity = new_capacity;
		}

// FILL
		void		insert (iterator position, size_type n, const value_type& val)
		{
			size_type	new_capacity = (this->_size + n) > this->_capacity ? (this->_capacity = this->_size + n) : this->_capacity;
			pointer		tmp = A.allocate(new_capacity);
			iterator	start = this->begin();
			iterator	end = this->end();
			size_type	i = 0;
			for (; i < position - start; ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i);
			}
			size_type	j = 0;
			for (; j < n; ++j)
				A.construct(tmp + i + j, *(start + i + j));
			i += j;
			for (; i < end - position; ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i - j);
			}
			A.deallocate(this->_begin, this->_capacity);
			this->_begin = tmp;
			this->_size += n;
			this->_capacity = new_capacity;
		}

// RANGE
		// template <class InputIterator>
		// 	void	insert (iterator position, 
		// 					InputIterator first, 
		// 					typename enable_if<!is_integral<InputIterator>::value>::type last);

// ERASE
// SINGLE ELEMENT
		iterator	erase (iterator position)
		{
			size_type	dist = static_cast<size_type>(position - this->begin());
			A.destroy(this->_begin + dist);
			for (size_type i = dist; i < this->_size; ++i)
			{
				A.construct(this->_begin + i, *(this->_begin + i + 1));
				A.destroy(this->_begin + i + 1);
			}
			--this->_size;
			return iterator(this->_begin + dist);
		}

// RANGE
		iterator	erase (iterator first, iterator last)
		{
			size_type	dist = static_cast<size_type>(first - this->begin());
			size_type	range = static_cast<size_type>(last - first);
			for (size_type	i = dist; i < range; ++i)
				A.destroy(this->_begin + i);
			for (size_type	i = dist; i < range; ++i)
			{
				A.construct(this->_begin + i, *(this->_begin + i + range));
				A.destroy(this->_begin + i + range);
			}
			this->_size -= range;
			return iterator(this->_begin + dist);
		}

// SWAP
		void		swap (vector& other)
		{
			pointer		tmp_pointer = this->_begin;
			size_type	tmp_capacity = this->_capacity;
			size_type	tmp_size = this->_size;

			this->_begin = other._begin;
			this->_capacity = other.capacity();
			this->_size = other.size();

			other._begin = tmp_pointer;
			other._capacity = tmp_capacity;
			other._size = tmp_size;
		}

		void		clear()
		{
			if (this->_size)
			{
				pointer	p = this->_begin + this->_size - 1;
				for (size_type i = 0; i < this->_size; ++i)
					A.destroy(p - i);
				this->_size = 0;
			}
		}


// ALLOCATOR
		allocator_type	get_allocator() const { return this->A; }

	private:
		pointer			_begin;
		size_type		_size;
		size_type		_capacity;
		allocator_type	A;
	};

// NON-MEMBER FUNCTION OVERLOADS
// RELATIONAL OPERATORS
		template <class T, class Alloc>
			friend bool	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class T, class Alloc>
			friend bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}

		template <class T, class Alloc>
			friend bool	operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class T, class Alloc>
			friend bool	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(rhs < lhs);
		}

		template <class T, class Alloc>
			friend bool	operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}

		template <class T, class Alloc>
			friend bool	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs < rhs);
		}

// FT::SWAP()
		template <class T, class Alloc>
			void	swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}

};

#endif
