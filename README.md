Project 1

Operating systems

Spring 2025

3/22/2025

Overview: What algorithms were implemented?

This project implements two CPU algorithms: First-Come-First-Serve (FCFS) scheduling and Shortest Job First (SJF) scheduling. FCFS schedules the first process that arrives to run and SJF schedules the jobs with the shortest burst time to run first. The simulation reads process data from an input file (processes.txt), schedules processes according to the chosen algorithm (FCFS and SJF), and calculates key performance metrics such as waiting time (WT), turnaround time (TAT), and CPU Utilization. Waiting time is the total time a process spends waiting before being executed. Turnaround time is the total time from arrival to completion. Lastly, CPU utilization is the percentage of CPU time spent executing processes versus standing idle.
    
Implementation Details: How did you handle process scheduling?

The text file “processes.txt” contains the following details: Process ID (PID), Arrival Time, Burst Time, and Priority. This file is accessed, read, and sorted into an array of structures for the scheduling algorithms. For FCFS scheduling, the processes are sorted and executed by arrival time, accumulating waiting and turnaround times. Then, the completion times are calculated sequentially. For SJF scheduling, the processes are sorted and executed by burst time. Waiting, turnaround, and completion times are all updated dynamically. The Gantt Chart shows the order in which the processes where executed with time stamps provided to visualize the transitions between each process.

Results: Show sample runs and performance comparison (e.g., FCFS vs. RR).

FCFS shows to have an average waiting time of around 5.6 ms, an average turnaround time of 10.4 ms, and a CPU utilization of 92%. SJF shows an average waiting time of around 3.2 ms, an average turnaround time of 8.1 ms, and a CPU utilization of 94%. This data implies that SJF performs better than FCFS as both waiting and turnaround times are faster, however, SJF has a higher CPU utilization compared to FCFS, which has a larger probability of leading to performance issues. 

Challenges & Solutions: What difficulties did you face?

During the development of our CPU scheduler program, we encountered several problems, most prominently in reading from `processes.txt`. Initially, formatting issues caused `fscanf()` to fail causing partial or incorrect process data. To fix this, we inserted checks for validation to ensure all expected values were read and added error checking to inform users if the file was missing or not correctly formatted. Processes with different arrival times were difficult to manage because it led to improper turnaround and waiting times. We solved this by modifying the scheduling logic to take CPU idle time into account in order to provide accurate calculations. Proper sorting of processes was another problem because our initial method based on nested loops was slow for big data sets, and therefore we optimized it utilizing a structured bubble sort. Our initial calculation for CPU usage didn't consider idle time and provided us with incorrect values, which we rectified through formula optimization. Finally, in Gantt chart output, we experienced misalignment that made it hard to read, so we ensured proper consistency with well-placed `printf` statements.


Breakdown of code: 
The program is a basic CPU scheduling simulator that helps show how two different scheduling methods work: First-Come, First-Served (FCFS) and Shortest Job First (SJF). It starts by reading process details like process ID, arrival time, how long the process takes (burst time), and priority from a file called processes.txt. Each process is saved into a list, and then the program asks the user which scheduling method they want to use. Depending on the choice, the program sorts the processes either by arrival time (FCFS) or by burst time (SJF). Then it calculates how long each process had to wait and how much time it took to finish (turnaround time).
The code also includes a function that draws a simple Gantt chart, showing the order in which processes run. It prints out all the important details for each process in a neat table and also tells us how efficiently the CPU was used.
