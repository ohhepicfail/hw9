#ifndef BERNOULLI_HPP
#define BERNOULLI_HPP

#include "nth_prime.hpp"


const unsigned MAGIC_NUMBER = 42;
const unsigned FIRST_PRIME_NUMBER = 2;


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
	static const unsigned value = conditional_t <SuitablePrime::value != MAGIC_NUMBER,
													SuitablePrime,
													std::integral_constant<unsigned, 0>>::value
									 + conditional_t<(SuitablePrime::value > 2), 
											Sum1DivP<K, decltype (SuitablePrime::next)>,
											std::integral_constant<unsigned, 0>>::value;
																		
};

// template<unsigned K>
// struct Sum1DivP<K, FindSuitablePrimes<K, 1>> {
// 	static const unsigned value = 
// };




// func () {
// 	number = nthprime (0);
// 	for (int i = 1; number <= k + 1; ++i)
// 		number = nthprime (i);
// 	return i - 2;
		
// }

// func () {
// 	if (nthprime (i) <= k + 1)
// 		return func (i + 1);
// 	return i - 1;
// }

// template<unsigned K, unsigned I = >
// struct FindSuitablePrimes {
// 	static const unsigned value = conditional_t<NthPrime<
// };

#endif