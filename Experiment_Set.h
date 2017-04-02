#ifndef _EXPERIMENT_SET_H
#define _EXPERIMENT_SET_H
#include "Experiment.h"
class Experiment_Set {
private:
    // 0 for zipf0-zipf10
    // 1 for zipf10
    // 2 for ip_trace
    // 3 for ip_trace 10% - 100%
    const int st, ed, reality, del, throuput;
    template<typename T>
    vector<Result> zipf0_10(T& sketch) {
        vector<Result> res;
        for (int i = 0; i <= 10; ++i) {
            res.push_back(Experiment(i, 0, 0).error(sketch).res);
        }
        return res;
    }
    template<typename T>
    vector<Result> zipf_range(T& sketch, int st, int ed) {
        vector<Result> res;
        for (int i = st; i <= ed; ++i) {
            res.push_back(Experiment(i, 0, 0).error(sketch).res);
        }
        return res;
    }
    template<typename T>
    vector<Result> zipf10(T& sketch) {
        vector<Result> res;
        res.push_back(Experiment(10, 0, 0).error(sketch).res);
        return res;
    }
/*
    template<typename T>
    vector<Result> ip_trace(T& sketch, int reality) {
        vector<Result> res;
        res.push_back(Experiment(reality).error(sketch).res);
        return res;
    }
*/
    template<typename T>
    vector<Result> ip_trace_range(T& sketch, int st, int ed, int reality) {
        vector<Result> res;
        for (int i = st; i <= ed; i++) {
            res.push_back(Experiment(i, 0, reality).error(sketch).res);
        }
        return res;
    }
    template<typename T>
    vector<Result> ip_delete(T& sketch, int reality, int del) {
        vector<Result> res;
        for (int i = 1; i <= del; i++) {
            res.push_back(Experiment(10, i, reality).error(sketch).res);
        }
        return res;
    }
    template<typename T>
    vector<Result> throughput(T& sketch, int st, int ed, int del, int reality) {
        vector<Result> res;
            for (int i = st; i <= ed; i++) {
                res.push_back(Experiment(i, 0, reality).speed(sketch).res);
            }
        return res;
    }
/*
    template<typename T>
    vector<Result> ip_trace1_10(T& sketch) {
        vector<Result> res;
        for (int i = 11; i <= 19; ++i) {
            res.push_back(Experiment(i).error(sketch).res);
        }
        return res;
    }
*/
public:
    Experiment_Set(int _st, int _ed, int _reality, int _del, int _throuput):st(_st), ed(_ed), reality(_reality), del(_del), throuput(_throuput) {}
    template<typename T>
    vector<Result> run(T&  sketch) {
        if (throuput) return throughput(sketch, st, ed, del, reality);
        if (del > 0) return ip_delete(sketch, reality, del);
        if (reality > 0) return ip_trace_range(sketch, st, ed, reality);
        return zipf_range(sketch, st, ed);
    /*
        switch(type) {
        case 0: return zipf0_10(sketch);
        case 1: return zipf10(sketch);
        case 2: return ip_trace(sketch);
        case 3: return ip_trace1_10(sketch);
        default: return vector<Result>();
        }
     */
    }
};
#endif
