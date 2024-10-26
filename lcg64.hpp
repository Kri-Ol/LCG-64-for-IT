#pragma once

#include <cstdint>

namespace lcg64
{

funq next(const uint64_t xi) -> uint64_t; // direct LCG

funq inverse(const uint64_t xp) -> uint64_t; // inverse LCG, such that inverse(next(q)) == q

funq skip(const int64_t  dist,
          const uint64_t xi   ) -> uint64_t; // skip by dist, which could be negative

}