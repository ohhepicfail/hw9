#include "nth_prime.hpp"
#include <iostream>
#include <cmath>
#include <cassert>


bool is_prime_f (unsigned x);
unsigned nth_prime_f (unsigned x);

int main () {
    const unsigned i = 100;
    
    #if 0
    std::cout << "is " << i << " a prime number? " << (IsPrime<i>::value ? "Yes" : "No") << std::endl;
    std::cout << i << "th/nd/rd prime is " << nth_prime_f (i) << "\t" << NthPrime<i>::value << std::endl;
    #endif

    FirstNPrimes<i> fnp;
    auto activate = fnp.dummy;  // This is necessary to activate the calculations
    auto primes = fnp.array;
    for (unsigned j = 1; j < i; j++) {
        auto func_result = nth_prime_f (j);
        std::cout << j + 1 << "th/nd/rd prime number is\t" << primes[j] << '\t' << func_result << std::endl;
        assert (primes[j] == func_result);
    }

    return 0;
}

bool is_prime_f (unsigned x) {
    if (x <= 3)
        return true;
    if (x % 2 == 0 || x % 3 == 0)
        return false;
    for (unsigned i = 6; i-1 <= std::sqrt (x); i += 6)
        if (x % (i-1) == 0 || x % (i+1) == 0)
            return false;
    return true;    
}

unsigned nth_prime_f (unsigned x) {
    if (x == 0)
        return 0;
    for (unsigned i = 2; x > 0; ++i) {
        if (is_prime_f (i))
            --x;
        if (x == 0)
            return i;
    }
}
