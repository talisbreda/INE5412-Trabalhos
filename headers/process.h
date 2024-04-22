#ifndef PROCESS_H
#define PROCESS_H

#include <math.h>
#include <process_control_block.h>
#include <chrono>

using namespace std::chrono;

class Process 
{
public: 
    Process(ProcessControlBlock *pcb);

    uint64_t generate_random_number();
    void run();
    int get_pid();
    int get_remaining_time();
    int get_priority(); 
    int get_creation_time();
    void set_remaining_time(int remaining_time);
    void reset();
    void set_state(State state);
    
    ~Process();
private:
    ProcessControlBlock *pcb;
    int creation_time;
	int duration; //seconds
	int period;
	int deadline;
	int priority;
    int remaining_time;
    int pid;
    uint64_t *registers;
    uint64_t SP;
    uint64_t PC;
    uint64_t ST;
    high_resolution_clock::time_point start_time;
};

#endif