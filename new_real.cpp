#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

double cal(double x) {
	return x * x;
}

int main() {
	//map<string, int> M;
	map<int, int> M;
	string str;
	freopen("x", "r", stdin);
	//freopen("data_stat.dat", "w", stdout);
	int s;
	while (scanf("%d", &s) != EOF) {
		M[s]++;
	}
	fclose(stdin);
	int cnt = 0, tot = 0, upper = 0, lower = 2147483647, cnt1 = 0;
	//printf("oh yeah %d\n", cnt);
	for (const auto& p: M) 
		if (p.second < 65536) {
		cnt ++;
		tot += p.second;
		if (p.second == 1) cnt1++;
		upper = max(upper, p.second);
		lower = min(lower, p.second);
	}
	//printf("Ah!\n");
	double avg = (tot + 0.0)/ cnt, sqr = 0;
	for (const auto& p: M) {
		sqr += cal(p.second - avg);
	}

	sqr /= tot;
	printf("Min: %d\nMax : %d\nTot: %d\nAvg: %lf\nVar: %lf\nCnt: %d\nCnt1: %d\n", lower, upper, tot, avg, sqr, cnt, cnt1);
	freopen("x", "r", stdin);
	freopen("x", "w", stdout);
	while (scanf("%d", &s) != EOF) 
		if (M[s] < 65536){
			printf("%d\n", s);
		}

}