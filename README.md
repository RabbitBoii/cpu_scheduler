# CPU Scheduler Project ACM

## Overview

This repository contains implementations of various CPU scheduling algorithms in C++. The algorithms included are:
- First-Come, First-Served (FCFS)
- Shortest Job First (SJF) Non-Preemptive
- Shortest Remaining Time First (SRTF) Preemptive
- Round Robin (RR)

Users can input the details of each process and see the scheduling results, including waiting times and turnaround times.


## First-Come, First-Served (FCFS)

First-Come, First-Served (FCFS) is one of the simplest CPU scheduling algorithms. In FCFS, processes are executed in the order they arrive in the ready queue. The process that arrives first gets executed first, and the next process starts only after the current process has completed its execution. This non-preemptive approach ensures that each process runs to completion without interruption once it starts.

## Shortest Remaining Time First (SRTF) Preemptive

Shortest Remaining Time First (SRTF) is a preemptive version of the Shortest Job First (SJF) scheduling algorithm. In SRTF, the scheduler always selects the process with the smallest amount of remaining execution time to run next. If a new process arrives with a shorter remaining time than the current process, the current process is preempted, and the new process is executed. This approach minimizes the average waiting time and turnaround time, as shorter processes are prioritized.

## Shortest Job First (SJF) Non-Preemptive

Shortest Job First (SJF) is a non-preemptive scheduling algorithm that selects the process with the shortest burst time from the ready queue to execute next. This method minimizes the average waiting time and turnaround time because shorter processes are completed quickly, reducing the time other processes wait. Once a process starts execution in SJF, it runs to completion without interruption.

## Round Robin (RR)
Round Robin (RR) is a preemptive CPU scheduling algorithm designed for time-sharing systems. In RR, each process is assigned a fixed time slice or quantum, during which it can execute. Once a process's time slice expires, it is preempted, and the next process in the ready queue is scheduled to run. This cycle continues until all processes are completed. If a process completes before its time slice expires, the scheduler immediately switches to the next process.
