#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#include "superfasthash.c"
#include "xxHash/xxhash.h"
#include "fnv.c"
#include "tommyds-2.0/tommyds/tommyhash.c"
#include "spooky/spooky-c.h"

// gcc bench.c xxHash/xxhash.c spooky/spooky-c.o --std=c99

static long long mstime(void) {
    struct timeval tv;
    long long mst;

    gettimeofday(&tv, NULL);
    mst = ((long long)tv.tv_sec)*1000;
    mst += tv.tv_usec/1000;
    return mst;
}

int main(int argc, char *argv[]) {
    long long t = mstime();
    const char *data = "duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,duygu,";
    for(int i = 0; i < 1000000; i++)
        SuperFastHash (data, 120);
    t = mstime() - t;
    printf("SuperFastHash: %lld mb/sec\n", ((1000000LL * 1000LL / t) * 120) / (1024 * 1024));

    t = mstime();
    for(int i = 0; i < 1000000; i++)
        XXH32(data, 120, (unsigned)274);
    t = mstime() - t;
    printf("XXH32: %lld mb/sec\n", ((1000000LL * 1000LL / t) * 120) / (1024 * 1024));

    t = mstime();
    unsigned long long xx_last = 0;
    for(int i = 0; i < 1000000; i++)
        xx_last = XXH64(data, 120, xx_last);
    t = mstime() - t;
    printf("XXH64: %lld mb/sec\n", ((1000000LL * 1000LL / t) * 120) / (1024 * 1024));

    t = mstime();
    Fnv64_t fnv_last = 0;
    for(int i = 0; i < 1000000; i++)
        fnv_last = fnv_64a_buf((void *)data, 120, fnv_last);
    t = mstime() - t;
    printf("fnv_64a_buf: %lld mb/sec\n", ((1000000LL * 1000LL / t) * 120) / (1024 * 1024));

    t = mstime();
    for(int i = 0; i < 1000000; i++)
        tommy_hash_u64(274, (const void *)data, 120);
    t = mstime() - t;
    printf("tommy_hash_u64: %lld mb/sec\n", ((1000000LL * 1000LL / t) * 120) / (1024 * 1024));

    t = mstime();
    uint64_t hash1, hash2;
    for(int i = 0; i < 1000000; i++)
        spooky((const void *)data, 120, &hash1, &hash2);
    t = mstime() - t;
    printf("spooky: %lld mb/sec\n", ((1000000LL * 1000LL / t) * 120) / (1024 * 1024));

    return 0;
}