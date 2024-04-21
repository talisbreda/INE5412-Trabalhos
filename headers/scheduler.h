#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cpu.h>

using namespace std::chrono;
class Scheduler
{
public:
    Scheduler(CPU* cpu) : cpu(cpu) {
        this->cpu = cpu;
    };
    void execute() {}
protected:
    std::vector<ProcessControlBlock *> get_ready_processes() {
        // to be implemented by subclasses
        return process_table;
    }


    void print_current_status(Process* current = nullptr) {
        if (current_time < 9) printf("\n %d-%d  ", current_time, current_time+1);
        else if (current_time == 9) printf("\n %d-%d ", current_time, current_time+1);
        else printf("\n%d-%d ", current_time, current_time+1);

        for (auto i = 0u; i < process_table.size(); i++) {
            if (current != nullptr && current->get_pid() == (int) i) {
                printf("## ");
            } else {
                if (process_table[i]->get_iterations() > 0 && (process_table[i]->get_creation_time() <= current_time || process_table[i]->get_remaining_time() == 0)) {
                    printf("-- ");
                    process_table[i]->set_total_wait_periods(process_table[i]->get_total_wait_periods() + 1);
                } else {
                    printf("   ");
                }
            }            
        }
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
                    deadline.first->dec_iterations();
                    printf("Iterations left for P%d: %d; ", deadline.first->get_pid(), deadline.first->get_iterations());
                    if (deadline.first->get_iterations() == 0) {
                        printf("\x1b[32mProcess P%d has finished all iterations; \x1b[0m", deadline.first->get_pid());
                    }
                } else if (deadline.first->get_iterations() > 0) {
                    printf("\x1b[31mDeadline missed for P%d; \x1b[0m", deadline.first->get_pid());
                    deadlines_missed++;
                }
                deadline.first->reset();
                deadline_accounted = true;
            }
        }
        return deadline_accounted;
    }

    bool process_created_at_current_time() {
        if (creation_accounted) {
            creation_accounted = false;
            return false;
        }
        if (current_time >= (int) processes_by_start_time.size()) return false;
        creation_accounted = processes_by_start_time[current_time].size() > 0;
        return creation_accounted;
    }

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