#pragma once


namespace lcg128
{

funq next(const __uint128_t xi) -> __uint128_t;    // direct LCG

funq inverse(const __uint128_t xp) -> __uint128_t; // inverse LCG, such that inverse(next(q)) == q

funq skip(const __int128_t  dist,
          const __uint128_t xi   ) -> __uint128_t; // skip by dist, which could be negative

}
