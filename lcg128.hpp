#pragma once

#ifndef func
    #define func auto
#endif

namespace lcg128
{

func next(const __uint128_t xi) -> __uint128_t; // direct LCG

func inverse(const __uint128_t xp) -> __uint128_t; // inverse LCG, such that inverse(next(q)) == q

func skip(const __int128_t  dist,
          const __uint128_t xi   ) -> __uint128_t; // skip by dist, which could be negative

}
