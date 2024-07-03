#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

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

int lerArquivo(struct processos processos[]) {
    FILE *Fp = fopen("processes.txt", "r");
    if (Fp == NULL) {
        perror("erro");
        exit(EXIT_FAILURE);
    }

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
        printf("Tempo de Conclusao: %d\n", processos[i].completion_time);
        printf("Tempo de Espera: %d\n", processos[i].waiting_time);
        printf("\n");
    }
    fclose(Fp);
    return n;
}

void processos_programa(struct processos processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    int prev_pid = -1;

    while (completed_processes < n) {
        int highest_priority = -1;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        if (processes[idx].pid != prev_pid) {
            if (prev_pid != -1) {
                printf("Troca de contexto: Processo %d preemptado pelo Processo %d\n", prev_pid, processes[idx].pid);
            }
            printf("Processo %d esta executando\n", processes[idx].pid);
            Sleep(10);
            prev_pid = processes[idx].pid;
        }

        processes[idx].remaining_time--;
        current_time++;

        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].waiting_time = processes[idx].completion_time - processes[idx].arrival_time - processes[idx].burst;
            completed_processes++;
            printf("Processo %d completou\n", processes[idx].pid);
        }
    }
}


void calcularTempoMedioDeEspera(struct processos processes[], int n) {
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    double average_waiting_time = (double)total_waiting_time / n;
    printf("tempo medio de espera: %.2f\n", average_waiting_time);
}


int main() {
    struct processos processos[100];
    int n = lerArquivo(processos);
    processos_programa(processos, n);
    calcularTempoMedioDeEspera(processos, n);
    return 0;
}
