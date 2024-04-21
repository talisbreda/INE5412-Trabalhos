#ifndef PROCESS_CONTROL_BLOCK_H
#define PROCESS_CONTROL_BLOCK_H

#include <stdio.h>
#include <ostream>

class ProcessControlBlock
{
public:
	ProcessControlBlock(int start_time, int duration, int period, int deadline, int priority, int iterations, int pid) { 
		this->creation_time = start_time;
		this->duration = duration;
		this->period = period;
		this->deadline = deadline;
		this->priority = priority;
		this->iterations = iterations;
		this->remaining_time = duration;
		this->pid = -1;
		this->registers = new uint64_t[6];
		this->SP = 0;
		this->PC = 0;
		this->ST = 0;
		this->total_turnaround_time = 0;
		this->total_wait_periods = 0;
		this->lost_deadlines = 0;
	}

	int get_creation_time() {
		return creation_time;
	}

	int get_duration() {
		return duration;
	}

	int get_period() {
		return period;
	}

	int get_priority() {
		return priority;
	}

	int get_deadline() {
		return deadline;
	}

	int get_remaining_time() {
		return remaining_time;
	}

	int get_iterations() {
		return iterations;
	}

	int get_pid() {
		return pid;
	}

	int get_total_turnaround_time() {
		return total_turnaround_time;
	}

	int get_total_wait_periods() {
		return total_wait_periods;
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

	int get_lost_deadlines() {
		return lost_deadlines;
	}

	void set_registers(uint64_t *registers) {
		this->registers = registers;
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
	
	void dec_remaining_time() {
		remaining_time--;
	}

	void dec_iterations() {
		iterations--;
	}

	void set_pid(int pid) {
		this->pid = pid;
	}

	void set_total_turnaround_time(int total_turnaround_time) {
		this->total_turnaround_time = total_turnaround_time;
	}

	void set_total_wait_periods(int total_wait_periods) {
		this->total_wait_periods = total_wait_periods;
	}

	void set_lost_deadlines(int lost_deadlines) {
		this->lost_deadlines = lost_deadlines;
	}

	void reset() {
			remaining_time = duration;
	}

	friend std::ostream &operator<<(std::ostream& os, const ProcessControlBlock& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << " period = " << p.period << " deadline = " << p.deadline << " iterations = " << p.iterations << std::endl;
		return os;
	}
	
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
	int lost_deadlines;
};

#endif