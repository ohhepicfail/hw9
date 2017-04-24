#ifndef BERNOULLI_HPP
#define BERNOULLI_HPP

#include "nth_prime.hpp"
#include <ratio>


const unsigned MAGIC_NUMBER = 42;
typename std::integral_constant<unsigned, 0> IntConst0;
typename std::integral_constant<unsigned, 1> IntConst1;



template<unsigned K, unsigned I = 0> 
struct FindPrimeNThatLessOrEq {
    static const unsigned value = conditional_t<(NthPrime<I>::value <= K), 
                                                FindPrimeNThatLessOrEq<K, I + 1>, 
                                                std::integral_constant<unsigned, I - 1>>::value;
};  

template<unsigned K, unsigned I = FindPrimeNThatLessOrEq<K + 1>::value>
struct FindSuitablePrimes {
    static const unsigned value = conditional_t<(K % (NthPrime<I>::value - 1) == 0), 
                                            NthPrime<I>,
                                            std::integral_constant<unsigned, MAGIC_NUMBER>>::value;
    static const FindSuitablePrimes<K, I - 1> next;
};

template<unsigned K>
struct FindSuitablePrimes<K, 0> {
    static const unsigned value = 0; 
};


template<unsigned K, typename SuitablePrime = FindSuitablePrimes<K>>
struct Sum1DivP {
    typedef Sum1DivP<K, decltype (SuitablePrime::next)> prev;
    typedef std::ratio_add<conditional_t<SuitablePrime::value != MAGIC_NUMBER,
                                std::ratio<IntConst1, SuitablePrime::value>,
                                std::ratio<0, 1>>,
                                std::ratio<prev::value::num, prev::value::den>> value;
                                                                        
};

template<unsigned K>
struct Sum1DivP<K, const FindSuitablePrimes<K, 1>>{
    typedef std::ratio<1, 2> value;
};


#endif