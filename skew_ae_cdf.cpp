#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"
vector<double> Mv, Fv, Sv;

string FILENAME = "skew_ae_cdf";

void ins(double M, double F, double S) {
    Mv.push_back(M), Fv.push_back(F), Sv.push_back(S);
}

    vector<vector<Result> > res;
int main() {
    
    const int ST = 1, ED = 10, Reality = 0, chara = 0;    //FILE * file;
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
    
    double MEM = 0.5, F = 0.15, S = 4.4;
     {
        MEM_SIZE = (int) (MEM * 8 * 1024 * 1024);
        res.clear();
        sketch.csm = new CSM_Sketch_16bit();
        sketch.cm = new CM_Sketch_16bit();
        sketch.a = new A_Sketch_16bit();
        sketch.c = new C_Sketch_16bit();
        sketch.cu = new CU_Sketch_16bit();
                
        sketch.d = new Diamond_Sketch_4bit_nd(F, S);
        Experiment_Set expr(ST, ED, Reality, 0, 0);
        res.push_back(expr.run(sketch.csm));
        printf("csm done\n");
        res.push_back(expr.run(sketch.cm));
        printf("cm done\n");
        res.push_back(expr.run(sketch.a));
        printf("a done\n");
        res.push_back(expr.run(sketch.c));
        printf("c done\n"); 

        //printf("%f %f \n", res[res.size() - 1][0].re_cdf[2], res[res.size() - 1][0].are);
        
        res.push_back(expr.run(sketch.cu));
        printf("cu done\n"); 

        //printf("%f %f \n", res[res.size() - 1][0].re_cdf[2], res[res.size() - 1][0].are);
        
        res.push_back(expr.run(sketch.d));
        printf("d done\n");
        string path = "x.dat";
        fr = fopen(path.c_str(), "a");
    fprintf(fr, "data number: %d\n", Reality);
    printf("data number: %d\n", Reality);
    printf("step1\n");
    fprintf(fr, "aae_rate");
    for (int i = 0; i < SKETCH_NUMBER; i++)
        fprintf(fr, " %s", sketch_name[i].c_str());
    fprintf(fr, "\n");
    printf("step2\n");
    for (int i = 0; i < AAE_RATE_SIZE; i++) {
        fprintf(fr, "%d", i);
        for (int j = 0; j < res.size(); j++)
            printf("%d %d\n", i, j), fprintf(fr, " %f", res[j][0].aae_rate[i]);
        fprintf(fr, "\n");
    }
}
}
