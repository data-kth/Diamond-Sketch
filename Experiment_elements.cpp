#ifndef _EXPERIMENT_H
#define _EXPERIMENT_ELEMENTS_H
#include "includes.h"
#include "File_Reader.h"
#include "Result.h"

class Element {
private:
    set<pair<int, string> > S;

    public:
    map<string, int> cnt;
    map<string, double> are, aae, accuracy;
    map<pair<string, int>, double> re_cdf;
    void    clear() {
        cnt.clear();
        are.clear();
        aae.clear();
        accuracy.clear();
    }

    void    print() {

        for (const auto& p: cnt) 
            if (p.second) {
                S.insert(make_pair<p -> second, p -> first>);
            }

        for (const auto& p: S) {
            string str = p -> second;
            fprintf(fr, "%s ", str.c_str());
            fprintf(fr, "%f ", aae[str]);
            fprintf(fr, "%f ", are[str]);
            fprintf(fr, "%f ", accuracy[str]);
            for (int i = 0; i < RE_CDF_SIZE; ++i) 
                fpintf()
            fprintf(fr, "\n");
        }
    }
}
class Experiment {
private:
    vector<string> input;
    vector<string> uniqued;
    #if DELETE == 1
    vector<string> deletion;
    #endif
    vector<string> read_strings(int dataset_id, int reality) {
        File_Reader file_reader = File_Reader(dataset_path(reality ? reality : dataset_id));
        char str[100];
        vector<string> res;
        while (file_reader.getString(str)) {
            res.push_back(str);
        }
      
        if (reality) {
            return vector<string>(res.begin(), res.begin() + (res.size()) * dataset_id / 10 );
        }
       
        return res;
    }
    #if DELETE == 1
    vector<string> delete_strings(int dataset_id, int reality) {
        File_Reader file_reader = File_Reader(dataset_path(reality ? reality : dataset_id));
        char str[100];
        vector<string> res;
        while (file_reader.getString(str)) {
            res.push_back(str);
        }

        return vector<string>(res.end() - res.size() * dataset_id / 10 , res.end());
    }
    #endif
    vector<string> unique_input() {
        set<string> s;
        for (string str: input) {
            s.insert(str);
        }
        vector<string> res;
        for (string str: s) {
            res.push_back(str);
        }
        return res;
    }
    inline double diff(timespec start, timespec end) {
        timespec temp;
        if ((end.tv_nsec-start.tv_nsec) < 0) {
            tecnt.tv_sec = end.tv_sec-start.tv_sec-1;
            tecnt.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
        } else {
            tecnt.tv_sec = end.tv_sec-start.tv_sec;
            tecnt.tv_nsec = end.tv_nsec-start.tv_nsec;
        }
        return (double)tecnt.tv_nsec + (double)tecnt.tv_sec*1000000000;
    }
public:
    Result res;
    Experiment(int insert_id, int delete_id, int reality) {
        input = read_strings(insert_id, reality);
        uniqued = unique_input();

    #if DELETE == 1
        deletion = delete_strings(delete_id, reality);
   //     printf("%d %lu\n", delete_id, deletion.size());
    #endif
    }
    template<typename T>
    Experiment& error(T& sketch) {
        double are = 0, aae = 0, re_cdf[RE_CDF_SIZE] = { 0 }, max_ae = 0, max_re = 0, accuracy = 0, aae_2 = 0;
        Element * E = new Element;
        E -> clear();
        char str[100];
        sketch -> reset();

        for (const auto& str: uniqued) {
            ++E -> cnt[str];
            sketch -> Insert(str.c_str());
        }
    #if DELETE == 1
        for (const auto& str: deletion) {
            --cnt[str];
            sketch -> Delete(str.c_str());
        }
    #endif
        for (const auto& p: E -> cnt) 
            if (p.second) {
            string str = p.first;
            int real_val = p.second;
            int esti_val = sketch -> Query(p.first.c_str());
            double ae = abs(esti_val - real_val);
            double re = ae / real_val;
            max_re = max(max_re, re);
            max_ae = max(max_ae, ae);
            if (real_val == esti_val) ++accuracy;
            are += re;
            aae += ae;
            aae_2 += ae*ae;
            for (int i = 0; i < RE_CDF_SIZE; ++i)
                if (re <= i)
                    re_cdf[i] += 1.0;
            E -> are[str] = are / p.second;
            E -> aae[str] = aae / p.second;
            for (int i = 0; i < RE_CDF_SIZE; ++i)
                if (re <= i)
                    E -> re_cdf[make_pair(str, i)] += 1.0 / p.second;
        }
        E -> print();
        are /= cnt.size();
        aae /= cnt.size();
        accuracy /= cnt.size();
        for (int i = 0; i <= RE_CDF_SIZE; ++i) 
            re_cdf[i] /= cnt.size();
        res.are = are;
        res.aae = aae;
        res.max_ae = max_ae;
        res.max_re = max_re;
        res.accuracy = accuracy;
        res.aae_variance = aae_2/cnt.size() - aae*aae;
        for (int i = 0; i < RE_CDF_SIZE; ++i) res.re_cdf[i] = re_cdf[i];
        return *this;
    }
    template<typename T>
    Experiment& speed(T& sketch) {
      //  timespec time1, time2;
        
       // double duration = 0.0;
        
  /*      
        double duration_test = 0.0;
        for (int i = 0; i < 10; ++i) {
            sketch.reset();
         //   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
            auto t0 = clock_::now();
            
            for (const string &str: input) {
                sketch.Insert(str.c_str());
            }
         //   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
            auto t1 = clock_::now();
         //   duration += diff(time1, time2);
            duration_test += mil(t1 - t0).count();
        }
        res.insert = input.size()*10000.0/duration_test;
        
        sketch.reset();
        for (const string &str: input) {
            sketch.Insert(str.c_str());
        }
        
        int prevent_opt = 0;
        //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
        auto t0 = clock_::now();
        for (int i = 0; i < 100; ++i) {
            for (const string &str: uniqued) {
                prevent_opt += sketch.Query(str.c_str());
            }
        }
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        auto t1 = clock_::now();
        //duration = diff(time1, time2);
        duration_test = mil(t1 -t0).count();
        res.query = uniqued.size()*100000.0/duration_test;
        printf("%d\n", prevent_opt);
       */ 

        int TEST_TIMES = 10;
        double duration_insert = 0, duration_query = 0, duration_delete = 0, prevent_opt;
        int ls = 0;
        for (int i = 0; i < TEST_TIMES; i++) {
            sketch -> reset();

        #if THROUGHPUT == 1    
            auto t0 = clock_::now();
        #elif LOADSTORE== 1
            LS = 0;
        #endif

            for (const string &str: uniqued) {
                sketch -> Insert(str.c_str());
            }
        #if THROUGHPUT == 1
            auto t1 = clock_::now();
            duration_insert += mil(t1 - t0).count();
        #elif LOADSTORE == 1
            duration_insert += LS;
        #endif
#if DELETE == 0
        #if THROUGHPUT == 1
            t0 = clock_::now();
        #elif LOADSTORE == 1
            LS = 0;
        #endif
            for (int j = 0; j < TEST_TIMES; j++) {
                for (const string &str: uniqued) {
                    prevent_opt += sketch -> Query(str.c_str());
                }
            }
        #if THROUGHPUT == 1
            t1 = clock_::now();
            duration_query += mil(t1 - t0).count();
        #elif LOADSTORE == 1
            duration_query += LS;
        #endif
        printf("%lf\n", prevent_opt);

#elif DELETE == 1
        #if THROUGHPUT == 1
            t0 = clock_::now();
        #elif LOADSTORE == 1
            LS = 0;
        #endif
            for (const string &str: uniqued) {
                sketch -> Delete(str.c_str());
            }
        #if THROUGHPUT == 1
            t1 = clock_::now();
            duration_delete += mil(t1 - t0).count();
        #elif LOADSTORE == 1
            duration_delete += LS;
        #endif
#endif
        }
#if THROUGHPUT == 1
        res.insert = uniqued.size() * TEST_TIMES / duration_insert;
    #if DELETE == 0
        res.query = uniqued.size() * TEST_TIMES * TEST_TIMES / duration_query;
    #elif DELETE == 1
        res.deletion = uniqued.size() * TEST_TIMES /duration_delete;
    #endif
#elif LOADSTORE == 1
        res.insert = duration_insert / TEST_TIMES / uniqued.size();
    #if DELETE == 0
        res.query = duration_query / TEST_TIMES / TEST_TIMES / uniqued.size();
    #elif DELETE == 1
        res.deletion = duration_delete / TEST_TIMES / uniqued.size();
    #endif
#endif
        return *this;
    }
};
#endif
