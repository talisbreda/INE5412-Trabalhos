#ifndef PROCESS_H
#define PROCESS_H

#include <process_params.h>

class Process 
{
public: 
    Process(ProcessParams *params, int pid) {
        this->duration = params->get_duration();
        this->creation_time = params->get_creation_time();
        this->period = params->get_period();
        this->deadline = params->get_deadline();
        this->priority = params->get_priority();
        this->remaining_time = this->duration;
        this->pid = pid;
    }

    void run() {
        remaining_time--;
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

    void reset() {
        remaining_time = duration;
    }
private:
    int creation_time;
	int duration; //seconds
	int period;
	int deadline;
	int priority;
    int remaining_time;
    int pid;
};

#endif