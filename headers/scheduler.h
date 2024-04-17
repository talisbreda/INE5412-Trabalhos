#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cpu.h>

class Scheduler
{
public:
    Scheduler(CPU* cpu) : cpu(cpu) {};
    virtual void execute();
private:
    CPU* cpu;
};


#endif