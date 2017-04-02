#ifndef _Diamond_Sketch_Delete
#define _Diamond_Sketch_Delete

#include "../includes.h"
#include "CU_Sketch_4bit_O.h"
#include "CU_Sketch_2bit_N.h"

#if DELETE == 1
class Diamond_Sketch_Delete
{	
private:
	CU_Sketch_2bit_N * carry;
	CU_Sketch_4bit_O * counting[MAX_SKETCH_HEIGHT]; 
	CU_Sketch_16bit * deletion;
	const int h;

public:
	int memory_usage() {
		int total = 0;
		total += carry->memory_usage();
		for (int i = 0; i < h; ++i) {
			total += counting[i]->memory_usage();
		}
		return total;
	}
	void reset() {
		carry->reset();
		for (int i = 1; i <= h; ++i) {
			counting[i-1]->reset();
		}
		deletion->reset();
	}
	Diamond_Sketch_Delete(double carry_ratio, double ratio, int carry_d= CARRY_HASH_TIME, int counting_d=HASH_TIME, int _h=4): h(_h) {
		double carry_total = MEM_SIZE * carry_ratio / (carry_ratio + 1), counting_total = MEM_SIZE - carry_total;
		double deletion_total = MEM_SIZE * 2;
		double tot = 1;
		double part[5] = {0};
		part[0] = 1;

#if	Sequence == G
		prinf("enter G\n");
		for (int i = 1; i < h; ++i) {
			part[i] = part[i - 1] * ratio;
			tot += part[i];
		}
#elif Sequence == A
		prinf("enter A\n");
		for (int i = 1; i < h; ++i) {
			part[i] = part[i - 1] + ratio;
			tot += part[i];
		}
#elif Sequence == Fib
		prinf("enter Fib\n");
		part[1] = ratio + 1;
		for (int i = 2; i < h; ++i) {
			part[i] = part[i - 1] + part[i - 2];
			tot += part[i];
		}
#endif

		for (int i = 1; i < h; ++i) {
			first_part *= ratio;
			tot += first_part;
		}
		carry = new CU_Sketch_2bit_N(carry_total / 2 / carry_d, carry_d);
		deletion = new CU_Sketch_16bit(deletion_total / 16/ carry_d, carry_d);
		int start_prime_num = 1000;
		for (int i = 1; i <= h; ++i) {
			counting[i-1] = new CU_Sketch_4bit_O(counting_total*part[h - i]/tot/counting_d/4, counting_d, start_prime_num);
		//	first_part /= ratio;
			start_prime_num += counting_d;
		}
	}
	
	~Diamond_Sketch_Delete() {
		delete carry;
		for (int i = 0; i < h; ++i) delete counting[i];
		delete deletion;
	}
	void Delete(const char * str) {
		deletion->Insert(str);
	}
	void Insert(const char * str) {
		int cur = 0;
		while (cur < h && counting[cur]->Insert(str)) ++cur;
		if (cur == h) --cur;
		carry->Insert(str, cur);
	}

	int Query(const char *str)
	{
		int pos = carry->Query(str), res = 0;
		while (pos >= 0) {
			res <<= 4;
			res += counting[pos]->Query(str);
			--pos;
		}
		res -= deletion->Query(str);
		return res;
	}
};
#endif
#endif
