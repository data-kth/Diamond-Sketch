#ifndef _CSketch_16bit_H
#define _CSketch_16bit_H

#include "../includes.h"
#include "BOBHash.h"

class C_Sketch_16bit {
private:
	const int w, d;
	short res[MAX_HASH_NUM];
	BOBHash bobhash[MAX_HASH_NUM<<1];
	short * counter[MAX_HASH_NUM];

public:
	int memory_usage() {
		return w * d * 16;
	}
	void reset() {
		for (int i = 0; i < d; ++i) {
			memset(counter[i], 0, sizeof(short) * w);
		}
	}
	C_Sketch_16bit(int _w = MEM_SIZE / 16 / HASH_TIME, int _d = HASH_TIME):w(_w), d(_d) {
		for (int i = 0; i < d; ++i) {
			counter[i] = new short [w];
			memset(counter[i], 0, sizeof(short) * w);
		}
		for (int i = 0; i < d*2; ++i) {
			bobhash[i] = BOBHash(i+1000);
		}
	}
	void Insert(const char * str) {
		for (int i = 0; i < d; ++i) {
			int index = bobhash[i].run(str, strlen(str)) % w;
			bool neg = (bobhash[i+d].run(str, strlen(str)) % 2) == 0;
			if (neg) {
				if (counter[i][index] != (short)0x8000) {
					--counter[i][index];
				}
			} else {
				if (counter[i][index] != (short)0x7fff) {
					++counter[i][index];
				}
			}
		}
	}
	int Query(const char * str) {
		for (int i = 0; i < d; ++i) {
			int index = bobhash[i].run(str, strlen(str)) % w;
			bool neg = (bobhash[i+d].run(str, strlen(str)) % 2) == 0;
			res[i] = (neg ? -counter[i][index] : counter[i][index]);
		}
		sort(res, res + d);
		return (res[d>>1] + res[(d>>1) - 1])/2;
		if (d&1)
			return res[d>>1];
		else
			return (res[d>>1] + res[(d>>1) - 1])>>1;
	}
	~C_Sketch_16bit() {
		for (int i = 0; i < d; ++i)
			delete [] counter[i];
	}
};

#endif//_CSketch_16bit_H
