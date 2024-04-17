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
        while (true) {
            std::vector<Process *> ready_processes = get_ready_processes();
            Process *p = ready_processes[0];
            bool deadline = deadline_at_current_time();
            if (!deadline) printf("(Current time: %d) Process %d with priority %d started \n", current_time, p->get_pid(), p->get_params()->get_priority());
            while (p->get_remaining_time() > 0 && !deadline) {
                this->cpu->run_process(p);
                current_time++;
                printf("(Current time: %d) Process %d with priority %d has %d seconds left\n", current_time, p->get_pid(), p->get_params()->get_priority(), p->get_remaining_time());
                deadline = deadline_at_current_time();
            }
        }
    }
private:
    std::vector<Process *> sort_by_priority(std::vector<Process *> processes) {
        std::sort(processes.begin(), processes.end(), [](Process *a, Process *b) {
            return a->get_params()->get_priority() > b->get_params()->get_priority();
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
            deadlines.push_back({processes_params[i]->get_deadline(), processes[i]->get_pid()});
        }
        std::sort(deadlines.begin(), deadlines.end());
    }

    bool deadline_at_current_time() {
        if (deadline_accounted) {
            deadline_accounted = false;
            return false;
        }
        for (std::pair<int, int> deadline : deadlines) {
            if (current_time % deadline.first == 0 && current_time != 0) {
                printf("(Current time: %d) Deadline for process %d\n", current_time, deadline.second);
                processes[deadline.second]->reset();
                deadline_accounted = true;
                return true;
            }
        }
        return false;
    }

    CPU* cpu;
    int current_time = 0;
    std::vector<std::vector<Process *>> processes_by_start_time;
    std::vector<ProcessParams *> processes_params;
    std::vector<Process *> processes;
    std::vector<std::pair<int, int>> deadlines;
    bool deadline_accounted = false;
};

#endif