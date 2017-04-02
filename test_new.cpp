#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"
vector<double> Mv, Fv, Sv;

void ins(double M, double F, double S) {
    Mv.push_back(M), Fv.push_back(F), Sv.push_back(S);
}

int main() {
    vector<vector<Result> > res;
    
    const int ST = 10, ED = 10, Reality = 0, chara = 0;    //FILE * file;
    FILE *fr;
    
    map<double, double> msF, mtF, msS, mtS;
    msF[4] = 0.01, mtF[4] =0.1;
    msF[2] = 0.08, mtF[2] = 0.18;
    msF[1] = 0.08, mtF[1] = 0.2;
    msF[0.5] = 0.10, mtF[0.5] = 0.14;
    
    msS[4] = 5.5, mtS[4]=6.7;
    msS[2] = 4, mtS[2] = 6;
    msS[1] = 4, mtS[1] = 6;
    msS[0.5] = 4, mtS[0.5] = 6;
    
    double MEM = 0.5;
#if D_only == 1
    string path = "x.dat";
    printf(">> %s\n", path.c_str());
    fr = fopen(path.c_str(), "a");
    //freopen(path.c_str(), "w", stdout);
#endif
    for (double F = msF[MEM]; F <= mtF[MEM]; F += 0.01)
        for (double S = msS[MEM]; S <= mtS[MEM]; S+=0.1) {
        MEM_SIZE = (int) (MEM * 8 * 1024 * 1024);{
        res.clear();
#if D_only == 0
        sketch.csm = new CSM_Sketch_16bit();
        sketch.cm = new CM_Sketch_16bit();
        sketch.a = new A_Sketch_16bit();
        sketch.c = new C_Sketch_16bit();
        sketch.cu = new CU_Sketch_16bit();
#endif
                
        sketch.d = new Diamond_Sketch_4bit_nd(F, S);
        Experiment_Set expr(ST, ED, Reality, 0, 0);
#if D_only == 0
        res.push_back(expr.run(sketch.csm));
 //       printf("csm done\n");
        res.push_back(expr.run(sketch.cm));
 //       printf("cm done\n");
        res.push_back(expr.run(sketch.a));
 //       printf("a done\n");
        res.push_back(expr.run(sketch.c));
 //       printf("c done\n");
        res.push_back(expr.run(sketch.cu));
 //       printf("cu done\n");
#endif
        res.push_back(expr.run(sketch.d));
#if D_only == 1
    fprintf(fr, "--------\n");
    fprintf(fr, "%f %f %f\n", MEM, F, S);
#endif
    printf("xx");
                printf("%f %f %f\n", MEM, F, S);
#if D_only == 0
    for (int i = 0; i < res.size(); ++i)
        fprintf(fr, " %s", sketch_name[i].c_str());
#endif
    printf("\n");
               for (int range = ST; range <= ED; range++)
                   for (int chara = 0; chara < 2; chara++){
                   //printf("%.1lf", range / 10.0);
                       fprintf(fr, "%s", res[0][0].name[chara].c_str());
                   for (int i = 0; i < res.size(); ++i)
                       fprintf(fr, " %f", res[i][range - ST][chara]);
                   fprintf(fr, "\n");
               }
            }
#if D_only == 0
    fclose(stdout);
#endif
    }
}
