#ifndef STACK_HPP
#define STACK_HPP

#include <vector> //change to myVector

namespace ft
{
	template <typename T, typename Container = std::vector<T> > //change to myVector
		class stack
	{
		private:
			Container	c;

		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef Container						container_type;


// CONSTRUCTOR
			explicit stack (const Container&	c = Container()) : c(c) {};


			bool				empty() const { return c.empty(); }

			size_type			size() const { return c.size(); }

			value_type&			top() { return c.back(); }

			const value_type&	top() const { return c.back(); }

			void				push(const value_type& val) { c.push_back(val); }

			void				pop() { c.pop_back(); }


// relational operators (non-member function overloads)
			friend bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) const 
				{ return (lhs.c == rhs.c); }

			friend bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) const 
				{ return (lhs.c != rhs.c); }

			friend bool	operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) const 
				{ return (lhs.c < rhs.c); }

			friend bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) const 
				{ return (lhs.c <= rhs.c); }

			friend bool	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) const 
				{ return (lhs.c > rhs.c); }

			friend bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) const 
				{ return (lhs.c >= rhs.c); }
///////////////////////////////////////////////////////

	};
};
#endif
