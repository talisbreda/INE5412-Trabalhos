#include <process.h>
#include <process_control_block.h>
#include "cpu.h"
#include <unistd.h>

CPU::CPU() {
    for (int i = 0; i < 6; i++) {
        this->registers[i] = 0;
    }
    this->SP = 0;
    this->PC = 0;
    this->ST = 0;
    this->currentProcess = nullptr;
}

void CPU::run_process() {
    this->delay();
    currentProcess->run();
}

void CPU::delay() {
    sleep(0.5);
}

Process* CPU::set_process(ProcessControlBlock *pcb) {
    currentProcess = new Process(pcb);
    return currentProcess;
}

Process *CPU::get_process() {
    return currentProcess;
}

void CPU::stop_process() {
    delete this->currentProcess;
    currentProcess = nullptr;
}

void CPU::set_registers(uint64_t *registers) {
    for (int i = 0; i < 6; i++) {
        this->registers[i] = registers[i];
    }
}

void CPU::set_register(int index, uint64_t value) {
    this->registers[index] = value;
}

void CPU::set_SP(uint64_t SP) {
    this->SP = SP;
}

void CPU::set_PC(uint64_t PC) {
    this->PC = PC;
}

void CPU::set_ST(uint64_t ST) {
    this->ST = ST;
}

uint64_t *CPU::get_registers() {
    return registers;
}

uint64_t CPU::get_SP() {
    return SP;
}

uint64_t CPU::get_PC() {
    return PC;
}

uint64_t CPU::get_ST() {
    return ST;
}