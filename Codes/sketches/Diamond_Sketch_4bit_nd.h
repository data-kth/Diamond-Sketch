#ifndef _Diamond_Sketch_4bit_ND_H
#define _Diamond_Sketch_4bit_ND_H

#include "../includes.h"
#include "CU_Sketch_4bit_O.h"
#include "CU_Sketch_2bit_N.h"

class Diamond_Sketch_4bit_nd
{	
private:
	CU_Sketch_2bit_N * carry;
	CU_Sketch_4bit_O * counting[MAX_SKETCH_HEIGHT]; 
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
	}
	#if	Sequence == G
	Diamond_Sketch_4bit_nd(double carry_ratio, double ratio, int carry_d= CARRY_HASH_TIME, int counting_d=HASH_TIME, int _h=4): h(_h) {
		double carry_total = MEM_SIZE * carry_ratio / (carry_ratio + 1), counting_total = MEM_SIZE - carry_total;
		double deletion_total = MEM_SIZE * 0.2;
		double tot = 1;
		double first_part = 1;
		for (int i = 1; i < h; ++i) {
			first_part *= ratio;
			tot += first_part;
		}
		carry = new CU_Sketch_2bit_N(carry_total / 2 / carry_d, carry_d);
		//deletion = new CU_Sketch_16bit(deletion_total / 16/ carry_d, carry_d);
		int start_prime_num = 1000;
		for (int i = 1; i <= h; ++i) {
			counting[i-1] = new CU_Sketch_4bit_O(counting_total*first_part/tot/counting_d/4, counting_d, start_prime_num);
			first_part /= ratio;
			start_prime_num += counting_d;
		}
	}
#elif Sequence == A
	Diamond_Sketch_4bit_nd(double carry_ratio, double ratio, int carry_d= CARRY_HASH_TIME, int counting_d=HASH_TIME, int _h=4): h(_h) {
		double carry_total = MEM_SIZE * carry_ratio / (carry_ratio + 1), counting_total = MEM_SIZE - carry_total;
		double deletion_total = MEM_SIZE * 0.2;
		double tot = 0;
		double first_part = 1;
		printf("enter A\n");
		for (int i = 1; i < h; ++i) {
			first_part += ratio;
			tot += first_part;
		}
		carry = new CU_Sketch_2bit_N(carry_total / 2 / carry_d, carry_d);
	//	deletion = new CU_Sketch_16bit(deletion_total / 16/ carry_d, carry_d);
		int start_prime_num = 1000;
		for (int i = 1; i <= h; ++i) {
			counting[i-1] = new CU_Sketch_4bit_O(counting_total*first_part/tot/counting_d/4, counting_d, start_prime_num);
			first_part -= ratio;
			start_prime_num += counting_d;
		}
	}

#elif Sequence == Fib
	Diamond_Sketch_4bit_nd(double carry_ratio, double ratio, int carry_d= CARRY_HASH_TIME, int counting_d=HASH_TIME, int _h=4): h(_h) {
		double carry_total = MEM_SIZE * carry_ratio / (carry_ratio + 1), counting_total = MEM_SIZE - carry_total;
		double deletion_total = MEM_SIZE * 0.2;
		double size[h];
		size[0] = 1, size[1] = 1 + ratio;
		double tot = size[0] + size[1];
		printf("Enter Fib\n");
		for (int i = 2; i < h; ++i) {
			size[i] = size[i - 1] + size[i - 2];
			tot += size[i];
		}
		carry = new CU_Sketch_2bit_N(carry_total / 2 / carry_d, carry_d);
	//	deletion = new CU_Sketch_16bit(deletion_total / 16/ carry_d, carry_d);
		int start_prime_num = 1000;
		for (int i = 1; i <= h; ++i) {
			counting[i-1] = new CU_Sketch_4bit_O(counting_total*size[h - i]/tot/counting_d/4, counting_d, start_prime_num);
			start_prime_num += counting_d;
		}
	}
#endif
	
	~Diamond_Sketch_4bit_nd() {
		delete carry;
		for (int i = 0; i < h; ++i) delete counting[i];
	}
	void Insert(const char * str) {
		//printf("%s\n", str);
		int cur = 0;
		while (cur < h && counting[cur]->Insert(str)) ++cur;
		if (cur == h) --cur;
	//	if (cur > 1) cout << "cur " << cur << endl;
		carry->Insert(str, cur);
	}

	int Query(const char *str)
	{
		int pos = carry->Query(str), res = 0;
		while (pos >= 0) {
			res <<= 4;
			res += counting[pos]->Query(str);
		//	if (pos > 0) cout << "Oh yeah!\n";
			--pos;
		}
		//cout << res << endl;
		return res;
	}
};
#endif
