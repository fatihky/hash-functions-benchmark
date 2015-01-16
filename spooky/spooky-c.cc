#include "spooky-c.h"
#include "spooky.cc"

extern "C" {

void spooky(const void *data, size_t length, uint64_t *hash1, uint64_t *hash2)
{
    SpookyHash::Hash128(data, length, hash1, hash2);
}

}