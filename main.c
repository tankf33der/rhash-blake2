#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "blake2.h"		// libb2
#include "blake2b.h"
#include "blake2s.h"

void print_vector(const uint8_t *buf, size_t size)
{
    for(size_t i = 0; i < size; i++) {
        printf("%02x", buf[i]);
    }
    printf(":\n");
}

int main(void) {
	uint8_t d[256], out1[64], out2[64];
	int result = 0;

	for(size_t i = 0; i < 256; i++) d[i] = i;

/*
	blake2s_ctx ctx;
	rhash_blake2s_init(&ctx);
	rhash_blake2s_update(&ctx, d, 0);
	rhash_blake2s_final(&ctx, out1);
	// OK - 69217a3079908094e11121d042354a7c1f55b6482ca1a51e1b250dfd1ed0eef9
	print_vector(out1, 32);
	
	rhash_blake2s_init(&ctx);
	rhash_blake2s_update(&ctx, d, 33);
	rhash_blake2s_final(&ctx, out1);
	// OK - a742f8b6af82d8a6ca2357c5f1cf91defbd066267d75c048b352366585025962
	print_vector(out1, 32);
*/

	// blake2s
	for(size_t i = 0; i < 256; i++) {
		blake2s_ctx ctx;

		rhash_blake2s_init(&ctx);
		rhash_blake2s_update(&ctx, d, i);
		rhash_blake2s_final(&ctx, out1);
		blake2s(out2, d, 0, 32, i, 0);
		result |= memcmp(out1, out2, 32);
	}

	// blake2b
	for(size_t i = 0; i < 256; i++) {
		blake2b_ctx ctx;

		rhash_blake2b_init(&ctx);
		rhash_blake2b_update(&ctx, d, i);
		rhash_blake2b_final(&ctx, out1);
		blake2b(out2, d, 0, 64, i, 0);
		result |= memcmp(out1, out2, 32);
	}
	return result;	
}
