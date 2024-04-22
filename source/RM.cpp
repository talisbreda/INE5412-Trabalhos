#include <scheduler.h>
#include <file.h>
#include <process.h>
#include <process_control_block.h>
#include <bits/stdc++.h>
#include <chrono>

#include "RM.h"

using namespace std::chrono;

void RM::execute() {
    File f;;
    f.read_file();
    f.print_processes_params();
    this->process_table = f.get_processes();
    if (this->process_table.size() == 0) {
        printf("No processes to run\n");
        return;
    }
    for (auto i = 0u; i < process_table.size(); i++) {
        process_table[i]->set_pid(i);;
    }
    this->organize_processes_by_start_time();
    this->list_deadlines();
    printf("tempo ");
    for (auto i = 0u; i < process_table.size(); i++) {
        printf("P%d ", i);
    }
    while (true) {
        std::vector<ProcessControlBlock *> ready_processes = get_ready_processes();
        if (ready_processes.size() == 0 && std::any_of(process_table.begin(), process_table.end(), [](ProcessControlBlock *p)
                                                        { return p->get_iterations() > 0; })) {
            bool deadline = deadline_at_current_time();
            bool process_created = process_created_at_current_time();
            if (!deadline && !process_created) {
                this->cpu->delay();
                this->print_current_status(); 
                current_time++;
                deadline = deadline_at_current_time();
                process_created = process_created_at_current_time();
            }
            continue;
        }
        else if (ready_processes.size() == 0)
        {
            printf("\nNo processes to run\n");
            int avg_turnaround_time = 0;
            for (auto pcb : process_table) {
                // code to loop through each PCB
                printf("P%d: Total turnaround time: %dus\n", pcb->get_pid(), pcb->get_total_turnaround_time());
                avg_turnaround_time += pcb->get_total_turnaround_time();
                printf("P%d: Total wait periods: %d\n", pcb->get_pid(), pcb->get_total_wait_periods());
            }
            printf("Average turnaround time: %ldus\n", avg_turnaround_time / process_table.size());
            break;
        }
        ProcessControlBlock *pcb = ready_processes[0];
        auto start = high_resolution_clock::now();
        Process *p = this->cpu->set_process(pcb);
        bool deadline = deadline_at_current_time();
        bool process_created = process_created_at_current_time();
        while (pcb->get_remaining_time() > 0 && !deadline && !process_created) {
            this->cpu->run_process();
            this->print_current_status(p); 
            current_time++;
            deadline = deadline_at_current_time();
            process_created = process_created_at_current_time();
        }
        // printf("\npcb context before process %d ends: SP: %ld; PC: %ld", pcb->get_pid(), (long)pcb->get_SP(), (long)pcb->get_PC());
        this->cpu->stop_process();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        pcb->set_total_turnaround_time(pcb->get_total_turnaround_time() + duration.count());
        // printf("\npcb context after process %d ends: SP: %ld; PC: %ld", pcb->get_pid(), (long)pcb->get_SP(), (long)pcb->get_PC());
    }
}

std::vector<ProcessControlBlock *> RM::sort_by_priority(std::vector<ProcessControlBlock *> process_table) {
    std::sort(process_table.begin(), process_table.end(), [](ProcessControlBlock *a, ProcessControlBlock *b) {
        return a->get_priority() > b->get_priority();
    });
    return process_table;
}

std::vector<ProcessControlBlock *> RM::get_ready_processes() {
    std::vector<ProcessControlBlock *> ready_processes;
    for (int i = 0; i <= this->current_time && i < (int) this->processes_by_start_time.size(); i++) {
        for (auto j = 0u; j < this->processes_by_start_time[i].size(); j++) {
            ProcessControlBlock *p = this->processes_by_start_time[i][j];
            if (p->get_remaining_time() > 0 && p->get_iterations() > 0) {
                ready_processes.push_back(p);
            }
        }
    }
    return sort_by_priority(ready_processes);
}