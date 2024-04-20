#ifndef EDF_H
#define EDF_H

#include <scheduler.h>
#include <file.h>
#include <process.h>
#include <process_control_block.h>
#include <bits/stdc++.h>

class EDF
{
public:
    EDF(CPU *cpu) {
        this->cpu = cpu;
    }

    void execute() {
        File f;
        f.read_file();
        f.print_processes_params();
        this->process_table = f.get_processes();
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
            if (ready_processes.size() == 0) {
                printf("No processes to run\n");
                break;
            }
            ProcessControlBlock *pcb = ready_processes[0];
            Process *p = this->cpu->set_process(pcb);
            bool deadline = deadline_at_current_time();
            // if (!deadline) printf("Process %d with priority %d started \n", current_time, p->get_pid(), p->get_priority());
            while (pcb->get_remaining_time() > 0 && !deadline) {
                this->cpu->run_process();
                // printf("Process %d with priority %d has %d seconds left\n", current_time, p->get_pid(), p->get_priority(), p->get_remaining_time());
                this->print_current_status(p); 
                current_time++;
                deadline = deadline_at_current_time();
            }
            // printf("\npcb context before process %d ends: SP: %ld; PC: %ld", pcb->get_pid(), (long)pcb->get_SP(), (long)pcb->get_PC());
            this->cpu->stop_process();
            // printf("\npcb context after process %d ends: SP: %ld; PC: %ld", pcb->get_pid(), (long)pcb->get_SP(), (long)pcb->get_PC());
        }
    }
private:
    void print_current_status(Process* current) {
        if (current_time < 9) printf("\n %d-%d  ", current_time, current_time+1);
        else if (current_time == 9) printf("\n %d-%d ", current_time, current_time+1);
        else printf("\n%d-%d ", current_time, current_time+1);

        for (auto i = 0u; i < process_table.size(); i++) {
            if (current->get_pid() == (int) i) {
                printf("## ");
            } else {
                if (process_table[i]->get_creation_time() <= current_time || process_table[i]->get_remaining_time() == 0) {
                    printf("-- ");
                } else {
                    printf("   ");
                }
            }            
        }
    }

    std::vector<ProcessControlBlock *> sort_by_deadline(std::vector<ProcessControlBlock *> process_table) {
        std::sort(process_table.begin(), process_table.end(), [](ProcessControlBlock *a, ProcessControlBlock *b) {
            return b->get_deadline() > a->get_deadline();
        });
        return process_table;
    }

    std::vector<ProcessControlBlock *> get_ready_processes() {
        std::vector<ProcessControlBlock *> ready_processes;
        for (int i = 0; i <= this->current_time && i < (int) processes_by_start_time.size(); i++) {
            for (auto j = 0u; j < processes_by_start_time[i].size(); j++) {
                ProcessControlBlock *p = processes_by_start_time[i][j];
                if (p->get_remaining_time() > 0) {
                    ready_processes.push_back(p);
                }
            }
        }
        return sort_by_deadline(ready_processes);
    }

    void organize_processes_by_start_time() {
        for (auto i = 0u; i < process_table.size(); i++) {
            ProcessControlBlock *pcb = process_table[i];

            while (pcb->get_creation_time() >= (int) processes_by_start_time.size()) {
                processes_by_start_time.push_back(std::vector<ProcessControlBlock *>());
            }
            processes_by_start_time[pcb->get_creation_time()].push_back(pcb);

        }
    }

    void list_deadlines() {
        for (auto i = 0u; i < process_table.size(); i++) {
            deadlines.push_back({process_table[i], process_table[i]->get_deadline()});
        }
        std::sort(deadlines.begin(), deadlines.end());
    }

    bool deadline_at_current_time() {
        if (deadline_accounted) {
            deadline_accounted = false;
            return false;
        }
        for (std::pair<ProcessControlBlock*, int> deadline : deadlines) {
            if (current_time - deadline.first->get_creation_time() > 0
                && (current_time - deadline.first->get_creation_time()) % deadline.second == 0 
                && current_time != 0) {
                if (deadline.first->get_remaining_time() == 0) {
                    printf("\x1b[32mEnd of period for P%d; \x1b[0m", deadline.first->get_pid());
                } else {
                    printf("\x1b[31mDeadline missed for P%d; \x1b[0m", deadline.first->get_pid());
                    deadlines_missed++;
                    printf("Number of deadlines missed: %d; ", deadlines_missed);
                }
                deadline.first->reset();
                deadline_accounted = true;
            }
        }
        return deadline_accounted;
    }

    CPU* cpu;
    int current_time = 0;
    std::vector<std::vector<ProcessControlBlock *>> processes_by_start_time;
    std::vector<ProcessControlBlock *> process_table;
    std::vector<std::pair<ProcessControlBlock*, int>> deadlines;
    bool deadline_accounted = false;
    int deadlines_missed = 0;
};

#endif