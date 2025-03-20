#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// Process structure
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to read process data from file
int readProcesses(Process processes[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return -1;
    }

    int i = 0;
    while (fscanf(file, "%d %d %d %d", 
                  &processes[i].pid, 
                  &processes[i].arrival_time, 
                  &processes[i].burst_time, 
                  &processes[i].priority) == 4) {
        i++;
    }
    fclose(file);
    return i; // Number of processes read
}

// Function to calculate waiting time, turnaround time, and completion time
void calculateTimes(Process processes[], int n, int completion_time[], float *cpu_utilization) {
    int total_execution_time = 0;
    int total_time = 0;

    processes[0].waiting_time = 0;
    completion_time[0] = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = completion_time[0] - processes[0].arrival_time;

    total_execution_time += processes[0].burst_time;
    total_time = completion_time[0];

    for (int i = 1; i < n; i++) {
        int prev_completion = completion_time[i - 1];

        processes[i].waiting_time = prev_completion - processes[i].arrival_time;
        if (processes[i].waiting_time < 0) processes[i].waiting_time = 0;

        completion_time[i] = prev_completion + processes[i].burst_time;
        processes[i].turnaround_time = completion_time[i] - processes[i].arrival_time;

        total_execution_time += processes[i].burst_time;
        total_time = completion_time[i];
    }

    // Calculate CPU Utilization
    *cpu_utilization = ((float)total_execution_time / total_time) * 100;
}

// Function to print Gantt Chart
void printGanttChart(Process processes[], int n, int completion_time[]) {
    printf("\nGantt Chart:\n ");
    
    // Print top border
    for (int i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n|");

    // Print process execution
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].pid);
    }

    printf("\n ");
    // Print bottom border
    for (int i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n0");

    // Print time stamps
    for (int i = 0; i < n; i++) {
        printf("     %d", completion_time[i]);
    }
    printf("\n");
}

// FCFS Scheduling
void fcfs(Process processes[], int n) {
    printf("\n===== First-Come, First-Served (FCFS) Scheduling =====\n");

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completion_time[n];
    float cpu_utilization;
    calculateTimes(processes, n, completion_time, &cpu_utilization);

    // Print results
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, 
               processes[i].turnaround_time);
    }

    // Print Gantt Chart and CPU Utilization
    printGanttChart(processes, n, completion_time);
    printf("\nCPU Utilization: %.2f%%\n", cpu_utilization);
}

// SJF Scheduling
void sjf(Process processes[], int n) {
    printf("\n===== Shortest Job First (SJF) Scheduling =====\n");

    // Sort by burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int completion_time[n];
    float cpu_utilization;
    calculateTimes(processes, n, completion_time, &cpu_utilization);

    // Print results
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, 
               processes[i].turnaround_time);
    }

    // Print Gantt Chart and CPU Utilization
    printGanttChart(processes, n, completion_time);
    printf("\nCPU Utilization: %.2f%%\n", cpu_utilization);
}

// Main function with menu-driven approach
int main() {
    Process processes[MAX_PROCESSES];
    int n = readProcesses(processes, "processes.txt");

    if (n <= 0) {
        printf("No valid processes found!\n");
        return 1;
    }

    int choice;
    do {
        printf("\nCPU Scheduling Menu:\n");
        printf("1. First-Come, First-Served (FCFS)\n");
        printf("2. Shortest Job First (SJF)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(processes, n);
                break;
            case 2:
                sjf(processes, n);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
