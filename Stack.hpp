#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
		class stack
	{
		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef Container						container_type;

		protected:
			container_type	cont;

		public:
// CONSTRUCTOR
			explicit stack(const container_type& _cont = container_type()) : cont(_cont) {}

			stack(const stack& other) : cont(other.cont) {}

			~stack() {}

			stack&	operator=(const stack& other)
			{
				this->cont = other.cont;
				return *this;
			}

			bool				empty() const { return cont.empty(); }

			size_type			size() const { return cont.size(); }

			value_type&			top() { return cont.back(); }

			const value_type&	top() const { return cont.back(); }

			void				push(const value_type& val) { cont.push_back(val); }

			void				pop() { cont.pop_back(); }


// RELATIONAL OPERATORS (non-member function overloads)
			friend bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
				{ return (lhs.cont == rhs.cont); }

			friend bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
				{ return (lhs.cont != rhs.cont); }

			friend bool	operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
				{ return (lhs.cont < rhs.cont); }

			friend bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
				{ return (lhs.cont <= rhs.cont); }

			friend bool	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
				{ return (lhs.cont > rhs.cont); }

			friend bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) 
				{ return (lhs.cont >= rhs.cont); }

	};
};
#endif
