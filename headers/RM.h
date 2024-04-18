#ifndef RM_H
#define RM_H

#include <scheduler.h>
#include <file.h>
#include <process.h>
#include <process_params.h>
#include <bits/stdc++.h>

class RM
{
public:
    RM(CPU *cpu) {
        this->cpu = cpu;
        File f;
        f.read_file();
        f.print_processes_params();
        this->processes_params = f.get_processes();
        for (auto i = 0u; i < processes_params.size(); i++) {
            Process *p = new Process(processes_params[i], i);
            processes.push_back(p);
        }
        this->organize_processes_by_start_time();
        this->list_deadlines();
    }

    void execute() {
        printf("tempo ");
        for (auto i = 0u; i < processes.size(); i++) {
            printf("P%d ", i);
        }
        while (true) {
            std::vector<Process *> ready_processes = get_ready_processes();
            if (ready_processes.size() == 0) {
                printf("No processes to run\n");
                break;
            }
            Process *p = ready_processes[0];
            bool deadline = deadline_at_current_time();
            // if (!deadline) printf("Process %d with priority %d started \n", current_time, p->get_pid(), p->get_priority());
            while (p->get_remaining_time() > 0 && !deadline) {
                this->cpu->run_process(p);
                // printf("Process %d with priority %d has %d seconds left\n", current_time, p->get_pid(), p->get_priority(), p->get_remaining_time());
                this->print_current_status(p); 
                current_time++;
                deadline = deadline_at_current_time();
            }
        }
    }
private:
    void print_current_status(Process* current) {
        if (current_time < 9) printf("\n %d-%d  ", current_time, current_time+1);
        else if (current_time == 9) printf("\n %d-%d ", current_time, current_time+1);
        else printf("\n%d-%d ", current_time, current_time+1);

        for (auto i = 0u; i < processes.size(); i++) {
            if (current->get_pid() == (int) i) {
                printf("## ");
            } else {
                if (processes[i]->get_creation_time() <= current_time || processes[i]->get_remaining_time() == 0) {
                    printf("-- ");
                } else {
                    printf("   ");
                }
            }            
        }
    }

    std::vector<Process *> sort_by_priority(std::vector<Process *> processes) {
        std::sort(processes.begin(), processes.end(), [](Process *a, Process *b) {
            return a->get_priority() > b->get_priority();
        });
        return processes;
    }

    std::vector<Process *> get_ready_processes() {
        std::vector<Process *> ready_processes;
        for (int i = 0; i <= this->current_time && i < (int) processes_by_start_time.size(); i++) {
            for (auto j = 0u; j < processes_by_start_time[i].size(); j++) {
                Process *p = processes_by_start_time[i][j];
                if (p->get_remaining_time() > 0) {
                    ready_processes.push_back(p);
                }
            }
        }
        return sort_by_priority(ready_processes);
    }

    void organize_processes_by_start_time() {
        for (auto i = 0u; i < processes.size(); i++) {
            ProcessParams *params = processes_params[i];
            Process *p = processes[i];

            while (params->get_creation_time() >= (int) processes_by_start_time.size()) {
                processes_by_start_time.push_back(std::vector<Process *>());
            }
            processes_by_start_time[params->get_creation_time()].push_back(p);

        }
    }

    void list_deadlines() {
        for (auto i = 0u; i < processes.size(); i++) {
            deadlines.push_back({processes[i], processes_params[i]->get_deadline()});
        }
        std::sort(deadlines.begin(), deadlines.end());
    }

    bool deadline_at_current_time() {
        if (deadline_accounted) {
            deadline_accounted = false;
            return false;
        }
        for (std::pair<Process*, int> deadline : deadlines) {
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
    std::vector<std::vector<Process *>> processes_by_start_time;
    std::vector<ProcessParams *> processes_params;
    std::vector<Process *> processes;
    std::vector<std::pair<Process*, int>> deadlines;
    bool deadline_accounted = false;
    int deadlines_missed = 0;
};

#endif