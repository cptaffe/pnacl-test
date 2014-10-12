// Extra Credit for Data Structures & Algorithms

// Get all prime numbers between a max and zero,
// realloc for larger and smaller numbers, filling
// in all of the positions with prime numbers.

#include <cmath>
#include <cstdlib>
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/var_array_buffer.h"

using namespace std;

pp::Var atkinSievePrimeGen(int32_t min, int32_t max) {
	//Create the various different variables required
	int root = ceil(sqrt(max));
	const int sieve_size = max - (min - 1);
	bool *sieve;
	
	sieve = new bool[sieve_size];

	for (int32_t i = 0; i < sieve_size; i++) {
		sieve[i] = false;
	}

	for (int32_t x = 1; x <= root; x++) {
		for (int32_t y = 1; y <= root; y++) {
			int32_t n = (4 * x * x) + (y * y);
			if (n <= max && n > min && (n % 12 == 1 || n % 12 == 5)) {
					sieve[n - min] ^= true;
			}
			n = (3 * x * x) + (y * y);
			if (n <= max && n > min && n % 12 == 7) {
				if ((n-min) > 0 && (n-min) < (max - min)){
					sieve[n - min] ^= true;
				}
			}
			n = (3 * x * x) - (y * y);
			if (x > y && n <= max && n > min && n % 12 == 11) {
					sieve[n - min] ^= true;
			}
		}
	}

	//Mark all multiples of squares as non-prime
	for (int32_t i = min; i <= root; i++) {
		if (sieve[i - min]) {
			for (int32_t j = i * i; j < max; j += i * i) {
				sieve[j - min] = false;
			}
		}
	}

	int prime_count;
	for (int32_t i = max; i > min; i--) {
		if (sieve[i - min]) {
			prime_count++;
		}
	}

	pp::VarArrayBuffer var_arr = pp::VarArrayBuffer::VarArrayBuffer(sizeof(int32_t) * prime_count);
	int32_t *arr = static_cast<int32_t *>(var_arr.Map());

	if (min <= 3 && max > 3) {arr[1] = 3;}
	if (min <= 2 && max > 2) {arr[0] = 2;}

	int32_t index = 2;
	for (int32_t i = 0; i < max - 2; i++) {
		if (sieve[i - min]) {
			arr[index++] = i;
		}
	}


	// free array
	delete[] sieve;

	return pp::Var(var_arr);
}

pp::Var calc(int32_t num) {
	//int32_t num = 2147483647;
	try {
		return atkinSievePrimeGen(0, num);
	} catch (...) {
		return pp::Var("prime calculation failed");
	}
}