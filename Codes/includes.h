#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstring>
#include <climits>
#include <time.h>
#include <vector>
#include <chrono>
#include <map>
#include <set>

using namespace std;

typedef unsigned int uint;
typedef unsigned long int u4;
typedef unsigned char u1;
typedef std::chrono::high_resolution_clock clock_;
typedef std::chrono::duration<float, std::milli> mil;

// for BOBHash
#define MAX_PRIME 1229
#define MAX_BIG_PRIME 50
#define HASH_TIME 4
#define CARRY_HASH_TIME 2

#define DELETE 0
#define THROUGHPUT 0
#define LOADSTORE 0

#define RE_CDF_SIZE 11
#define AAE_RATE_SIZE 11

// for sketches
#define MAX_HASH_NUM 20
#define MAX_SKETCH_HEIGHT 16 // for diamond sketch
#define FILTER_SIZE 32 // for A Sketch

#define SKETCH_NUMBER 6

#define D_only 0

#define A 0
#define G 1
#define Fib 2

#define Sequence G

// for memory
//#define MEM_SIZE 8 * 1024 * 1024

int LS = 0;

int MEM_SIZE = 0;
int HASH_TYPE = 1;

// file pathes
string dataset_path(int dataset_id) {
	if (dataset_id <= 10) return "ip_trace.dat";
	//if (dataset_id <= 100) return "ip_strace.dat";
	return "error";
}
/*
string result_path(int dataset_id, int sketch_id) {
	return "x.dat";
}
string figure_path(string figure_name) {
	return "x.dat";
}
*/
string sketch_name[SKETCH_NUMBER] = { "CSM", "CM", "A", "C", "CU", "D" };

#endif
