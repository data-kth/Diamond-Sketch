#ifndef _CUSketch_4BIT_O_H
#define _CUSketch_4BIT_O_H

#include "../includes.h"
#include "BOBHash.h"

class CU_Sketch_4bit_O {	
private:
	BOBHash bobhash[MAX_HASH_NUM];
	int index[MAX_HASH_NUM];
	unsigned char * counter[MAX_HASH_NUM];
	const int w, d;

public:
	int memory_usage() {
		return w * d * 4;
	}
	void reset() {
		for (int i = 0; i < d; i++) {
			memset(counter[i], 0, sizeof(unsigned char) * w);
		}
	}
	CU_Sketch_4bit_O(int _w, int _d, int start_prime_num):w(_w),d(_d) {
		for (int i = 0; i < d; i++) {
			counter[i] = new unsigned char[w];
			memset(counter[i], 0, sizeof(unsigned char) * w);
		}

		for (int i = 0; i < d; i++) {
			bobhash[i] = BOBHash(i + start_prime_num);
		}
	}

	bool Insert (const char * str) {
		unsigned char min_value = 15;
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i].run(str, strlen(str))) % w;
			LS++;
			min_value = min(min_value, counter[i][index[i]]);
		}
		if (min_value != 15) {
			for (int i = 0; i < d; ++i)
				if (counter[i][index[i]] == min_value)
					++counter[i][index[i]];
			return false;
		}
		for (int i = 0; i < d; ++i)
			counter[i][index[i]] = 0;
		return true;
	}

	unsigned char Query (const char *str) {
		unsigned char min_value = 15;
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i].run(str, strlen(str))) % w;
			LS++;
			min_value = min(min_value, counter[i][index[i]]);
		}
		return min_value;
	}
	~CU_Sketch_4bit_O() {
		for (int i = 0; i < d; i++)	
			delete [] counter[i];
	}
};
#endif //_CUSketch_8BIT_O_H