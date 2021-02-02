#include "RandomGenerator.h"

std::mt19937_64 RandomGenerator::generator(std::chrono::system_clock::now().time_since_epoch().count());

int RandomGenerator::randomIntBetween(int min, int max) {
	return (max < min) ? 0 : (RandomGenerator::generator() % ((max - min) + 1) + min);
}
