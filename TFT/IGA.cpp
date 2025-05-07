#include "SwitchingCounter.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



long SwitchingCounter(const vector<int> processos, int maquina, bool debug) {
    for (int i=0;i<processos.size();++i){
        if (ferramentasJob[processos[i]]>c[maquina]){
            trocasPorEstagio[0] = 10000000;
            trocasPorEstagio[1] = 10000000;
            return 10000000;
        }
    }
    int start_dist = 0;
    int C = c[maquina];
    int n = processos.size();
    int i,end, passive_intervals_count = 0, last_full = -1;
    std::vector<int> last_seen_tool;
    std::vector<int> filled_slots;
    for (int j = 0; j < t; j++){
        last_seen_tool.push_back(-2);
    } 
    for (int k = 0; k < n; k++) {
        filled_slots.push_back(0);
        start_dist += matrixFerramentasIGA[processos[k]].size();
    }

    for (end = 0; end < n; end++) {
        for (int tool : matrixFerramentasIGA[end]) {
            if (last_full <= last_seen_tool[tool]) {
                for (i = end - 1; i > last_seen_tool[tool]; i--) {
                    if ((++filled_slots[i]) == C) {
                        last_full = i;
                        break;
                    }
                }
                passive_intervals_count++;
            }
            last_seen_tool[tool] = end;
        }
        
        filled_slots[end] = matrixFerramentasIGA[processos[end]].size();
        if (filled_slots[end] == C) { last_full = end; }
    }
    return start_dist - passive_intervals_count;
}

double completionTime(std::vector<std::vector<unsigned>> tProcessamento, std::vector<int>& tarefas, int maquina){
    double tPr = 0;
    for (std::vector<int>::const_iterator i = tarefas.begin(); i!=tarefas.end(); ++i){
        if (ferramentasJob[*i]>c[maquina])
            return 1000000;
        tPr+= tProcessamento[maquina][*i];
    }
    long nTrocas = SwitchingCounter(tarefas,maquina);
    double tTrocas = nTrocas*tempoTroca[maquina];
    return (tPr+tTrocas);
}

double sumCompletionTime(std::vector<std::vector<int>>& maquinas, std::vector<std::vector<unsigned>> tProcessamento){
    double tot = 0;
    int maq = 0;
    std::vector<int> maquinaAux;
    for(std::vector<std::vector<int>>::const_iterator i = maquinas.begin(); i!=maquinas.end(); ++i){
        maquinaAux = *i;
        tot += completionTime(tProcessamento, maquinaAux, maq);
        maq++;
    }
    return tot;
}

long total_trocas(std::vector<double> chromosome){
    long totTrocas = 0;
    std::vector<std::vector<int>> maquinas;
    std::vector<std::pair<double, int>> idx_maquinas;
    int maquina = 0;
    int at = 0;
    std::vector<std::pair<double, unsigned>> ranking(chromosome.size());
    for (unsigned i = 0; i < chromosome.size(); ++i) {
        ranking[i] = std::pair<double, unsigned>(chromosome[i], i);
    }

    std::sort(ranking.begin(), ranking.end());
    std::vector<int> processos;
    int nTrocas = 0;
    for (std::vector<std::pair<double, unsigned>>::const_iterator i = ranking.begin(); i != ranking.end(); ++i) {
        at = (int)i->first;
        if (maquina == 0) {
            maquina = at;
            processos.clear();
        }
        if (maquina == at) {
            processos.push_back(i->second);
        }
        else {
            nTrocas = SwitchingCounter(processos, maquina - 1);
            totTrocas += nTrocas;
            maquinas.push_back(processos);
            maquina = at;
            processos.clear();
            processos.push_back(i->second);
        }
    }
    nTrocas = SwitchingCounter(processos, maquina - 1);
    totTrocas+=nTrocas;
    
    return totTrocas;
}

long flowTime(std::vector<double> chromosome, std::vector<std::vector<unsigned>> tProcessamento){
    std::vector<long>flowTimes;
    std::vector<std::vector<int>> maquinas;
    int maquina = 0;
    int at = 0;
    maquinas.clear();
    long completeFlowTime = 0;
    std::vector<std::pair<double, unsigned>> ranking(chromosome.size());
    for (unsigned i = 0; i < chromosome.size(); ++i) {
        ranking[i] = std::pair<double, unsigned>(chromosome[i], i);
    }

    std::sort(ranking.begin(), ranking.end());
    std::vector<int> processos;

    for (std::vector<std::pair<double, unsigned>>::const_iterator i = ranking.begin(); i != ranking.end(); ++i) {
        at = (int)i->first;
        if (maquina == 0) {
            maquina = at;
            processos.clear();
        }
        if (maquina == at) {
            processos.push_back(i->second);
        }
        else {
            maquinas.push_back(processos);
            maquina = at;
            processos.clear();
            processos.push_back(i->second);
        }
    }
    maquinas.push_back(processos);

    flowTimes.clear();
    maquina = 0;
    for (std::vector<std::vector<int>>::const_iterator i = maquinas.begin(); i != maquinas.end(); ++i) {
        std::vector<int> maquinaAux = *i;
        SwitchingCounter(maquinaAux,maquina);
        flowTimes.push_back(tProcessamento[maquina][maquinaAux[0]]);
        for (unsigned j = 1; j < maquinaAux.size(); ++j) {
            flowTimes.push_back(trocasPorEstagio[j]*tempoTroca[maquina] + tProcessamento[maquina][maquinaAux[j]] + flowTimes[j-1]);
        }
        long flwt = 0;
        for (unsigned j=0;j<flowTimes.size();j++)
            flwt+=flowTimes[j];
        completeFlowTime += flwt;
        maquina++;
        flowTimes.clear();
    }
    return completeFlowTime;
}