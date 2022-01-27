#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

#include <memory>
#include "utilities.hpp"

template <typename T, typename Compare = std::less<T>, 
		typename Allocator = std::allocator<T> > 
	class RBTree
{
public:
	typedef T					value_type;
	typedef Compare				value_compare;
	typedef Allocator			allocator_type;

	// typedef typename Allocator::template rebind<Node<Value>>::other	nodeAlloc;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t		difference_type;
	typedef std::size_t			size_type;

	
};

#endif

/*
	* перегрузить оператор сравнения двух pair по ключам
	* rebind аллокатор с T на pair
*/