#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main() {
	freopen("x.dat", "r", stdin);
	freopen("x.csv", "w", stdout);
	printf("carry_ratio,ratio,are,aae\n");
	char heihei[100];
	vector<double> mem, F, S, are, aae;
	map<pair<double, double>, double > Mare, Maae;
	set<double> sS, sF;
	while (scanf("--------\n") != EOF) {
		double x, y, z;
		scanf("%lf%lf%lf\n", &x, &y, &z);
		mem.push_back(x), F.push_back(y), S.push_back(z);
		sF.insert(y), sS.insert(z);
		//printf("%f,%f,", y, z);
		scanf("are %lf\n", &x);
		are.push_back(x);
		Mare[make_pair(y, z)] = x;
		//printf("%f,",x);
		scanf("aae %lf\n", &x);
		aae.push_back(x);
		Maae[make_pair(y, z)] = x;
		//printf("%f %f %f\n", x, y, z);
	}
	for (int i = 0; i < mem.size(); i++){
		printf("%lf,%lf,%lf,%lf\n", F[i], S[i], are[i], aae[i]);
	}
	freopen("x.csv", "w", stdout);
	//printf("0");
	for (const auto& p : sF)
		printf(",%lf", p);
	printf("\n");
	for (const auto& S : sS) {
		printf("%lf", S);
		for (const auto& F : sF)
			printf(",%lf", Maae[make_pair(F, S)]);
		printf("\n");
	}


	freopen("x.csv", "w", stdout);
	//printf("0");
	for (const auto& p : sF)
		printf(",%lf", p);
	printf("\n");
	for (const auto& S : sS) {
		printf("%lf", S);
		for (const auto& F : sF)
			printf(",%lf", Mare[make_pair(F, S)]);
		printf("\n");
	}
}