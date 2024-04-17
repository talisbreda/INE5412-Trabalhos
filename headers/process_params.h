#ifndef PROCESS_PARAMS_H
#define PROCESS_PARAMS_H

#include <stdio.h>
#include <ostream>

class ProcessParams
{
public:
	ProcessParams(int start_time, int duration, int period, int deadline, int priority) { 
		this->creation_time = start_time;
		this->duration = duration;
		this->period = period;
		this->deadline = deadline;
		this->priority = priority;
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

	friend std::ostream &operator<<(std::ostream& os, const ProcessParams& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << " period = " << p.period << " deadline = " << p.deadline << std::endl;
		return os;
	}
	
private:	
	int creation_time;
	int duration; //seconds
	int period;
	int deadline;
	int priority;
};

#endif