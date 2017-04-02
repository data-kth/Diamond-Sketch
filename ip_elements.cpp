#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"
vector<double> Mv, Fv, Sv;

string FILENAME = "ip_elements";
FILE *fr;

void ins(double M, double F, double S) {
    Mv.push_back(M), Fv.push_back(F), Sv.push_back(S);
}

    vector<vector<Result> > res;
int main() {
    
    const int ST = 10, ED = 10, Reality = 47, chara = 0;    //FILE * file;
    
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

        MEM_SIZE = (int) (MEM * 8 * 1024 * 1024);
        res.clear();
        sketch.csm = new CSM_Sketch_16bit();
        sketch.cm = new CM_Sketch_16bit();
        sketch.a = new A_Sketch_16bit();
        sketch.c = new C_Sketch_16bit();
        sketch.cu = new CU_Sketch_16bit();
                
        string path = "x.dat";
        fr = fopen(path.c_str(), "a");


        sketch.d = new Diamond_Sketch_4bit_nd(F, S);
        Experiment_Set expr(ST, ED, Reality, 0, 0);

        fprintf(fr, "d\naae are accuracy re_cdf1~10\n");
        fflush(fr);
        res.push_back(expr.run(sketch.d));
        printf("d done\n");
        fprintf(fr, "--------------------------\n");
        fflush(fr);
}
