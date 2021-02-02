#pragma once

#include <random>

class RandomGenerator {
public:
	RandomGenerator() = delete;

	static int randomIntBetween(int, int);

private:
	static std::mt19937_64 generator;
};

