#ifndef PROCESS_H
#define PROCESS_H

#include <math.h>
#include <process_control_block.h>
#include <chrono>

using namespace std::chrono;

class Process 
{
public: 
    Process(ProcessControlBlock *pcb) {
        this->pcb = pcb;
        this->duration = pcb->get_duration();
        this->creation_time = pcb->get_creation_time();
        this->period = pcb->get_period();
        this->deadline = pcb->get_deadline();
        this->priority = pcb->get_priority();
        this->remaining_time = pcb->get_remaining_time();
        this->pid = pcb->get_pid();
        this->registers = pcb->get_registers();
        this->SP = pcb->get_SP();
        this->PC = pcb->get_PC();
        this->ST = pcb->get_ST();
		this->start_time = high_resolution_clock::now();
        printf("Instantiating process %d", pid);
    }

    uint64_t generate_random_number() {
        return (uint64_t)(rand() % ((uint64_t)pow(2, 64) - 1)) + 1;
    };

    void run() {
        remaining_time--;
        pcb->dec_remaining_time();
        for (int i = 0; i < 6; i++) {
            registers[i] = generate_random_number();
        }
        SP = generate_random_number();
        PC = generate_random_number();
        ST = generate_random_number();
    }

    int get_pid() {
        return pid;
    }

    int get_remaining_time() {
        return remaining_time;
    }

    int get_priority() {
        return priority;
    }

    int get_creation_time() {
        return creation_time;
    }

    void set_remaining_time(int remaining_time) {
        remaining_time = remaining_time;
    }

    void reset() {
        remaining_time = duration;
    }

    ~Process() {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start_time);
        pcb->set_total_turnaround_time(pcb->get_total_turnaround_time() + duration.count());
        pcb->set_registers(registers);
        pcb->set_SP(SP);
        pcb->set_PC(PC);
        pcb->set_ST(ST);
        // printf("\nProcess %d destroyed", pid);
    }
private:
    ProcessControlBlock *pcb;
    int creation_time;
	int duration; //seconds
	int period;
	int deadline;
	int priority;
    int remaining_time;
    int pid;
    uint64_t *registers;
    uint64_t SP;
    uint64_t PC;
    uint64_t ST;
    high_resolution_clock::time_point start_time;
};

#endif