#include "../../vector.hpp"

#include <iostream>

#include <vector>

int main()
{
	sjtu::vector<long long> v;
	for (long long i = 0; i < 1LL << 20; ++i) {
	    std::cout<<i<<std::endl;
	    if(i==12289)
        {
	        int a=0;
        }
		v.push_back(i);
	}
	std::cout << v.back() << std::endl;
	for (long long i = 0; i < 1LL << 11; ++i) {
		v.insert(v.begin(), i);
	}
	for (size_t i = 0; i < 1LL << 10; ++i) {
		std::cout << v.front() << std::endl;
		v.erase(v.begin());
	}
	return 0;
}