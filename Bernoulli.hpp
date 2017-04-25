#ifndef BERNOULLI_HPP
#define BERNOULLI_HPP

#include "nth_prime.hpp"
#include <ratio>
#include <iomanip>

template<unsigned N, unsigned K>
struct BinomialCoeff {
    static const unsigned value = BinomialCoeff<N-1, K-1>::value + BinomialCoeff<N-1, K>::value;  
};

template<unsigned N>
struct BinomialCoeff<N, N> {
    static const unsigned value = 1;
};

template<unsigned N>
struct BinomialCoeff<N, 0> {
    static const unsigned value = 1;
};


template<unsigned N, unsigned K = 1>
struct CalcBernoulli {
    typedef std::ratio_multiply<
                std::ratio<-1, N + 1>,
                std::ratio_multiply<
                    std::ratio<BinomialCoeff<N + 1, K + 1>::value>,
                    typename CalcBernoulli<N-K>::value>> step; 
    typedef conditional_t<N % 2 == 1,
                std::ratio<0>,
                std::ratio_add<
                        step,
                        typename CalcBernoulli<N, K + 1>::value>> value;
};

template<unsigned N>
struct CalcBernoulli<N, N> {
    typedef std::ratio<-1, N + 1> value;
};

template<unsigned N>
struct BernoulliNumber {
    typedef typename CalcBernoulli<N>::value value; 
};

template <>
struct BernoulliNumber<0> {
    typedef std::ratio<1> value;
};

template <>
struct BernoulliNumber<1> {
    typedef std::ratio<-1, 2> value;   
};  


// http://kvant.mccme.ru/1974/06/chisla_bernulli.htm
// point 3 in this article

const unsigned MAGIC_NUMBER = 42;
typedef std::integral_constant<unsigned, 1> IntConst1;


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

template<unsigned I>
struct FindSuitablePrimes<1, I> {
    static const unsigned value = 2; 
    static const FindSuitablePrimes<0, I> next;
};

template<unsigned I>
struct FindSuitablePrimes<0, I> {
    static const unsigned value = 1;
    static const FindSuitablePrimes<0, 0> next;
};

template<unsigned K>
struct FindSuitablePrimes<K, 0> {
    static const unsigned value = 1; 
    static const FindSuitablePrimes<0, 0> next;
};

template<>
struct FindSuitablePrimes<0, 0> {
    static const unsigned value = 1;
};

template<unsigned K, typename SuitablePrime = FindSuitablePrimes<K>>
struct Sum1DivP {
    typedef Sum1DivP<K, decltype (SuitablePrime::next)> prev;
    typedef std::ratio_add<conditional_t<SuitablePrime::value != MAGIC_NUMBER,
                                std::ratio<IntConst1::value, SuitablePrime::value>,
                                std::ratio<0, 1>>,
                            std::ratio<prev::value::num, prev::value::den>> value;
                                                                        
};

template<unsigned K>
struct Sum1DivP<K, const FindSuitablePrimes<K, 1>>{
    typedef std::ratio<1, 2> value;
};

template<unsigned K>
struct Sum1DivP<K, const FindSuitablePrimes<0, 0>>{
    typedef std::ratio<0, 1> value;
};

template<unsigned N>
struct CheckAll {
    typedef std::ratio_add<typename Sum1DivP<N>::value, typename BernoulliNumber<N>::value> sum;
    static const bool value = conditional_t<sum::num % sum::den == 0 || (N != 1 && N % 2 != 0),
                                                std::true_type,
                                                std::false_type>::value;
    static bool print () {
        std::cout << "i: " << N << '\t' 
                  << "Bernoulli number: " << std::right << std::setw (14) << BernoulliNumber<N>::value::num 
                  << '/' << std::left << std::setw (8) << BernoulliNumber<N>::value::den
                  << "Sum(1/p): " << std:: right << std::setw(6) << Sum1DivP<N>::value::num 
                  << '/' <<std::left << std::setw (6) << Sum1DivP<N>::value::den 
                  << "result: " << (value ? "Weakly true" : "strongly false") << std::endl;
        return CheckAll<N-1>::print ();
    }
};

template<>
struct CheckAll<0> {
    static const bool value = true;
    static bool print () {
        std::cout << "i: " << 0 << '\t' 
                  << "Bernoulli number: " << std::right << std::setw (14) << BernoulliNumber<0>::value::num 
                  << '/' << std::left << std::setw (8) << BernoulliNumber<0>::value::den
                  << "Sum(1/p): " << std:: right << std::setw(6) << Sum1DivP<1>::value::num 
                  << '/' <<std::left << std::setw (6) << Sum1DivP<1>::value::den 
                  << "result: " << (value ? "Weakly true" : "strongly false") << std::endl;
        return value;
    }
};

#endif