#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cpu.h>
#include <bits/stdc++.h>

class Scheduler
{
public:
    Scheduler(CPU* cpu);

protected:

    std::vector<ProcessControlBlock *> get_ready_processes();
    void print_current_status(Process* current = nullptr);
    void organize_processes_by_start_time();
    void list_deadlines();
    bool deadline_at_current_time();
    bool process_created_at_current_time();

    CPU* cpu;
    int current_time = 0;
    std::vector<std::vector<ProcessControlBlock *>> processes_by_start_time;
    std::vector<ProcessControlBlock *> process_table;
    std::vector<std::pair<ProcessControlBlock*, int>> deadlines;
    bool deadline_accounted = false;
    bool creation_accounted = false;
    int deadlines_missed = 0;
};


#endif