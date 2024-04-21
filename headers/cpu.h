#ifndef CPU_H
#define CPU_H

#include <process.h>
#include <process_control_block.h>

class CPU
{
public:
    CPU() {
        for (int i = 0; i < 6; i++) {
            this->registers[i] = 0;
        }
        this->SP = 0;
        this->PC = 0;
        this->ST = 0;
        this->currentProcess = nullptr;
    }

    void run_process() {
        this->delay();
        currentProcess->run();
    }

    void delay() {
        sleep(1);
    }

    Process *set_process(ProcessControlBlock *pcb) {
        currentProcess = new Process(pcb);
        return currentProcess;
    }

    Process *get_process() {
        return currentProcess;
    }

    void stop_process() {
        delete this->currentProcess;
        currentProcess = nullptr;
    }

    void set_registers(uint64_t *registers) {
        for (int i = 0; i < 6; i++) {
            this->registers[i] = registers[i];
        }
    }

    void set_register(int index, uint64_t value) {
        this->registers[index] = value;
    }

    void set_SP(uint64_t SP) {
        this->SP = SP;
    }

    void set_PC(uint64_t PC) {
        this->PC = PC;
    }

    void set_ST(uint64_t ST) {
        this->ST = ST;
    }

    uint64_t *get_registers() {
        return registers;
    }

    uint64_t get_SP() {
        return SP;
    }

    uint64_t get_PC() {
        return PC;
    }

    uint64_t get_ST() {
        return ST;
    }


private:
    uint64_t registers[6];
    uint64_t SP;
    uint64_t PC;
    uint64_t ST;
    Process *currentProcess;
};

#endif
