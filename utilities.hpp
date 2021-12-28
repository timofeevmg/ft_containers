#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstddef>
#include <iterator>

///////////////////////////////////////////////////////////////////////////////
//                            ITERATOR_TRAITS                                //
///////////////////////////////////////////////////////////////////////////////
template <class Iterator> class iterator_traits
{
public:
	typedef typename Iterator::difference_type			difference_type;
	typedef typename Iterator::value_type				value_type;
	typedef typename Iterator::pointer					pointer;
	typedef typename Iterator::reference				reference;
	typedef typename Iterator::iterator_category		iterator_category;
};
template <class T> class iterator_traits<T*>
{
public:
	typedef std::ptrdiff_t						difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
};
template <class T> class iterator_traits<const T*>
{
public:
	typedef std::ptrdiff_t						difference_type;
	typedef T									value_type;
	typedef const T*							pointer;
	typedef const T&							reference;
	typedef std::random_access_iterator_tag		iterator_category;
};

///////////////////////////////////////////////////////////////////////////////
//                                ENABLE_IF                                  //
///////////////////////////////////////////////////////////////////////////////
template <bool B, class T = void>
	struct	enable_if {};
 
template <class T>
	struct	enable_if <true, T> { typedef T type; };

#endif


//is_integral
//equal
//lexicographical compare
//std::pair
//std::make_pair