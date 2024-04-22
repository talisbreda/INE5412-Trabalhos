#include <stdio.h>
#include <ostream>
#include "process_control_block.h"

ProcessControlBlock::ProcessControlBlock(int start_time, int duration, int period, int deadline, int priority, int iterations, int pid) { 
    this->creation_time = start_time;
    this->duration = duration;
    this->period = period;
    this->deadline = deadline;
    this->priority = priority;
    this->iterations = iterations;
    this->remaining_time = duration;
    this->pid = -1;
    this->registers = new uint64_t[6];
    this->SP = 0;
    this->PC = 0;
    this->ST = 0;
    this->total_turnaround_time = 0;
    this->total_wait_periods = 0;
    this->state = NEW;
}

int ProcessControlBlock::get_creation_time() {
    return creation_time;
}

int ProcessControlBlock::get_duration() {
    return duration;
}

int ProcessControlBlock::get_period() {
    return period;
}

int ProcessControlBlock::get_priority() {
    return priority;
}

int ProcessControlBlock::get_deadline() {
    return deadline;
}

int ProcessControlBlock::get_remaining_time() {
    return remaining_time;
}

int ProcessControlBlock::get_iterations() {
    return iterations;
}

int ProcessControlBlock::get_pid() {
    return pid;
}

int ProcessControlBlock::get_total_turnaround_time() {
    return total_turnaround_time;
}

int ProcessControlBlock::get_total_wait_periods() {
    return total_wait_periods;
}

State ProcessControlBlock::get_state() {
    return state;
}

uint64_t* ProcessControlBlock::get_registers() {
    return registers;
}

uint64_t ProcessControlBlock::get_SP() {
    return SP;
}

uint64_t ProcessControlBlock::get_PC() {
    return PC;
}

uint64_t ProcessControlBlock::get_ST() {
    return ST;
}

void ProcessControlBlock::set_registers(uint64_t *registers) {
    this->registers = registers;
}

void ProcessControlBlock::set_SP(uint64_t SP) {
    this->SP = SP;
}

void ProcessControlBlock::set_PC(uint64_t PC) {
    this->PC = PC;
}

void ProcessControlBlock::set_ST(uint64_t ST) {
    this->ST = ST;
}

void ProcessControlBlock::dec_remaining_time() {
    remaining_time--;
}

void ProcessControlBlock::dec_iterations() {
    iterations--;
}

void ProcessControlBlock::set_pid(int pid) {
    this->pid = pid;
}

void ProcessControlBlock::set_total_turnaround_time(int total_turnaround_time) {
    this->total_turnaround_time = total_turnaround_time;
}

void ProcessControlBlock::set_total_wait_periods(int total_wait_periods) {
    this->total_wait_periods = total_wait_periods;
}

void ProcessControlBlock::reset() {
    remaining_time = duration;
}

void ProcessControlBlock::set_state(State state) {
    this->state = state;
}

ProcessControlBlock::~ProcessControlBlock() {
    delete[] registers;
}