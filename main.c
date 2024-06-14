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
        exit(EXIT_FAILURE);
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

    for (int i = 0; i < n; i++){
        printf("Processo %d:\n", i + 1);
        printf("PID: %d\n", processos[i].pid);
        printf("Tempo de Chegada: %d\n", processos[i].arrival_time);
        printf("Burst: %d\n", processos[i].burst);
        printf("Prioridade: %d\n", processos[i].priority);
        printf("Tempo Restante: %d\n", processos[i].remaining_time);
        printf("Tempo de Inicio: %d\n", processos[i].start_time);
        printf("Tempo de Conclusão: %d\n", processos[i].completion_time);
        printf("Tempo de Espera: %d\n", processos[i].waiting_time);
        printf("\n");
    }
    fclose(Fp);
}

int main() {
    lerArquivo();
    return 0;
}
