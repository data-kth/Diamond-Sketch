#ifndef _ASketch_16bit_H
#define _ASketch_16bit_H

#include "../includes.h"
#include "Hash.h"
#include "CM_Sketch_16bit.h"

class A_Sketch_16bit {	
private:
	struct filter_bucket {
		unsigned short new_count, old_count;
		char str[100];
	};
	CM_Sketch_16bit * sketch;
	filter_bucket * filter;
	const int filter_size;
	int filter_empty_pos = 0;

	int find_element_in_filter(const char* str) {
		for (int i = 0; i < filter_empty_pos; ++i) {
			if (strcmp(str, filter[i].str) == 0) {
				return i;
			}
		}
		return -1;
	}

	int min_element_in_filter() {
		unsigned short min_val = (unsigned short)~0, min_pos = -1;
		for (int i = 0; i < filter_empty_pos; ++i) {
			if (filter[i].new_count < min_val) {
				min_val = filter[i].new_count;
				min_pos = i;
			}
		}
		return min_pos;
	}

public:
	void reset() {
		sketch->reset();
		memset(filter, 0, sizeof(filter_bucket) * filter_size);
	}
	int memory_usage() {
		int total = 0;
		//if (output) printf("filter size : (estimated) %f MB\n", filter_size*64/(8.0*1024*1024));
		total += filter_size * 16 * HASH_TIME;
		total += sketch->memory_usage();
		//if (output) printf("total usage : %f MB\n", total/(8.0*1024*1024));
		return total;
	}
	A_Sketch_16bit (int _w = MEM_SIZE / 16 / HASH_TIME, int _d = HASH_TIME, int _filter_size = FILTER_SIZE):
	filter_size(_filter_size)
	{		
		sketch = new CM_Sketch_16bit(_w, _d);
		filter = new filter_bucket[filter_size];
		memset(filter, 0, sizeof(filter_bucket) * filter_size);
	}

	void Insert(const char * str, int times = 1) {
		int index = find_element_in_filter(str);
		if (index != -1) {
			filter[index].new_count += times;
			return;
		}
		index = filter_empty_pos;
		if (index != filter_size) {
			strcpy(filter[index].str, str);
			filter[index].new_count = times;
			filter[index].old_count = 0;
			++filter_empty_pos;
			return;
		}
		sketch->Insert(str, times);
		index = min_element_in_filter();
		unsigned short estimated_freq = sketch->Query(str);
		if (estimated_freq > filter[index].new_count) {
			unsigned short update = filter[index].new_count - filter[index].old_count;
			if (update > 0) {
				sketch->Insert(filter[index].str, update);
			}
			strcpy(filter[index].str, str);
			filter[index].new_count = estimated_freq;
			filter[index].old_count = estimated_freq;
		}
	}

	unsigned short Query(const char *str) {
		int index = find_element_in_filter(str);
		if (index != -1) {
			return filter[index].new_count;
		}
		return sketch->Query(str);
	}
	~A_Sketch_16bit() {
		delete sketch;
		delete [] filter;
	}
};
#endif//_ASketch_16bit_H
