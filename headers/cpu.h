#ifndef CPU_H
#define CPU_H

#include <process.h>
#include <process_control_block.h>

class CPU
{
private:
    uint64_t registers[6];
    uint64_t SP;
    uint64_t PC;
    uint64_t ST;
    Process *currentProcess;

public:
    CPU();

    void run_process();

    void delay();

    Process *set_process(ProcessControlBlock *pcb);

    Process *get_process();

    void stop_process();

    void set_registers(uint64_t *registers);

    void set_register(int index, uint64_t value);

    void set_SP(uint64_t SP);

    void set_PC(uint64_t PC);

    void set_ST(uint64_t ST);

    uint64_t *get_registers();

    uint64_t get_SP();

    uint64_t get_PC();

    uint64_t get_ST();



};

#endif
