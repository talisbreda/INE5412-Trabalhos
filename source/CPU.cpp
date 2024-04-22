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
    currentProcess->set_state(RUNNING);
    currentProcess->run();
    this->set_PC(currentProcess->get_pcb()->get_PC());
    this->set_SP(currentProcess->get_pcb()->get_SP());
    this->set_ST(currentProcess->get_pcb()->get_ST());
    this->set_registers(currentProcess->get_pcb()->get_registers());
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
    if (currentProcess->get_remaining_time() == 0) {
        currentProcess->set_state(TERMINATED);
    } else {
        currentProcess->set_state(READY);
    }
    this->reset_registers();
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

void CPU::reset_registers() {
    this->set_PC(0);
    this->set_SP(0);
    this->set_ST(0);
    for (int i = 0; i < 6; i++) {
        this->registers[i] = 0;
    }
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