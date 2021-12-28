#include "Stack.hpp"

#include <iostream>

int	main()
{
	ft::stack<int>	st;

	std::cout << "Test STACK\n" 
				<< "************************************************************\n"
				<< "st empty:			" 
				<< std::boolalpha 
				<< st.empty() 
				<< "	(must be: true)"
				<< std::endl;

	std::cout << "st push 5 integers			{0, 1, 2, 3, 4}" 
				<< std::endl;
	for(int i = 0; i < 5; ++i)
	{
		st.push(i);
	}

	std::cout << "st size:			" 
				<< st.size() 
				<< "	(must be: 5)"
				<< std::endl;
	
	std::cout << "st empty:			" 
				<< st.empty() 
				<< "	(must be: false)"
				<< std::endl;

	///////// TEST RELATIONAL OPERATORS ////////////////
	ft::stack<int>	st2;
	std::cout << "\n" 
				<< "st2 empty:			" 
				<< std::boolalpha 
				<< st2.empty() 
				<< "	(must be: true)"
				<< std::endl;

	std::cout << "st == st2:			" 
				<< std::boolalpha
				<< (st == st2) 
				<< "	(must be: false)"
				<< std::endl;

	std::cout << "st != st2:			" 
				<< std::boolalpha
				<< (st != st2) 
				<< "	(must be: true)"
				<< std::endl;

	std::cout << "st < st2:			" 
				<< std::boolalpha
				<< (st < st2) 
				<< "	(must be: false)"
				<< std::endl;

	std::cout << "st > st2:			" 
				<< std::boolalpha
				<< (st > st2) 
				<< "	(must be: true)"
				<< std::endl;

	std::cout << std::endl;
	/////////////////////////////////////////////////////////

	std::cout << "st change top integer x2		{0, 1, 2, 3, 8}" 
				<< std::endl;
	st.top() *= 2;

	std::cout << "Print out st:				{";
	for(int i = 0; i < 5; ++i)
	{
		std::cout << st.top();
		st.pop();
		if (st.size())
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << "}" << std::endl;
		}
	}
}
