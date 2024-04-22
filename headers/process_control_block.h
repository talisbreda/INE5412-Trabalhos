#ifndef PROCESS_CONTROL_BLOCK_H
#define PROCESS_CONTROL_BLOCK_H

#include <stdio.h>
#include <ostream>

enum State
{
	NEW,
	READY,
	RUNNING,
	TERMINATED
};
class ProcessControlBlock
{
public:
	ProcessControlBlock(int start_time, int duration, int period, int deadline, int priority, int iterations, int pid);

	int get_creation_time();
	int get_duration();
	int get_period();
	int get_priority();
	int get_deadline();
	int get_remaining_time();
	int get_iterations();
	int get_pid();
	int get_total_turnaround_time();
	int get_total_wait_periods();
	State get_state();
	uint64_t *get_registers();
	uint64_t get_SP();
	uint64_t get_PC();
	uint64_t get_ST();
	void set_registers(uint64_t *registers);
	void set_SP(uint64_t SP);
	void set_PC(uint64_t PC);
	void set_ST(uint64_t ST);
	void dec_remaining_time();
	void dec_iterations();
	void set_pid(int pid);
	void set_total_turnaround_time(int total_turnaround_time);
	void set_total_wait_periods(int total_wait_periods);
	void set_state(State state);
	void reset();

	~ProcessControlBlock();
	
private:	
	int creation_time;
	int duration; //seconds
	int period;
	int deadline;
	int priority;
	int iterations;
	int remaining_time;
	int pid;
	int total_turnaround_time;
	int total_wait_periods;
	uint64_t *registers;
	uint64_t SP;
	uint64_t PC;
	uint64_t ST;
	State state;
};

#endif