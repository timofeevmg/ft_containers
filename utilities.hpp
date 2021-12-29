#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
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

///////////////////////////////////////////////////////////////////////////////
//                                  EQUAL                                    //
///////////////////////////////////////////////////////////////////////////////
	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				return false;
			}
		}
		return true;
	}

///////////////////////////////////////////////////////////////////////////////
//                        LEXICOGRAPHICAL_COMPARE                            //
///////////////////////////////////////////////////////////////////////////////
	template<class InputIterator1, class InputIterator2>
		bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
	
};

#endif


//is_integral
//std::pair
//std::make_pair