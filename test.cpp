#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"

int main() {
	vector<vector<Result> > res;
	Experiment_Set expr(1);
	res.push_back(expr.run(sketch.csm));
	res.push_back(expr.run(sketch.cm));
	res.push_back(expr.run(sketch.a));
	res.push_back(expr.run(sketch.c));
	res.push_back(expr.run(sketch.cu));
	res.push_back(expr.run(sketch.d));
	for (int j = 0; j < 8; ++j) {
		printf("========================\n%s\n", Result.name[j].c_str());
		for (int i = 0; i < res.size(); ++i)
			printf("%s : %f\n", sketch.name[i].c_str(), res[i][0][j]);
	}
}
