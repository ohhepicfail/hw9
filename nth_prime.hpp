#ifndef NTH_PRIME_HPP
#define NTH_PRIME_HPP

#include <type_traits>
#include <tuple>
#include <iostream>
#include <array>

// because of metashell >.<
template<bool B, class T, class F>
using conditional_t = typename std::conditional<B, T, F>::type;

template<unsigned X> struct IsPrime;
template<unsigned X, unsigned I> struct IsPrimeHelper;

struct Prime {
    enum { value = true };
};

struct NonPrime {
    enum { value = false };
};

template<unsigned X> struct IsPrime {
    enum { value = conditional_t
            <((X % 2 == 0 && X > 2) || (X % 3 == 0 && X > 3)), 
            NonPrime, 
            conditional_t
                <X <= 3, 
                Prime, 
                IsPrimeHelper<X, 6>>>::value 
    };
};

template<unsigned X, unsigned I> struct IsPrimeHelper {
    enum { 
        value = conditional_t 
                   <(X >= (I - 1)*(I - 1) && X % (I-1) == 0) || ( X >= (I + 1)*(I + 1) && X % (I+1) == 0), 
                   NonPrime , 
                   IsPrimeHelper<X, std::min (X, I + 6)>>::value
    };
};

template<unsigned X> struct IsPrimeHelper<X, X> {
    enum { value = Prime::value };
};

template<unsigned N, unsigned I = 2> 
struct NthPrime {
    enum { value = conditional_t<IsPrime<I>::value,
                NthPrime< N - 1, I + 1>,
                NthPrime< N, I + 1>>::value
    };
};

template<unsigned I> 
struct NthPrime<0, I> {
    enum { value = I - 1 };
};


template<unsigned N, unsigned I = N - 1>
struct FirstNPrimes : FirstNPrimes<N, I - 1> {
    static const unsigned dummy;
};

template<unsigned N>
struct FirstNPrimes<N, 0> {
    static const unsigned dummy;
    static unsigned array[N];
};

template<unsigned N, unsigned I>
const unsigned FirstNPrimes<N, I>::dummy = FirstNPrimes<N, 0>::array[I] = NthPrime<I>::value + 0 * FirstNPrimes<N, I - 1>::dummy;

template<unsigned N>
unsigned FirstNPrimes<N, 0>::array[N];


#endif
