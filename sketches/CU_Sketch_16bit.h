#ifndef _CUSketch_16BIT_H
#define _CUSketch_16BIT_H

#include "../includes.h"
#include "BOBHash.h"

class CU_Sketch_16bit {	
private:
	BOBHash bobhash[MAX_HASH_NUM];
	int index[MAX_HASH_NUM];
	unsigned short * counter[MAX_HASH_NUM];
	const int w, d;

public:
	int memory_usage() {
		return w * d * 16;
	}
	void reset() {
		for (int i = 0; i < d; i++) {
			memset(counter[i], 0, sizeof(unsigned short) * w);
		}
	}

	CU_Sketch_16bit(int _w = MEM_SIZE / 16 / HASH_TIME, int _d = HASH_TIME):w(_w),d(_d) {
		for (int i = 0; i < d; i++) {
			counter[i] = new unsigned short[w];
			memset(counter[i], 0, sizeof(unsigned short) * w);
		}

		for (int i = 0; i < d; i++) {
			bobhash[i] = BOBHash(i + 1000);
		}
	}

	void Insert (const char * str) {
		unsigned short min_value = ~0;
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i].run(str, strlen(str))) % w;
			min_value = min(min_value, counter[i][index[i]]);
		}
		if (min_value != (unsigned short)~0)
			for (int i = 0; i < d; ++i)
				if (counter[i][index[i]] == min_value)
					++counter[i][index[i]];
	}

	unsigned short Query (const char *str) {
		unsigned short min_value = ~0;
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i].run(str, strlen(str))) % w;
			min_value = min(min_value, counter[i][index[i]]);
		}
		return (min_value == (unsigned short)~0) ? 0 : min_value;
	}
	~CU_Sketch_16bit() {
		for (int i = 0; i < d; i++)	
			delete [] counter[i];
	}
};
#endif //_CUSketch_16BIT_H
