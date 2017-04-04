#include "includes.h"
#include "sketches.h"
#include "Experiment_Set.h"
vector<double> Mv, Fv, Sv;


int main() {
    vector<vector<Result> > res;
    
    const int ST = 1, ED = 10, Reality = 1, chara = 0;   
    string FILENAME = "res";
    FILE *fr;
    
    double MEM = 0.5, F = 0.15, S = 4.4;

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
        res.push_back(expr.run(sketch.cu));
        printf("cu done\n");
        res.push_back(expr.run(sketch.d));
        printf("d done\n");


    vector<int> Goal;
    Goal.push_back(0);
    Goal.push_back(1);
    for (int index = 0; index < Goal.size(); index++) {
        int chara = Goal[index];
        string path = FILENAME + res[0][0].name[chara] + ".dat";
        printf(">> %s\n", path.c_str());
        fr = fopen(path.c_str(), "a");
        fprintf(fr, "ComparisonOf%s", res[0][0].name[chara].c_str());

        for (int i = 0; i < res.size(); ++i)
            fprintf(fr, " %s", sketch_name[i].c_str());
        fprintf(fr, "\n");

        for (int range = ST; range <= ED; range++) {
            fprintf(fr, "%d%%", range * 10);       
                   for (int i = 0; i < res.size(); ++i)
                       fprintf(fr, " %f", res[i][range - ST][chara]);
            fprintf(fr, "\n");
        }  
    }
}
