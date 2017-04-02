#ifndef _RESULT_H
#define _RESULT_H
#include "includes.h"
struct Result {
    float are, aae, re_cdf[RE_CDF_SIZE], aae_rate[AAE_RATE_SIZE], insert = -1.0, query = -1.0, max_ae, max_re, accuracy, aae_variance, ls;
#if DELETE == 1
    float deletion = -1.0; 
#endif
    static const vector<string> name;// = {"are", "aae", "insert", "query", "max_ae", "max_re", "accuracy", "aae_variance"};
    float operator [] (int pos) {
        switch(pos) {
        case 0: return are;
        case 1: return aae;
        case 2: return insert;
        case 3: return query;
    #if DELETE == 1
        case 4: return deletion;
        case 5: return max_ae;
        case 6: return max_re;
        case 7: return accuracy;
        case 8: return aae_variance;
    #elif DELETE == 0
        case 4: return max_ae;
        case 5: return max_re;
        case 6: return accuracy;
        case 7: return aae_variance;
    #endif
        default: return -1;
        }
    }
    void load(const char* data_path) {
        FILE* file = fopen(data_path, "r");
        fscanf(file, "are : %f\n", &are);
        fscanf(file, "aae : %f\n", &aae);
        fscanf(file, "re_cdf : %f", &re_cdf[0]);
        for (int i = 1; i <= 9; ++i) fscanf(file, " %f", &re_cdf[i]);
        fscanf(file, " %f\n", &re_cdf[10]);
        fscanf(file, "insert : %f Mips\n", &insert);
        fscanf(file, "query : %f Mips\n", &query);
        fscanf(file, "max_ae : %f\n", &max_ae);
        fscanf(file, "max_re : %f\n", &max_re);
        fscanf(file, "accuracy : %f\n", &accuracy);
        fscanf(file, "aae_variance : %f\n", &aae_variance);
        fclose(file);
    }
    void store(const char* data_path) {
        FILE* file = fopen(data_path, "w");
        fprintf(file, "are : %f\n", are);
        fprintf(file, "aae : %f\n", aae);
        fprintf(file, "re_cdf : %f", re_cdf[0]);
        for (int i = 1; i <= 9; ++i) fprintf(file, " %f", re_cdf[i]);
        fprintf(file, " %f\n", re_cdf[10]);
        fprintf(file, "insert : %f Mips\n", insert);
        fprintf(file, "query : %f Mips\n", query);
        fprintf(file, "max_ae : %f\n", max_ae);
        fprintf(file, "max_re : %f\n", max_re);
        fprintf(file, "accuracy : %f\n", accuracy);
        fprintf(file, "aae_variance : %f\n", aae_variance);
        fclose(file);
    }
    void output() {
        printf("are : %f\n", are);
        printf("aae : %f\n", aae);
        printf("re_cdf : %f", re_cdf[0]);
        for (int i = 1; i <= 9; ++i) printf(" %f", re_cdf[i]);
        printf(" %f\n", re_cdf[10]);
        printf("insert : %f Mips\n", insert);
        printf("query : %f Mips\n", query);
        printf("max_ae : %f\n", max_ae);
        printf("max_re : %f\n", max_re);
        printf("accuracy : %f\n", accuracy);
        printf("aae_variance : %f\n", aae_variance);
    }
};
#if DELETE == 1
const vector<string> Result::name = {"ARE", "AAE", "INSERT", "QUERY", "DELETE", "MAX_AE", "MAX_RE", "ACCURACY", "AAE_VARIANCE", "LS"};
#elif DELETE == 0
const vector<string> Result::name = {"ARE", "AAE", "INSERT", "QUERY", "MAX_AE", "MAX_RE", "ACCURACY", "AAE_VARIANCE", "LS"};
#endif
#endif