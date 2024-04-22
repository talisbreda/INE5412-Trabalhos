#include <math.h>
#include <process_control_block.h>
#include "process.h"
#include <chrono>

using namespace std::chrono;

Process::Process(ProcessControlBlock *pcb) {
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

uint64_t Process::generate_random_number() {
    return (uint64_t)(rand() % ((uint64_t)pow(2, 64) - 1)) + 1;
};

void Process::run() {
    remaining_time--;
    pcb->dec_remaining_time();
    for (int i = 0; i < 6; i++) {
        registers[i] = generate_random_number();
    }
    SP = generate_random_number();
    PC = generate_random_number();
    ST = generate_random_number();
}

int Process::get_pid() {
    return pid;
}

int Process::get_remaining_time() {
    return remaining_time;
}

int Process::get_priority() {
    return priority;
}

int Process::get_creation_time() {
    return creation_time;
}

void Process::set_remaining_time(int remaining_time) {
    remaining_time = remaining_time;
}

void Process::reset() {
    remaining_time = duration;
}

void Process::set_state(State state) {
    pcb->set_state(state);
}

Process::~Process() {
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_time);
    pcb->set_total_turnaround_time(pcb->get_total_turnaround_time() + duration.count());
    pcb->set_registers(registers);
    pcb->set_SP(SP);
    pcb->set_PC(PC);
    pcb->set_ST(ST);
    // printf("\nProcess %d destroyed", pid);
}