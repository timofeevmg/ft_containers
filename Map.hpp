#ifndef CUSTOM_MAP_HPP
#define CUSTOM_MAP_HPP

#include <functional>
#include "utilities.hpp"

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
		typedef 											difference_type;
		typedef size_t										size_type;

	};
}

#endif
