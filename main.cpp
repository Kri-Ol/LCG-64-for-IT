#include <limits>

#include <cstdio>
#include <cstdlib>

#include "lcg.hpp"

func main() -> int {
    
    uint64_t xi = 9876103423452345341uLL;
    
    {
        printf("Test 0: inverse\n");
        printf("%llu -> %llu -> %llu\n\n", xi, next(xi), inverse(next(xi)) );
    }
    
    {
        printf("Test 1: skip forward and move\n");
        int64_t dist = 12345LL;
        
        uint64_t zs = skip(dist, xi);
    
        uint64_t z = xi;
        for( auto _ = 0; _ != dist; ++_) {
            z = next(z);
        }

        printf("%llu -> %llu\n\n", zs, z );
    }
    
    {
        printf("Test 2: whole ring forward skip\n");
        auto dist = std::numeric_limits<int64_t>::max();
        
        uint64_t z = xi;
     
        // done in three steps, two 2^{63}-1 steps and then 2    
        z = skip(dist, z);
        z = skip(dist, z);
        z = skip(2LL, z);
        
        printf("%llu -> %llu\n\n", xi, z ); 
    }

    {
        printf("Test 3: 0 skip\n");
        int64_t dist = 0LL;
        
        uint64_t z = xi;
        
        z = skip(dist, z);
        printf("%llu -> %llu\n\n", xi, z );        
    }

    {
        printf("Test 4: skip backward and forward\n");
        int64_t dist = -12345LL;
        
        uint64_t zb = skip(dist, xi);
        
        uint64_t z = skip(abs(dist), zb);
    
        printf("%llu -> %llu -> %llu\n\n", xi, zb, z);
    }
    
    {
        printf("Test 5: skip backward and move forward\n");
        int64_t dist = -12345LL;
        
        uint64_t zb = skip(dist, xi);
        
        uint64_t z = zb;
        for( auto _ = 0; _ != abs(dist); ++_) {
            z = next(z);
        }
    
        printf("%llu -> %llu -> %llu\n\n", xi, zb, z);
    }
    
    {
        printf("Test 6: whole ring skip backward\n");
        auto dist = std::numeric_limits<int64_t>::min();
        
        uint64_t z = xi;
     
        // done in two steps, two -2^{63} steps    
        z = skip(dist, z);
        z = skip(dist, z);
        
        printf("%llu -> %llu\n\n", xi, z ); 
    }
    
    return 0;
}
