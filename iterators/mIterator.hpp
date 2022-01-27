#ifndef M_ITERATOR_HPP
#define M_ITERATOR_HPP

#include "utilities.hpp"

///////////////////////////////////////////////////////////////////////////////
//                       BIDIRECTIONAL ITERATOR FOR MAP                      //
///////////////////////////////////////////////////////////////////////////////
//                                 ITERATOR                                  //
///////////////////////////////////////////////////////////////////////////////
template <class Key, class T> class mIterator
{
	private:
		struct Node
		{
			ft::pair<const Key, T>	data;
			Node					*left;
			Node					*right;
			Node					*parent;
			bool					isBlack;
			bool					isNIL;
		}

		Node*		ptr;

	public:
		typedef typename Node *								nodePtr
		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
		typedef value_type&									reference;
		typedef value_type*									pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

		mIterator() : ptr(nullptr) {};
		mIterator(const nodePtr _ptr) : ptr(_ptr) {};
		mIterator(const mIterator& other) : ptr(other.getNodePtr());

		~mIterator();

		mIterator&	operator=(const mIterator& other)
		{
			if (this != &other)
			{
				this->ptr = other.ptr;
			}
			return *this;
		}

		nodePtr		getNodePtr() const { return this->ptr; }

		reference	operator*() { return this->ptr->data; }
		pointer		operator->() { return &this->ptr->data; }

		mIterator&	operator++();
		mIterator	operator++(int);

		mIterator&	operator--();
		mIterator	operator--(int);
};


#endif