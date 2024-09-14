#pragma once

#include <cstdint>

#define func auto

func next(uint64_t xi) -> uint64_t; // direct LCG

func inverse(uint64_t xp) -> uint64_t; // inverse LCG, such that inverse(next(q)) == q

func skip(int64_t dist, uint64_t xi) -> uint64_t; // skip by dist, which could be negative
