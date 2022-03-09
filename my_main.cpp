#include "Vector.hpp"
#include "Stack.hpp"
#include "Map.hpp"
#include "Set/Set.hpp"
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <iostream>
#include <iomanip>
#include <string>

// #define _RESET   "\033[0m"
// #define _BLACK   "\033[30m"      /* Black */
// #define _RED     "\033[31m"      /* Red */
// #define _GREEN   "\033[32m"      /* Green */
// #define _YELLOW  "\033[33m"      /* Yellow */
// #define _BLUE    "\033[34m"      /* Blue */
// #define _MAGENTA "\033[35m"      /* Magenta */
// #define _CYAN    "\033[36m"      /* Cyan */
// #define _WHITE   "\033[37m"      /* White */

int _ratio = 1000;

int		main()
{
///////////////////////////////////////////////////////////////////////////////
//                                VECTOR                                     //
///////////////////////////////////////////////////////////////////////////////

/**
 * PRINTOUT VECTOR ELEMENTS
 **/

// while (first++ != last)
// 	std::cout << *first << std::endl;

	// std::cout << YELLOW << "---------------VECTOR_TEST-----------------" << std::endl;
	// std::cout << "---------------CONSTRUCTOR-----------------" << RESET << std::endl;
	// std::cout << "creating empty vector v1..." << std::endl;
	// ft::vector<int> v1;
	// std::cout << "v1 size : " << v1.size() << " | v1 capacity : " << v1.capacity() << std::endl;

	// std::cout << std::endl;
	// std::cout << "creating vector v2 with 100 copies of int=5..." << std::endl;
	// ft::vector<int> v2(100, 5);
	// std::cout << "v2 size : " << v2.size() << " | v2 capacity : " << v2.capacity() << std::endl;
	// std::cout << "v2[0] = " << v2[0] << " | v2[99] = " << v2[99] << std::endl;
	
	// std::cout << std::endl;
	// std::cout << "creating vector v3 with 10 elements from another vector..." << std::endl;
	// ft::vector<int> another;
	// for (int i = 0; i < 10; ++i)
	// {
	// 	another.push_back(i);
	// }
	// ft::vector<int>::iterator	itb = another.begin();
	// ft::vector<int>::iterator	ite = another.end();
	// ft::vector<int>	v3(itb, ite);
	// std::cout << "v3 size : " << v3.size() << " | v3 capacity : " << v3.capacity() << std::endl;
	// std::cout << "v3[0] = " << v3[0] << " | v3[9] = " << v3[9] << std::endl;


//INSERT VALUE
	// ft::vector<int> vector;
	// vector.assign(26000000, 1);
	// vector.insert(vector.end() - 8000000, 44);
	// vector.size();
	// vector.capacity();

//SWAP
	// ft::vector<int>	vector;
	// vector.assign(1100 * _ratio, 11);
	// std::cout << "vector:	" << vector[100000] << "|" << vector.size() << "|" << vector.capacity() << std::endl;

	// ft::vector<int> tmp(500 * _ratio, 5);
	// std::cout << "tmp:	" << tmp[100000] << "|" << tmp.size() << "|" << tmp.capacity() << std::endl;

	// ft::vector<int>	tmp2(1000 * _ratio, 10);
	// std::cout << "tmp2:	" << tmp2[100000] << "|" << tmp2.size() << "|" << tmp2.capacity() << std::endl;

	// ft::vector<int>	tmp3(1500 * _ratio, 15);
	// std::cout << "tmp3:	" << tmp3[100000] << "|" << tmp3.size() << "|" << tmp3.capacity() << std::endl;

	// ft::vector<int> tmp4(3000 * _ratio, 30);
	// std::cout << "tmp4:	" << tmp4[100000] << "|" << tmp4.size() << "|" << tmp4.capacity() << std::endl;

	// std::cout << std::endl;

	// vector.swap(tmp);
	// std::cout << "swap(vector/tmp):" << std::endl;
	// std::cout << "vector:	" << vector[100000] << "|" << vector.size() << "|" << vector.capacity() << std::endl;
	// std::cout << "tmp:	" << tmp[100000] << "|" << tmp.size() << "|" << tmp.capacity() << std::endl;

	// std::cout << std::endl;

	// vector.swap(tmp3);
	// std::cout << "swap(vector/tmp3):" << std::endl;
	// std::cout << "vector:	" << vector[100000] << "|" << vector.size() << "|" << vector.capacity() << std::endl;
	// std::cout << "tmp3:	" << tmp3[100000] << "|" << tmp3.size() << "|" << tmp3.capacity() << std::endl;

	// // std::swap(vector, tmp2);

	// // std::swap(vector, tmp4);

// ==
	// ft::vector<int> V_int1;
	// ft::vector<int> V_int2;
	// ft::vector<int> V_int3;

	// V_int1.push_back(1);
	// V_int3.push_back(1);

	// std::cout << "V_int1 == V_int2 :" << std::boolalpha << (V_int1 == V_int2) << std::endl;

	// V_int2.push_back(2);

	// std::cout << "V_int1 == V_int2 :" << std::boolalpha << (V_int1 == V_int2) << std::endl;
	// std::cout << "V_int1 == V_int3 :" << std::boolalpha << (V_int1 == V_int3) << std::endl;

// STACK
	// ft::stack<int>	stk;
	// for (int i = 0; i < 100; ++i)
	// 	stk.push(i);

	// ft::stack<int> stack2(stk);
	// ft::stack<int> stack3;
	// stack3 = stack2;

// MAP
	ft::map<int, int>	mp;

	mp.insert(ft::make_pair(10, 10));
	mp.insert(ft::make_pair(20, 20));
	mp.insert(ft::make_pair(30, 30));
	mp.insert(ft::make_pair(40, 40));
	mp.insert(ft::make_pair(50, 50));
	mp.insert(ft::make_pair(60, 60));

	const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>&	pair = mp.equal_range(10);

	(void)pair;


	// std::map<int, int>	m;
	// m.insert(std::pair<int, int>(1, 100));
	// m.insert(std::pair<int, int>(2, 200));
	// m.insert(std::pair<int, int>(3, 300));
	// m.insert(std::pair<int, int>(4, 400));

	// std::map<int, int>::iterator	it;
	// it = m.lower_bound(10);
	// std::cout << it->first << std::endl;

	return 0;
};