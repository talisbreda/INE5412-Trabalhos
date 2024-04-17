#ifndef CPU_H
#define CPU_H

#include <process.h>

class CPU
{
public:
    CPU() {}

    void run_process(Process* process) {
        sleep(1);
        process->run();
    }
};

#endif
