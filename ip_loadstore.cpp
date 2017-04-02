#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"
vector<double> Mv, Fv, Sv;

string FILENAME = "ip_loadstore";

void ins(double M, double F, double S) {
    Mv.push_back(M), Fv.push_back(F), Sv.push_back(S);
}

int main() {
    vector<vector<Result> > res;
    
    const int ST = 1, ED = 10, Reality = 47, chara = 0, del = 0;    //FILE * file;
    FILE *fr;
    
    map<double, double> msF, mtF, msS, mtS;
    msF[4] = 0.01, mtF[4] =0.1;
    msF[2] = 0.08, mtF[2] = 0.18;
    msF[1] = 0.08, mtF[1] = 0.2;
    msF[0.5] = 0.15, mtF[0.5] = 0.22;
    
    msS[4] = 5.5, mtS[4]=6.7;
    msS[2] = 4, mtS[2] = 6;
    msS[1] = 4, mtS[1] = 6;
    msS[0.5] = 4, mtS[0.5] = 6;
    double MEM = 0.5, F = 0.15, S = 4.6;    

        MEM_SIZE = (int) (MEM * 8 * 1024 * 1024);
        res.clear();
        sketch.a = new A_Sketch_16bit();
    #if DELETE == 0            
        sketch.d = new Diamond_Sketch_4bit_nd(F, S);
    #elif DELETE == 1
        sketch.del = new Diamond_Sketch_Delete(F, S);
    #endif
    Experiment_Set expr(ST, ED, Reality, DELETE, THROUGHPUT | LOADSTORE);
    
        res.push_back(expr.run(sketch.a));
        printf("a done\n");
    #if DELETE == 0
        res.push_back(expr.run(sketch.d));
    #elif DELETE == 1
        res.push_back(expr.run(sketch.del));
    #endif
        printf("d done\n");


    vector<int> Goal;
#if DELETE == 0
    Goal.push_back(2);
    Goal.push_back(3);
#elif DELETE == 1
    Goal.push_back(4);
#endif
    for (int index = 0; index < Goal.size(); index++) {
        int chara = Goal[index];
        string path = "x.dat";
        printf(">> %s\n", path.c_str());
        fr = fopen(path.c_str(), "a");
        fprintf(fr, "cnt");

        for (int i = 0; i < res.size(); ++i)
            fprintf(fr, " %s", sketch_name[i].c_str());
        fprintf(fr, "\n");
        for (int range = ST; range <= ED; range++) {
            fprintf(fr, "%.1f", range / 10.0);       
                   for (int i = 0; i < res.size(); ++i)
                       fprintf(fr, " %f", res[i][range - ST][chara]);
            fprintf(fr, "\n");
        }  
    }
}
