#ifndef CUSTOM_MAP_HPP
#define CUSTOM_MAP_HPP

#include <functional>
#include <algorithm>
#include "utilities.hpp"
#include "RedBlackTree.hpp"

namespace ft
{
/**
 * ///////////////////////////////////////////////////////////////////////////////
 * //                                   MAP                                     //
 * ///////////////////////////////////////////////////////////////////////////////
 */
	template <class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > > 
		class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

		typedef RedBlackTree<value_type, key_compare, allocator_type>	tree_type;
		typedef typename	tree_type::iterator							iterator;
		typedef typename	tree_type::const_iterator					const_iterator;
		typedef typename	tree_type::reverse_iterator					reverse_iterator;
		typedef typename	tree_type::const_reverse_iterator			const_reverse_iterator;

		class value_compare
		{
		private:
			key_compare _comp;

		public:
			value_compare(const key_compare& c) : _comp(c) {}

			bool operator()(const value_type& x, const value_type& y) const 
			{ return (_comp(x.first, y.first)); }
		};

	private:
		tree_type		_tree;
		key_compare		_key_comp;

	public:
// CONSTRUCTOR
//// empty
		map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : 
					_tree(tree_type(comp, alloc), _key_comp(comp)) {}

//// range
		template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : 
				_tree(tree_type(comp, alloc)), _key_comp(comp)
		{
			this->_tree.insert(first, last);
		}

//// copy
		map(const map& x)
		{
			
		}

// DESTRUCTOR
		~map() {}


// =
		map& operator= (const map& x)
		{
			if (this != &x)
			{
				this->_tree = x._tree;
				this->_key_comp = x._key_comp;
			}
			return *this;
		}

// ITERATORS
		iterator				begin() { return this->_tree.begin(); }
		const_iterator			begin() const { return this->_tree.begin(); }
		iterator				end() { return this->_tree.end(); }
		const_iterator			end() const { return this->_tree.end(); }
		reverse_iterator		rbegin() { return this->_tree.rbegin(); }
		const_reverse_iterator	rbegin() const { return this->_tree.rbegin(); }
		reverse_iterator		rend() { return this->_tree.rend(); }
		const_reverse_iterator	rend() const { return this->_tree.rend(); }

//CAPACITY
		bool		empty() const { return this->_tree.empty(); }
		size_type	size() const { return this->_tree.size(); }
		size_type	max_size() const { return this->_tree.max_size(); }

// []
		mapped_type&	operator[](const key_type& k)
			return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;

// MODIFIERS
/**
 * INSERT
 */
//// single element
		pair<iterator,bool>	insert(const value_type& val)
		{
			return (this->_tree.insert(val));
		}
//// with hint (Hint for the position where the element can be inserted)
		iterator			insert(iterator position, const value_type& val)
		{
			(void)position; //////////////////////try to optimize with hint
			return this->insert(val);
		}
//// range
		template <class InputIterator>
			void			insert (InputIterator first, InputIterator last, 
									typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
		{
			this->_tree.insert(first, last);
		}

/**
 * ERASE
 */
//// POSITION
		void		erase(iterator position)
		{
			this->_tree.erase(position);
		}
//// KEY
		size_type	erase(const key_type& k)
		{
			this->_tree(ft::make_pair(k, mapped_type()));
		}
//// RANGE
		void		erase(iterator first, iterator last)
		{
			this->_tree.erase(first, last);
		}

/**
 * SWAP
 */
		void	swap(map& x)
		{
			std::swap(this->_key_comp, x._key_comp);
			this->_tree.swap(x._tree);
		}

/**
 * CLEAR
 */
		void	clear() { this->_tree.clear(); }

// OBSERVERS
		key_compare		key_comp() const { return this->_key_comp; }

		value_compare	value_comp() const { return this->_tree.value_comp(); }

// OPERATIONS
/**
 * FIND
 */
		iterator		find(const key_type& k)
		{
			return this->_tree.find(ft::make_pair(k, mapped_type()));
		}
		const_iterator	find(const key_type& k) const
		{
			return this->_tree.find(ft::make_pair(k, mapped_type()));
		}

// return 1 or 0 (only unique elements)
		size_type	count(const key_type& k) const
		{
			return this->_tree.count(ft::make_pair(k, mapped_type()));
		} 

/**
 * LOWER_BOUND
 */
		iterator		lower_bound(const key_type& k)
		{
			return this->_tree.lower_bound(ft::make_pair(k, mapped_type()));
		}
		const_iterator	lower_bound(const key_type& k) const
		{
			return this->_tree.lower_bound(ft::make_pair(k, mapped_type()));
		}

/**
 * UPPER_BOUND
 */
		iterator		upper_bound(const key_type& k)
		{
			return this->_tree.upper_bound(ft::make_pair(k, mapped_type()));
		}
		const_iterator	upper_bound(const key_type& k) const
		{
			return this->_tree.upper_bound(ft::make_pair(k, mapped_type()));
		}

/**
 * EQUAL_RANGE
 */
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{
			return this->_tree.equal_range(ft::make_pair(k, mapped_type()));
		}
		pair<iterator,iterator>				equal_range(const key_type& k)
		{
			return this->_tree.equal_range(ft::make_pair(k, mapped_type()));
		}

// ALLOCATOR
		allocator_type	get_allocator() const { return this->A;}
	};
}

#endif
