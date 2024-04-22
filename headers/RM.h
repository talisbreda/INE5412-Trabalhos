#ifndef RM_H
#define RM_H

#include <scheduler.h>
#include <file.h>
#include <process.h>
#include <process_control_block.h>
#include <bits/stdc++.h>
#include <chrono>

using namespace std::chrono;

class RM : public Scheduler
{
protected:

    std::vector<ProcessControlBlock *> sort_by_priority(std::vector<ProcessControlBlock *> process_table);

    std::vector<ProcessControlBlock *> get_ready_processes();

public:
    RM(CPU *cpu) : Scheduler(cpu) {}

    void execute();
};

#endif