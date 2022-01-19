#include "Vector.hpp"
#include <iostream>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

int		main()
{
///////////////////////////////////////////////////////////////////////////////
//                                VECTOR                                     //
///////////////////////////////////////////////////////////////////////////////

	std::cout << YELLOW << "---------------VECTOR_TEST-----------------" << std::endl;
	std::cout << "---------------CONSTRUCTOR-----------------" << RESET << std::endl;
	std::cout << "creating empty vector v1..." << std::endl;
	ft::vector<int> v1;
	std::cout << "v1 size : " << v1.size() << " | v1 capacity : " << v1.capacity() << std::endl;

	std::cout << std::endl;
	std::cout << "creating vector v2 with 100 copies of int=5..." << std::endl;
	ft::vector<int> v2(100, 5);
	std::cout << "v2 size : " << v2.size() << " | v2 capacity : " << v2.capacity() << std::endl;
	std::cout << "v2[0] = " << v2[0] << " | v2[99] = " << v2[99] << std::endl;
	
	std::cout << std::endl;
	std::cout << "creating vector v3 with 10 elements from another vector..." << std::endl;
	ft::vector<int> another;
	for (int i = 0; i < 10; ++i)
	{
		another.push_back(i);
	}
	ft::vector<int>::iterator	itb = another.begin();
	ft::vector<int>::iterator	ite = another.end();
	ft::vector<int>	v3(itb, ite);
	std::cout << "v3 size : " << v3.size() << " | v3 capacity : " << v3.capacity() << std::endl;
	std::cout << "v3[0] = " << v3[0] << " | v3[9] = " << v3[9] << std::endl;

	ft::vector<int> tmp0;
	ft::vector<int> tmp(10000000, 4), tmp2(10000000, 5);
	tmp = tmp2;
	ft::vector<int> tmp3(tmp);
	ft::vector<int> tmp4(tmp.begin(), tmp.end());
	ft::vector<int> v4(-1, -1);

};