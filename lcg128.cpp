
#include "suffix128.hpp"
#include "lcg128.hpp"

constexpr __uint128_t m = 0xdb36357734e34abb0050d0761fcdfc15_u128; // parameters from https://arxiv.org/pdf/2001.05304.pdf, 
                                                                   // factored [5, 23, 229, 11064454130225395449793397439790987]
constexpr __uint128_t c = 0x7_u128; // could be 0x7uLL as mutual prime to m, see prime factors above

constexpr __uint128_t im = 295713064423480201165222953644432290621_u128; // modular inverse from m, using Mathematica ModularInverse[m, 2^128]

func lcg128::next(const __uint128_t xi) -> __uint128_t { // direct LCG
    return m*xi + c;
}

func lcg128::inverse(const __uint128_t xp) -> __uint128_t { // inverse LCG, such that ilcq(lcg(q)) == q
    return (xp - c)*im;
}
