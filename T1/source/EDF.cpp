#include <scheduler.h>
#include <file.h>
#include <process.h>
#include <process_control_block.h>
#include <bits/stdc++.h>
#include <chrono>
#include "EDF.h"


void EDF::execute() {
    File f;
    f.read_file();
    f.print_processes_params();
    this->process_table = f.get_processes();
    for (auto i = 0u; i < process_table.size(); i++) {
        process_table[i]->set_pid(i);;
    }
    if (this->process_table.size() == 0) {
        printf("No processes to run\n");
        return;
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
                if (this->cpu->get_process() != nullptr)
                    this->cpu->stop_process();
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
                printf("P%d: Lost deadlines: %d\n", pcb->get_pid(), pcb->get_lost_deadlines());
            }
            printf("Average turnaround time: %ldus\n", avg_turnaround_time / process_table.size());
            printf("Number of context switches: %d\n", context_switches);
            break;
        }
        ProcessControlBlock *pcb = ready_processes[0];
        bool deadline = deadline_at_current_time();

        if (pcb->get_remaining_time() > 0 && !deadline) {
            Process *currentProcess = this->cpu->get_process();
            if (currentProcess != nullptr && pcb->get_pid() != currentProcess->get_pid()) {
                this->cpu->stop_process();
                this->cpu->set_process(pcb);
                context_switches++;
            } else if (currentProcess == nullptr) {
                context_switches++;
                this->cpu->set_process(pcb);
            }
        }

        bool process_created = process_created_at_current_time();
        while (pcb->get_remaining_time() > 0 && !deadline && !process_created) {
            this->cpu->run_process();
            this->print_current_status(this->cpu->get_process()); 
            current_time++;
            deadline = deadline_at_current_time();
            process_created = process_created_at_current_time();
        }
    }
}

std::vector<ProcessControlBlock* > EDF::sort_by_earliest_deadline(std::vector<ProcessControlBlock *> processes) {
    bool swapped;
    auto n = processes.size();
    if (n <= 1) return processes;
    for (auto i = 0u; i < n - 1; i++) {
        swapped = false;
        for (auto j = 0u; j < n - i - 1; j++) {
            int j_next_deadline = processes[j]->get_creation_time() + processes[j]->get_deadline();
            while (j_next_deadline <= current_time) {
                j_next_deadline += processes[j]->get_deadline();
            }
            int jp1_next_deadline = processes[j + 1]->get_creation_time() + processes[j + 1]->get_deadline();
            while (jp1_next_deadline <= current_time) {
                jp1_next_deadline += processes[j + 1]->get_deadline();
            }

            if (j_next_deadline == jp1_next_deadline) {
                if (processes[j]->get_priority() < processes[j + 1]->get_priority()) {
                    std::swap(processes[j], processes[j + 1]);
                    swapped = true;
                }
            } else if (j_next_deadline > jp1_next_deadline) {
                std::swap(processes[j], processes[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
    return processes;
}

std::vector<ProcessControlBlock *> EDF::get_ready_processes() {
    std::vector<ProcessControlBlock *> ready_processes;
    for (int i = 0; i <= this->current_time && i < (int) processes_by_start_time.size(); i++) {
        for (auto j = 0u; j < processes_by_start_time[i].size(); j++) {
            ProcessControlBlock *p = processes_by_start_time[i][j];
            if (p->get_remaining_time() > 0 && p->get_iterations() > 0) {
                ready_processes.push_back(p);
            }
        }
    }
    return sort_by_earliest_deadline(ready_processes); 
}