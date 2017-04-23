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
struct FirstNPrimes {
    static const unsigned value = NthPrime<I>::value;
	FirstNPrimes<N, I - 1> prev;
	template<typename Func>
	bool check (Func func) {
		if (value != func (I))
			return false;
		return prev.check (func);
	}
};

template<unsigned N>
struct FirstNPrimes<N, 0> {
    static const unsigned value = NthPrime<0>::value;
	template<typename Func>
	bool check (Func func) {
		return true;
	}
};


#endif
