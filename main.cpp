#include <limits>

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "lcg64.hpp"
#include "lcg128.hpp"

#include "suffix128.hpp"

inline funq u01(uint64_t x) -> double {
    return double(x >> 11) * 0x1.0p-53;
}

funq main() -> int {
        
    uint64_t xi = 9876103423452345341uLL;
    
    {
        printf("Test 0: inverse\n");
        printf("%llu -> %llu -> %llu\n\n", xi, lcg64::next(xi), lcg64::inverse(lcg64::next(xi)) );
    }
    
    {
        printf("Test 1: skip forward and move\n");
        int64_t dist = 12345LL;
        
        uint64_t zs = lcg64::skip(dist, xi);
    
        uint64_t z = xi;
        for( auto _ = 0; _ != dist; ++_) {
            z = lcg64::next(z);
        }

        printf("%llu -> %llu\n\n", zs, z );
    }
    
    {
        printf("Test 2: whole ring forward skip\n");
        auto dist = std::numeric_limits<int64_t>::max();
        
        uint64_t z = xi;
     
        // done in three steps, two 2^{63}-1 steps and then 2    
        z = lcg64::skip(dist, z);
        z = lcg64::skip(dist, z);
        z = lcg64::skip(2LL, z);
        
        printf("%llu -> %llu\n\n", xi, z ); 
    }

    {
        printf("Test 3: 0 skip\n");
        int64_t dist = 0LL;
        
        uint64_t z = xi;
        
        z = lcg64::skip(dist, z);
        printf("%llu -> %llu\n\n", xi, z );        
    }

    {
        printf("Test 4: skip backward and forward\n");
        int64_t dist = -12345LL;
        
        uint64_t zb = lcg64::skip(dist, xi);
        
        uint64_t z = lcg64::skip(abs(dist), zb);
    
        printf("%llu -> %llu -> %llu\n\n", xi, zb, z);
    }
    
    {
        printf("Test 5: skip backward and move forward\n");
        int64_t dist = -12345LL;
        
        uint64_t zb = lcg64::skip(dist, xi);
        
        uint64_t z = zb;
        for( auto _ = 0; _ != abs(dist); ++_) {
            z = lcg64::next(z);
        }
    
        printf("%llu -> %llu -> %llu\n\n", xi, zb, z);
    }
    
    {
        printf("Test 6: whole ring skip backward\n");
        auto dist = std::numeric_limits<int64_t>::min();
        
        uint64_t z = xi;
     
        // done in two steps, two -2^{63} steps    
        z = lcg64::skip(dist, z);
        z = lcg64::skip(dist, z);
        
        printf("%llu -> %llu\n\n", xi, z ); 
    }
    
    {
        printf("Test 7: 128 inverse\n");
        printf("%llu -> %llu -> %llu\n\n", xi, uint64_t(lcg128::next(xi)), uint64_t(lcg128::inverse(lcg128::next(xi))) );
    }    
    
    {
        printf("Test 8: 128 skip forward and move\n");
        int64_t dist = 12345LL;
        
        __uint128_t zs = lcg128::skip(__int128_t(dist), xi);
    
        __uint128_t z = xi;
        for( auto _ = 0; _ != dist; ++_) {
            z = lcg128::next(z);
        }

        printf("%llu\n\n", uint64_t(zs == z) );
    }
    
    {
        printf("Test 9: 128 whole ring forward skip\n");
        auto dist = 0x7fffffff'ffffffff'ffffffff'ffffffff_128;
        
        __uint128_t z{xi};
     
        // done in three steps, two 2^{128}-1 steps and then 2    
        z = lcg128::skip(dist, z);
        z = lcg128::skip(dist, z);
        z = lcg128::skip(__int128_t{2}, z);
        
        printf("%llu -> %llu\n\n", xi, uint64_t(z) ); 
    }
    
    {
        printf("Test 10: whole ring skip backward\n");
        auto dist = -0x7fffffff'ffffffff'ffffffff'ffffffff_128 - 1;
        
        __uint128_t z{xi};
     
        // done in two steps, two -2^{128} steps    
        z = lcg128::skip(dist, z);
        z = lcg128::skip(dist, z);
        
        printf("%llu -> %llu\n\n", xi, uint64_t(z) ); 
    }
    
    return 0;
}
