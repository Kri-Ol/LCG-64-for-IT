
#include "suffix128.hpp"
#include "lcg128.hpp"

constexpr __uint128_t m = 0xdb36357734e34abb0050d0761fcdfc15_u128; // parameters from https://arxiv.org/pdf/2001.05304.pdf, 
                                                                   // factored [5, 23, 229, 11064454130225395449793397439790987]
constexpr __uint128_t c = 0x7_u128; // could be 0x7uLL as mutual prime to m, see prime factors above

constexpr __uint128_t im = 295713064423480201165222953644432290621_u128; // modular inverse from m, using Mathematica ModularInverse[m, 2^128]

constexpr __uint128_t ZERO = 0_u128;
constexpr __uint128_t ONE  = 1_u128;
constexpr __uint128_t MAX  = 0xffffffffffffffffffffffffffffffff_u128;


func lcg128::next(const __uint128_t xi) -> __uint128_t { // direct LCG
    return m*xi + c;
}

func lcg128::inverse(const __uint128_t xp) -> __uint128_t { // inverse LCG, such that ilcq(lcg(q)) == q
    return (xp - c)*im;
}

func lcg128::skip(const __int128_t  ns,
                  const __uint128_t seed) -> __uint128_t
{
    if (ns == ZERO)
        return seed;
        
    // compute positive number of seeds to skip
    __uint128_t nskip = (ns > ZERO) ? __uint128_t(ns) : (MAX - __uint128_t(-ns)) + ONE;

    // The algorithm here to determine the parameters used to skip ahead is
    // described in the paper F. Brown, "Random Number Generation with Arbitrary Stride,"
    // Trans. Am. Nucl. Soc. (Nov. 1994). This algorithm is able to skip ahead in
    // O(log2(N)) operations instead of O(N). It computes parameters
    // M and C which can then be used to find x_N = M*x_0 + C mod 2^M.

    // initialize constants
    __uint128_t mm{ m };  // original multiplicative constant
    __uint128_t cc{ c };  // original additive constant

    __uint128_t m_next{ ONE }; // new effective multiplicative constant
    __uint128_t c_next{ ZERO }; // new effective additive constant

    while (nskip > ZERO)
    {
        if (nskip & ONE) // check least significant bit for being 1
        {
            m_next = m_next * mm;
            c_next = c_next * mm + cc;
        }

        cc = ((mm + ONE) * cc);
        mm = (mm * mm);

        nskip = nskip >> ONE; // shift right, dropping least significant bit
    }

    return (m_next * seed + c_next); // we can now find the new seed
}
