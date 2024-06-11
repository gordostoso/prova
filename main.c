#include <stdio.h>
#include <stdlib.h>

struct processos {
    int pid;               // ID do processo
    int arrival_time;      // Tempo de chegada
    int burst;             // Duração do processo
    int priority;          // Prioridade do processo
    int remaining_time;    // Tempo restante para completar o processo
    int start_time;        // Tempo em que o processo começa a executar
    int completion_time;   // Tempo em que o processo termina
    int waiting_time;      // Tempo de espera do processo
};

void lerArquivo() {
    FILE *Fp = fopen("processes.txt", "r");
    if (Fp == NULL) {
        perror("erro");
        return 1;
    }

    struct processos processos[100]; 
    int n = 0;

    while (fscanf(Fp, "%d %d %d %d", &processos[n].pid, &processos[n].arrival_time, &processos[n].burst, &processos[n].priority) != EOF) {
        processos[n].remaining_time = processos[n].burst;
        processos[n].start_time = -1;
        processos[n].completion_time = -1;
        processos[n].waiting_time = -1;
        n++;
    }

    fclose(Fp);
}

int main() {
    lerArquivo();
    return 0;
}
