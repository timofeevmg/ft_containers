#ifndef CUSTOM_SET_HPP
#define CUSTOM_SET_HPP

#include <functional>
#include <algorithm>
#include "../utilities.hpp"
#include "RedBlackTree.hpp"

namespace ft
{
/**
 * ///////////////////////////////////////////////////////////////////////////////
 * //                                   SET                                     //
 * ///////////////////////////////////////////////////////////////////////////////
 */
	template <class T, class Compare = std::less<T>, 
			class Alloc = std::allocator<T> > 
		class set
	{
	public:
		typedef T											key_type;
		typedef T											value_type;
		typedef Compare										key_compare;
		typedef Compare										value_compare;
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

	private:
		tree_type		_tree;
		key_compare		_key_comp;
		allocator_type	_alloc;

	public:
// CONSTRUCTOR
//// empty
		explicit set(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : 
					_tree(tree_type(comp, alloc)), _key_comp(comp), _alloc(alloc) {}

//// range
		template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : 
				_tree(tree_type(first, last, comp, alloc)), _key_comp(comp) {}

//// copy
		set(const set& other) : _tree(other._tree), _key_comp(other._key_comp) {}

// DESTRUCTOR
		~set() {}


// =
		set& operator= (const set& x)
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
			return (this->insert(val)).first;
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
		size_type	erase(const value_type& val)
		{
			return this->_tree.erase(val);
		}
//// RANGE
		void		erase(iterator first, iterator last)
		{
			this->_tree.erase(first, last);
		}

/**
 * SWAP
 */
		void	swap(set& x)
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

		value_compare	value_comp() const { return this->key_comp(); }

// OPERATIONS
/**
 * FIND
 */
		iterator		find(const key_type& k)
		{
			return this->_tree.find(k);
		}
		const_iterator	find(const key_type& k) const
		{
			return this->_tree.find(k);
		}

// return 1 or 0 (only unique elements)
		size_type	count(const key_type& k) const
		{
			return this->_tree.count(k);
		} 

/**
 * LOWER_BOUND
 */
		iterator		lower_bound(const key_type& k)
		{
			return this->_tree.lower_bound(k);
		}
		const_iterator	lower_bound(const key_type& k) const
		{
			return this->_tree.lower_bound(k);
		}

/**
 * UPPER_BOUND
 */
		iterator		upper_bound(const key_type& k)
		{
			return this->_tree.upper_bound(k);
		}
		const_iterator	upper_bound(const key_type& k) const
		{
			return this->_tree.upper_bound(k);
		}

/**
 * EQUAL_RANGE
 */
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{
			return make_pair(this->_tree.lower_bound(k), this->_tree.upper_bound(k));
		}
		pair<iterator,iterator>				equal_range(const key_type& k)
		{
			return make_pair(this->_tree.lower_bound(k), this->_tree.upper_bound(k));
		}

// ALLOCATOR
		allocator_type	get_allocator() const { return _alloc;}
	};

/**
 * NON-MEMBER FUNCTION OVERLOADS
 * RELATIONAL_OPERATORS
 */
	template <class T, class Compare, class Alloc>
			bool	operator==(const set<T,Compare,Alloc>& lhs, 
								const set<T,Compare,Alloc>& rhs)
			{
				return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

	template <class T, class Compare, class Alloc>
			bool	operator!=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
			{
				return !(lhs == rhs);
			}

	template <class T, class Compare, class Alloc>
			bool	operator<(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}

	template <class T, class Compare, class Alloc>
			bool	operator<=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
			{
				return !(rhs < lhs);
			}

	template <class T, class Compare, class Alloc>
			bool	operator>(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
			{
				return !(lhs <= rhs);
			}

	template <class T, class Compare, class Alloc>
			bool	operator>=(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
			{
				return !(lhs < rhs);
			}

/**
 * SWAP
 */
	template <class T, class Compare, class Alloc>
			void swap(set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
			{
				x.swap(y);
			}
};

#endif
