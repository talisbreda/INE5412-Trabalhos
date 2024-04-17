#ifndef PROCESS_H
#define PROCESS_H

#include <process_params.h>

class Process 
{
public: 
    Process(ProcessParams *params, int pid) {
        this->params = params;
        this->duration = params->get_duration();
        this->remaining_time = this->duration;
        this->pid = pid;
    }

    void run() {
        remaining_time--;
    }

    ProcessParams *get_params() {
        return params;
    }

    int get_pid() {
        return pid;
    }

    int get_remaining_time() {
        return remaining_time;
    }

    void reset() {
        remaining_time = duration;
    }
private:
    ProcessParams *params;
    int duration;
    int remaining_time;
    int pid;
};

#endif