#ifndef EDF_H
#define EDF_H

#include <scheduler.h>
#include <file.h>
#include <process.h>
#include <process_control_block.h>
#include <bits/stdc++.h>
#include <chrono>

using namespace std::chrono;

class EDF : public Scheduler
{
public:
    EDF(CPU *cpu) : Scheduler(cpu) {}

    void execute();

private:

    std::vector<ProcessControlBlock* > sort_by_earliest_deadline(std::vector<ProcessControlBlock *> processes);

    std::vector<ProcessControlBlock *> get_ready_processes();
};

#endif