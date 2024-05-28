#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <process_control_block.h>

class File
{

public:
	File() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			std::cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
	
		int start_time, duration, period, deadline, priority, iterations;
		
		if (!myfile.is_open()) {
			std::cout << "Arquivo não está aberto!" << std::endl;
		}
		
		while (myfile >> start_time >> duration >> period >> deadline >> priority >> iterations) {
			ProcessControlBlock *p = new ProcessControlBlock(start_time, duration, period, deadline, priority, iterations, -1);
			processes.push_back(p);
		}

		std::cout << "Quantidade de processos lidos do arquivo: " << processes.size() << std::endl;
	}

	void print_processes_params() {
		std::vector<ProcessControlBlock *>::iterator iter = processes.begin();

		for(; iter < processes.end(); iter++) {
			ProcessControlBlock *p = *iter;
			printf("Creation time: %d | Duration: %d | Period: %d | Deadline: %d | Priority: %d | Iterations: %d\n", p->get_creation_time(), p->get_duration(), p->get_period(), p->get_deadline(), p->get_priority(), p->get_iterations());
		}
	}

	std::vector<ProcessControlBlock *> get_processes() {
		return processes;
	}

	~File() {
		for(auto i = 0u; i < processes.size() ; i++) {
			ProcessControlBlock *p = processes[i];
			delete p;
		}
	}

private:
	std::ifstream myfile; 
	std::vector<ProcessControlBlock *> processes;
};

#endif