#include <memory>
#include <iostream>
#include <vector>

int		main()
{
	// std::allocator<int>	A;
	// int	*p = A.allocate(sizeof(int) * 1000000);
	// if (p == nullptr)
	// 	return 1;

	// std::cout << p << std::endl;
	// std::cout << *p << std::endl;

	// A.construct(p, 5);
	// int *ptr = p + sizeof(int);
	// A.construct(ptr, 10);

	// std::cout << p << std::endl;
	// std::cout << *p << std::endl;
	// std::cout << ptr << std::endl;
	// std::cout << *ptr << std::endl;

	// A.destroy(p);
	// A.destroy(ptr);
	// A.deallocate(p, (sizeof(int) * 1000000));

	// return 0;

	std::vector<int> v1;

	std::cout << v1.size() << "//" << v1.capacity() << std::endl;

	for (int i = 0; i < 5; ++i)
	{
		v1.push_back(1);
		std::cout << v1.size() << "//" << v1.capacity() << std::endl;
	}

	return 0;
}
