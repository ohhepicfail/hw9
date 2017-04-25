#include "nth_prime.hpp"
#include "Bernoulli.hpp"
#include <iostream>
#include <cmath>
#include <cassert>


bool is_prime_f (unsigned x);
unsigned nth_prime_f (unsigned x);


int main () {
    const unsigned i = 33;
    
    #if 0
    std::cout << "is " << i << " a prime number? " << (IsPrime<i>::value ? "Yes" : "No") << std::endl;
    std::cout << i << "th/nd/rd prime is " << nth_prime_f (i) << "\t" << NthPrime<i>::value << std::endl;
    #endif

    #ifdef TEST_FNP
    FirstNPrimes<i> fnp;
    assert (fnp.check (nth_prime_f));
    #endif

    #ifdef TEST_BERNOULLI

    CheckAll<i>::print ();
    #endif

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
    unsigned i;
    for (i = 2; x > 0; ++i) 
        if (is_prime_f (i))
            --x;

    return i - 1;
}