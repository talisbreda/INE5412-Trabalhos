#ifndef PROCESS_CONTROL_BLOCK_H
#define PROCESS_CONTROL_BLOCK_H

#include <stdio.h>
#include <ostream>

class ProcessControlBlock
{
public:
	ProcessControlBlock(int start_time, int duration, int period, int deadline, int priority, int pid) { 
		this->creation_time = start_time;
		this->duration = duration;
		this->period = period;
		this->deadline = deadline;
		this->priority = priority;
		this->remaining_time = duration;
		this->pid = -1;
		this->registers = new uint64_t[6];
		this->SP = 0;
		this->PC = 0;
		this->ST = 0;
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

	int get_pid() {
		return pid;
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

	void set_pid(int pid) {
		this->pid = pid;
	}

	void reset() {
			remaining_time = duration;
	}

	friend std::ostream &operator<<(std::ostream& os, const ProcessControlBlock& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << " period = " << p.period << " deadline = " << p.deadline << std::endl;
		return os;
	}
	
private:	
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
};

#endif