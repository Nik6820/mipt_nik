#include <chrono>
#include <random>
#include <iostream>


int rand_uns(int min, int max) {
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

int main(){
    std::cout<<rand_uns(0,3);
}
