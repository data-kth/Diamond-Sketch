#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"
vector<double> Mv, Fv, Sv;

string FILENAME = "ip_basic_A";

void ins(double M, double F, double S) {
    Mv.push_back(M), Fv.push_back(F), Sv.push_back(S);
}

int main() {
    vector<vector<Result> > res;
    
    const int ST = 10, ED = 10, Reality = 47, chara = 0;    //FILE * file;
    FILE *fr;
    
    map<double, double> msF, mtF, msS, mtS;
    msF[4] = 0.01, mtF[4] =0.1;
    msF[2] = 0.08, mtF[2] = 0.18;
    msF[1] = 0.08, mtF[1] = 0.2;
    msF[0.5] = 0.10, mtF[0.5] = 1;
    
    msS[4] = 5.5, mtS[4]=6.7;
    msS[2] = 4, mtS[2] = 6;
    msS[1] = 4, mtS[1] = 6;
    msS[0.5] = 4, mtS[0.5] = 6;
    
    double MEM = 0.5;
    for (double F = msF[MEM]; F <= mtF[MEM]; F += 0.1)
        for (double S = msS[MEM]; S <= mtS[MEM]; S+=0.4) {
        MEM_SIZE = (int) (MEM * 8 * 1024 * 1024);
        res.clear();
                
        sketch.d = new Diamond_Sketch_4bit_nd(F, S);
        Experiment_Set expr(ST, ED, Reality, 0, 0);
        res.push_back(expr.run(sketch.d));

    vector<int> Goal;
    Goal.push_back(0);
    Goal.push_back(1);
    printf("%lf %lf\n", F, S);
    for (int index = 0; index < Goal.size(); index++) {
        int chara = Goal[index];
        string path = "x.dat";
        printf(">> %s\n", path.c_str());
        fr = fopen(path.c_str(), "a");
        fprintf(fr, "ComparisonOf%s", res[0][0].name[chara].c_str());

        for (int i = 0; i < res.size(); ++i)
            fprintf(fr, " %s", sketch_name[i].c_str());

        for (int range = ST; range <= ED; range++) {
            fprintf(fr, "%d%%", range * 10);       
                   for (int i = 0; i < res.size(); ++i)
                       fprintf(fr, " %f", res[i][range - ST][chara]);
            fprintf(fr, "\n");
        }  
    }
}
}
