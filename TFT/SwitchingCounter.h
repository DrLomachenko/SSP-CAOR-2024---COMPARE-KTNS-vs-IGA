#ifndef SwitchingCounter_H
#define SwitchingCounter_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Объявления внешних переменных
extern std::vector<int> ferramentasJob;
extern std::vector<std::vector<int>> candidateList;
extern unsigned trocasPorEstagio[130];
extern std::vector<std::vector<int>> matrixFerramentas;
extern std::vector<std::vector<int>> matrixFerramentasIGA;
extern unsigned t; // ferramentas
extern vector<unsigned> c; // capacidade do magazine
extern std::vector<unsigned> tempoTroca;
extern int m;

// Объявления функций
long SwitchingCounter(const vector<int> processos, int maquina, bool debug = false); // Значение по умолчанию ТОЛЬКО здесь
double completionTime(std::vector<std::vector<unsigned>> tProcessamento, std::vector<int>& tarefas, int maquina);
double sumCompletionTime(std::vector<std::vector<int>>& maquinas, std::vector<std::vector<unsigned>> tProcessamento);
long total_trocas(std::vector<double> chromosome);
long flowTime(std::vector<double> chromosome, std::vector<std::vector<unsigned>> tProcessamento);

#endif