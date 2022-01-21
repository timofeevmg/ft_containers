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
//                              IS_INTEGRAL                                  //
///////////////////////////////////////////////////////////////////////////////
	template <class T, bool v>
		struct integral_constant
		{
			static const bool				value = v;
			typedef T						value_type;
			typedef integral_constant<T, v>	type;
			operator T() const { return v; }
		};
	
	template <class T> struct is_integral : public integral_constant<T, false> {};
	template <> struct is_integral<bool> : public integral_constant<bool, true> {};
	template <> struct is_integral<char> : public integral_constant<char, true> {};
	template <> struct is_integral<char16_t> : public integral_constant<char16_t, true> {};
	template <> struct is_integral<char32_t> : public integral_constant<char32_t, true> {};
	template <> struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};
	template <> struct is_integral<signed char> : public integral_constant<signed char, true> {};
	template <> struct is_integral<short int> : public integral_constant<short int, true> {};
	template <> struct is_integral<int> : public integral_constant<int, true> {};
	template <> struct is_integral<long int> : public integral_constant<long int, true> {};
	template <> struct is_integral<long long int> : public integral_constant<long long int, true> {};
	template <> struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};
	template <> struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};
	template <> struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
	template <> struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};
	template <> struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};

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
	};

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
	};

///////////////////////////////////////////////////////////////////////////////
//                                   PAIR                                    //
///////////////////////////////////////////////////////////////////////////////
	template <class T1, class T2> 
		struct pair
	{
	public:
		typedef T1			first_type;
		typedef T2			second_type;

		first_type			first;
		second_type			second;

// CONSTRUCTOR
//// DEFAULT
		pair() : first(), second() {};

//// COPY
		template <class U, class V> 
			pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {};

//// INIT
		pair(const first_type& a, const second_type& b) : first(a), second(b) {};

		~pair() {};

// =
		pair&	operator= (const pair& pr)
		{
			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return *this;
		}
	};

// RELATIONAL OPERATORS
	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

	template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

	template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }

// MAKE PAIR
	template <class T1,class T2>
		pair<T1,T2> make_pair (T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }

///////////////////////////////////////////////////////////////////////////////
//                                CONDITIONAL                                //
///////////////////////////////////////////////////////////////////////////////
	// template<bool B, class T, class F>
	// 	struct conditional
	// 	{
	// 		typedef T type;
	// 	};
	
	// template<class T, class F>
	// 	struct conditional<false, T, F>
	// 	{
	// 		typedef F type;
	// 	};
};


#endif

//std::pair
//std::make_pair
