#ifndef _CUSketch_2BIT_N_H
#define _CUSketch_2BIT_N_H

#include "../includes.h"
#include "Hash.h"

class CU_Sketch_2bit_N {	
private:
	Hash hash[MAX_HASH_NUM];
	int index[MAX_HASH_NUM];
	unsigned char * counter[MAX_HASH_NUM];
	const int w, d;

public:
	int memory_usage() {
		return w * d * 2;
	}
	void reset() {
		for (int i = 0; i < d; i++) {
			memset(counter[i], 0, sizeof(unsigned char) * w);
		}
	}
	CU_Sketch_2bit_N(int _w, int _d):w(_w),d(_d) {
		for (int i = 0; i < d; i++) {
			counter[i] = new unsigned char[w];
			memset(counter[i], 0, sizeof(unsigned char) * w);
		}

		for (int i = 0; i < d; i++) {
			hash[i] = Hash(i + 1000);
		}
	}
	/*
	void Insert (const char * str) {
		unsigned char min_value = 3;
		for (int i = 0; i < d; i++) {
			index[i] = (bobhash[i].run(str, strlen(str))) % w;
			min_value = min(min_value, counter[i][index[i]]);
		}
		//if (min_value != 15)
		for (int i = 0; i < d; ++i)
			if (counter[i][index[i]] == min_value)
				++counter[i][index[i]];
	}*/

	void Insert (const char * str, int to_num) {
		//if (to_num >= 2) cout << "to_num=" << to_num << endl;
		for (int i = 0; i < d; i++) {
			int index = (hash[i].run(str, strlen(str), HASH_TYPE)) % w;
			LS++;
			counter[i][index] = max(counter[i][index], (unsigned char)to_num);
		}
	}

	unsigned char Query (const char *str) {
		unsigned char min_value = 3;
		for (int i = 0; i < d; i++) {
			index[i] = (hash[i].run(str, strlen(str), HASH_TYPE)) % w;
			LS++;
			min_value = min(min_value, counter[i][index[i]]);
		}
		return min_value;
	}
	~CU_Sketch_2bit_N() {
		for (int i = 0; i < d; i++)	
			delete [] counter[i];
	}
};
#endif //_CUSketch_2BIT_N_H
