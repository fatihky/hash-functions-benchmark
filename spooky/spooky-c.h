#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void spooky(const void *data, size_t length, uint64_t *hash1, uint64_t *hash2);

#ifdef __cplusplus
}
#endif