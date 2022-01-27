#ifndef CUSTOM_MAP_HPP
#define CUSTOM_MAP_HPP

#include <functional>
#include "iterators/mIterator.hpp"

namespace ft
{
///////////////////////////////////////////////////////////////////////////////
//                                   MAP                                     //
///////////////////////////////////////////////////////////////////////////////
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > > 
		class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef 											iterator;
		typedef 											const_iterator;
		typedef 											reverse_iterator;
		typedef 											const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

	private:
		nodePtr			root;
		nodePtr			tNIL;
		size_type		_size;
		allocator_type	A;

	public:

// CONSTRUCTOR
//// empty
		explicit map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
//// range
		template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());
//// copy
		map(const map& x);

// DESTRUCTOR
		~map();


// =
		map& operator= (const map& x);

// ITERATORS
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

//CAPACITY
		bool		empty() const { return !this->_size; }
		size_type	size() const { return this->_size; }
		size_type	max_size() const { return this->A.max_size(); }

// []
		mapped_type&	operator[](const key_type& k);

// MODIFIERS
//// single element
		pair<iterator,bool>	insert(const value_type& val);
//// with hint
		iterator			insert(iterator position, const value_type& val);
//// range
		template <class InputIterator>
			void			insert (InputIterator first, InputIterator last);

		void		erase(iterator position);
		size_type	erase(const key_type& k);
		void		erase(iterator first, iterator last);

		void	swap(map& x);

		void	clear();

// OBSERVERS
		key_compare		key_comp() const;

		value_compare	value_comp() const;

// OPERATIONS
		iterator		find(const key_type& k);
		const_iterator	find(const key_type& k) const;

		size_type	count(const key_type& k) const; // return 1 or 0 (only unique elements)

		iterator		lower_bound(const key_type& k);
		const_iterator	lower_bound(const key_type& k) const;

		iterator		upper_bound(const key_type& k);
		const_iterator	upper_bound(const key_type& k) const;

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const;
		pair<iterator,iterator>				equal_range(const key_type& k);

// ALLOCATOR
		allocator_type	get_allocator() const { return this->A;}
	};
}

#endif
