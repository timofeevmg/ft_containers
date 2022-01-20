#include "Vector.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

int _ratio = 10000;

int		main()
{
///////////////////////////////////////////////////////////////////////////////
//                                VECTOR                                     //
///////////////////////////////////////////////////////////////////////////////

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
	ft::vector<std::string> V_str1;
	ft::vector<std::string> V_str2;

	// V_int1.push_back(1);
	// V_int3.push_back(1);
	V_str1.push_back("aa");
	V_str2.push_back("ab");

	// std::cout << "V_int1 == V_int2 :" << std::boolalpha << (V_int1 == V_int2) << std::endl;

	// V_int2.push_back(2);

	// std::cout << "V_int1 == V_int2 :" << std::boolalpha << (V_int1 == V_int2) << std::endl;
	// std::cout << "V_int1 == V_int3 :" << std::boolalpha << (V_int1 == V_int3) << std::endl;
	std::cout << "V_str1 == V_str2 :" << std::boolalpha << (V_str1 == V_str2) << std::endl;

};