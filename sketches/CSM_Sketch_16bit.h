#ifndef _CSMketch_16bit_H
#define _CSMketch_16bit_H

#include "../includes.h"
#include "BOBHash.h"

class CSM_Sketch_16bit {
private:
	const int w, d;
	unsigned short * counter[MAX_HASH_NUM];
	int total_num = 0;
	BOBHash bobhash[MAX_HASH_NUM];

public:
	int memory_usage() {
		return w * d * 16;
	}
	void reset() {
		for (int i = 0; i < d; ++i) {
			memset(counter[i], 0, sizeof(short) * w);
		}
	}
	CSM_Sketch_16bit(int _w = MEM_SIZE / 16 / HASH_TIME, int _d = HASH_TIME):w(_w),d(_d) {
		srand(time(0));
		for (int i = 0; i < d; ++i) {
			counter[i] = new unsigned short [w];
			memset(counter[i], 0, sizeof(short) * w);
		}
		for (int i = 0; i < d; ++i) {
			bobhash[i] = BOBHash(i+1000);
		}
	}
	void Insert(const char * str) {
		int i = rand() % d;
		int index = bobhash[i].run(str, strlen(str)) % w;
		if (~counter[i][index]) {
			++counter[i][index];
			++total_num;
		}
	}
	int Query(const char * str) {
		int res = 0;
		for (int i = 0; i < d; ++i) {
			int index = bobhash[i].run(str, strlen(str)) % w;
			res += (unsigned int)counter[i][index];
		}
		return res - total_num / w;
	}
	~CSM_Sketch_16bit() {
		for (int i = 0; i < d; ++i) {
			delete [] counter[i];
		}
	}
};

#endif//_CSMketch_16bit_H
