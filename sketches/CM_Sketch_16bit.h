#ifndef _CMSketch_16bit_H
#define _CMSketch_16bit_H

#include "../includes.h"
#include "BOBHash.h"

class CM_Sketch_16bit {	
private:
	BOBHash bobhash[MAX_HASH_NUM];
	unsigned short * counter[MAX_HASH_NUM];
	const int w, d;

public:
	int memory_usage() {
		return w * d * 16;
	}
	void reset() {
		for (int i = 0; i < d; i++) {
			memset(counter[i], 0, sizeof(short) * w);
		}
	}
	CM_Sketch_16bit(int _w = MEM_SIZE / 16 / HASH_TIME, int _d = HASH_TIME):w(_w),d(_d)
	{		
		for (int i = 0; i < d; i++) {
			counter[i] = new unsigned short[w];
			memset(counter[i], 0, sizeof(short) * w);
		}

		for (int i = 0; i < d; i++) {
			bobhash[i] = BOBHash(i+1000);
		}
	}

	void Insert(const char * str) {
		for (int i = 0; i < d; ++i) {
			int index = (bobhash[i].run(str, strlen(str))) % w;
			if (counter[i][index] != (unsigned short)~0) 
				++counter[i][index];
		}
	}

	void Insert(const char * str, unsigned short times) {
		for (int i = 0; i < d; ++i) {
			int index = (bobhash[i].run(str, strlen(str))) % w;
			LS++;
			unsigned int after = (unsigned int)counter[i][index] + (unsigned int)times;
			if (after > 0xffff)
				counter[i][index] = 0xffff;
			else
				counter[i][index] = after;
		}
	}

	unsigned short Query(const char *str) {
		unsigned short min_value = ~0;
		for (int i = 0; i < d; i++) {
			int index = (bobhash[i].run(str, strlen(str))) % w;
			LS++;
			min_value = min(min_value, counter[i][index]);
		}
		return min_value;
	}

	void Delete(const char * str) {
		for (int i = 0; i < d; ++i) {
			int index = (bobhash[i].run(str, strlen(str))) % w;
			LS++;
			--counter[i][index];
		}
	}
	~CM_Sketch_16bit()
	{
		for (int i = 0; i < d; i++)	
			delete [] counter[i];
	}
};
// int CM_Sketch::prime_num = 1000;
#endif//_CMSketch_16bit_H
