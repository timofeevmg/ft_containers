#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>

#include "vIterator.hpp"

namespace ft
{
///////////////////////////////////////////////////////////////////////////////
//                                VECTOR                                     //
///////////////////////////////////////////////////////////////////////////////
	template <typename T, typename Allocator = std::allocator<T> > 
		class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer	const_pointer;

		typedef ptrdiff_t	difference_type;
		typedef size_t		size_type;

		typedef vIterator<value_type>				iterator;
		typedef const_vIterator<value_type>			const_iterator;
		typedef vRevIterator<iterator>				reverse_iterator;
		typedef vRevIterator<const_iterator>		const_reverse_iterator;

	private:
		pointer		_begin;
		size_type	_size;
		size_type	_capacity;
		Allocator	A;

	public:
///////////////////////////////////////////////////////////////////////////////
//                           MEMBER FUNCTIONS                                //
///////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
//// DEFAULT
		explicit vector (const allocator_type& alloc = allocator_type()) : 
						_begin(nullptr), _size(0), _capacity(0), A(alloc)
		{
			this->_begin = A.allocate(this->_capacity);
		}
// explicit - not to implicitly convert data types


//// FILL
		explicit vector (size_type n, const value_type& val = value_type(), 
						const allocator_type& alloc = allocator_type()) : 
						_begin(nullptr), _size(n), _capacity(n), A(alloc)
		{
			this->_begin = A.allocate(this->_capacity);

			for (size_type i = 0; i < n; ++i)
				A.construct(&this->_begin[i], val);
		}


//// RANGE
		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(), 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : 
					_begin(nullptr), A(alloc)
		{
			this->_size = last - first;
			this->_capacity = this->_size;
			this->_begin = A.allocate(this->_capacity);
			for (difference_type i = 0; i < static_cast<difference_type>(this->_size); ++i)
				A.construct(&this->_begin[i], *(first + i));
		}


//// COPY
		vector (const vector& other) : 
			_begin(nullptr), _size(other._size), _capacity(other._capacity), A(other.A) 
		{
			this->_begin = A.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				A.construct(&this->_begin[i], other[i]);
		}


// DESTRUCTOR
		~vector()
		{
			for (size_type i = 0; i < this->_size; ++i)
				A.destroy(&this->_begin[i]);
			A.deallocate(this->_begin, this->_capacity);
		}


// OPERATOR=
		vector&	operator= (const vector& other)
		{
			if (this == &other)
				return *this;

			this->~vector();
			// pointer	p = this->_begin + this->_size - 1;
			// for (size_type i = 0; i < this->_size; ++i)
			// 	A.destroy(p - i);

			// A.deallocate(this->_begin, this->_capacity);
			this->_size = other.size();
			this->_capacity = other.capacity();
			this->_begin = A.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				A.construct(&this->_begin[i], other[i]);
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

//// RESIZE
		void		resize (size_type n, value_type val = value_type())
		{
			if (n > this->_capacity)
				(n < 2 * this->_capacity) ? this->reallocVector(2 * this->_capacity) : this->reallocVector(n);
			while (n > this->_size)
				push_back(val);
			while(n < this->_size)
				pop_back();
		}

		size_type	capacity() const { return this->_capacity; }
		bool		empty() const { return !this->_size; }

//// RESERVE
		void		reserve (size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("too large to allocate vector");
			if (n > this->_capacity)
				this->reallocVector(n);
		};


// ELEMEN ACCESS
		reference		operator[] (size_type n) { return *(this->_begin + n); }
		const_reference	operator[] (size_type n) const { return *(this->_begin + n); }

//// AT
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
//// ASSIGN
////// RANGE
		template <class InputIterator>
			void	assign (InputIterator first, InputIterator last, 
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			if (first > last)
				return;
			this->clear();
			size_type	newSize = static_cast<size_type>(last - first);
			if (newSize > this->_capacity)
				this->reallocVector(newSize);
			for (size_type i = 0; first != last; ++i, ++first)
				A.construct(this->_begin + i, *first);
			this->_size = newSize;
		}

////// FILL
		void		assign (size_type n, const value_type& val)
		{
			this->clear();
			if (n > this->_capacity)
				this->reallocVector(n);
			for (size_type i = 0; i < n; ++i)
				A.construct(this->_begin + i, val);
			this->_size = n;
		}

//// PUSH_BACK
		void		push_back (const value_type& val)
		{
			if (this->_capacity < this->_size + 1)
				this->reserve(this->_size * 2);
			if (this->_size + 1 > this->_capacity)
                    reallocVector(!this->_capacity ? 1 : this->_capacity * 2);
			A.construct(&this->_begin[this->_size], val);
			++this->_size;
		}

//// POP_BACK
		void		pop_back()
		{
			if (this->_size)
			{
				A.destroy(this->_begin + this->_size - 1);
				--this->_size;
			}
		}

//// INSERT
////// SINGLE ELEMENT
		iterator	insert (iterator position, const value_type& val)
		{
			difference_type	dist = position - this->begin();
			this->insert(position, 1, val);
			return	iterator(this->_begin + dist);
		}

////// FILL
		void		insert (iterator position, size_type n, const value_type& val)
		{
			size_type	new_capacity;
			if ((this->_size + 1) > this->_capacity)
			{
				if ((this->_size + 1) < (this->_capacity * 2))
					new_capacity = this->_capacity * 2;
				else
					new_capacity = this->_size + 1;
			}
			else
				new_capacity = this->_capacity;
			pointer		tmp = A.allocate(new_capacity);
			iterator	start = this->begin();
			iterator	end = this->end();
			size_type	i = 0;
			for (; i < static_cast<size_type>(position - start); ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i);
			}
			size_type	j = 0;
			for (; j < n; ++j)
				A.construct(tmp + i + j, val);
			i += j;
			for (; i < static_cast<size_type>(end - position); ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i - j);
			}
			A.deallocate(this->_begin, this->_capacity);
			this->_begin = tmp;
			this->_size += n;
			this->_capacity = new_capacity;
		}

////// RANGE
		template <class InputIterator>
			void	insert (iterator position, InputIterator first, InputIterator last,
							typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
		{
			size_type	length = static_cast<size_type>(last - first);
			size_type	newCap;
			if ((this->_size + length) > this->_capacity)
			{
				if ((this->_size + length) < (this->_capacity * 2))
					newCap = this->_capacity * 2;
				else
					newCap = this->_size + length;
			}
			else
				newCap = this->_capacity;
			pointer		tmp = A.allocate(newCap);
			iterator	start = this->begin();
			iterator	end = this->end();
			size_type	i = 0;
			for (; i < position - start; ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i);
			}
			size_type	j = 0;
			for (; j < length; ++j, ++first)
				A.construct(tmp + i + j, *first);
			i += j;
			for (; i < end - position; ++i)
			{
				A.construct(tmp + i, *(start + i));
				A.destroy(this->_begin + i - j);
			}
			A.deallocate(this->_begin, this->_capacity);
			this->_begin = tmp;
			this->_size += length;
			this->_capacity = newCap;
		}

//// ERASE
////// SINGLE ELEMENT
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

////// RANGE
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
			pointer			tmp_pointer = this->_begin;
			size_type		tmp_capacity = this->_capacity;
			size_type		tmp_size = this->_size;
			allocator_type	tmp_alloc = this->A;

			this->_begin = other._begin;
			this->_capacity = other.capacity();
			this->_size = other.size();
			this->A = other.get_allocator();

			other._begin = tmp_pointer;
			other._capacity = tmp_capacity;
			other._size = tmp_size;
			other.A = tmp_alloc;
		}

		void		clear()
		{
			while (this->_size != 0)
				this->pop_back();
		}


// ALLOCATOR
		allocator_type	get_allocator() const { return this->A; }

	private:
		void reallocVector(size_type newCap)
		{
			pointer	tmp = A.allocate(newCap);

			for (size_type i = 0; i < this->_size; ++i)
				A.construct(tmp + i, *(this->_begin + i));
			this->~vector();
			this->_begin = tmp;
			this->_capacity = newCap;
		}
	};

// NON-MEMBER FUNCTION OVERLOADS
// RELATIONAL OPERATORS
		template <class T, class Alloc>
			bool	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class T, class Alloc>
			bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(lhs == rhs);
		}

		template <class T, class Alloc>
			bool	operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class T, class Alloc>
			bool	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return !(rhs < lhs);
		}

		template <class T, class Alloc>
			bool	operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (rhs < lhs);
		}

		template <class T, class Alloc>
			bool	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
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
