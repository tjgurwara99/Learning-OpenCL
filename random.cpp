#include <random>
#include <iostream>

int main()
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<double> distribution(0,1);
	return 0;

}


