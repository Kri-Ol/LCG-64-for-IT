#include <limits>

#include "lcg64.hpp"

constexpr uint64_t m = 0xd1342543de82ef95uLL; // parameters from https://arxiv.org/pdf/2001.05304.pdf, factored [5, 17, 1277, 2908441, 47750621]
constexpr uint64_t c = 0x1uLL; // could be 0x7uLL as mutual prime to m, see prime factors above

constexpr uint64_t im = 6281218453581128637uLL; // modular inverse from m, using Mathematica ModularInverse[m, 2^64]

func lcg64::next(const uint64_t xi) -> uint64_t { // direct LCG
    return m*xi + c;
}

func lcg64::inverse(const uint64_t xp) -> uint64_t { // inverse LCG, such that ilcq(lcg(q)) == q
    return (xp - c)*im;
}

func lcg64::skip(const int64_t  ns,
                 const uint64_t seed) -> uint64_t
{
    if (ns == 0LL)
        return seed;
        
    // compute positive number of seeds to skip
    uint64_t nskip = (ns > 0LL) ? uint64_t(ns) : (std::numeric_limits<uint64_t>::max() - uint64_t(-ns)) + 1uLL;

    // The algorithm here to determine the parameters used to skip ahead is
    // described in the paper F. Brown, "Random Number Generation with Arbitrary Stride,"
    // Trans. Am. Nucl. Soc. (Nov. 1994). This algorithm is able to skip ahead in
    // O(log2(N)) operations instead of O(N). It computes parameters
    // M and C which can then be used to find x_N = M*x_0 + C mod 2^M.

    // initialize constants
    uint64_t mm{ m };  // original multiplicative constant
    uint64_t cc{ c };  // original additive constant

    uint64_t m_next{ 1uLL }; // new effective multiplicative constant
    uint64_t c_next{ 0uLL }; // new effective additive constant

    while (nskip > 0uLL)
    {
        if (nskip & 1uLL) // check least significant bit for being 1
        {
            m_next = m_next * mm;
            c_next = c_next * mm + cc;
        }

        cc = ((mm + 1uLL) * cc);
        mm = (mm * mm);

        nskip = nskip >> 1uLL; // shift right, dropping least significant bit
    }

    return (m_next * seed + c_next); // we can now find the new seed
}
