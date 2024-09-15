#pragma once

#include <cstdint>

#ifndef func
    #define func auto
#endif

namespace lcg64
{

func next(const uint64_t xi) -> uint64_t; // direct LCG

func inverse(const uint64_t xp) -> uint64_t; // inverse LCG, such that inverse(next(q)) == q

func skip(const int64_t  dist,
          const uint64_t xi   ) -> uint64_t; // skip by dist, which could be negative

}