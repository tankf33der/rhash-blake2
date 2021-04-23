#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "blake2.h"		// libb2
#include "blake2b.h"
#include "blake2s.h"


int main(void) {
	uint8_t d[256], out1[64], out2[64];
	int result = 0;

	for(size_t i = 0; i < 256; i++) d[i] = i;


	// blake2s
	for(size_t i = 0; i < 256; i++) {
		blake2s_ctx ctx;

		rhash_blake2s_init(&ctx);
		rhash_blake2s_update(&ctx, d, i);
		rhash_blake2s_final(&ctx, out1);
		blake2s(out2, d, 0, 32, i, 0);
		result |= memcmp(out1, out2, i);
		printf("%d: %lu\n", result, i);
	}

	// blake2b
	for(size_t i = 0; i < 256; i++) {
		blake2b_ctx ctx;

		rhash_blake2b_init(&ctx);
		rhash_blake2b_update(&ctx, d, i);
		rhash_blake2b_final(&ctx, out1);
		blake2b(out2, d, 0, 64, i, 0);
		result |= memcmp(out1, out2, i);
		printf("%d: %lu\n", result, i);
	}

	
	return result;	
}
