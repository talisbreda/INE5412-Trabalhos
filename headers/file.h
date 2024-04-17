#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <process_params.h>

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
	
		int start_time, duration, period, deadline, priority;
		
		if (!myfile.is_open()) {
			std::cout << "Arquivo não está aberto!" << std::endl;
		}
		
		while (myfile >> start_time >> duration >> period >> deadline >> priority) {
			ProcessParams *p = new ProcessParams(start_time, duration, period, deadline, priority);
			processes.push_back(p);
		}

		std::cout << "Quantidade de processos lidos do arquivo: " << processes.size() << std::endl;
	}

	void print_processes_params() {
		std::vector<ProcessParams *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			std::cout << *p;
		}
	}

	std::vector<ProcessParams *> get_processes() {
		return processes;
	}

	~File() {
		for(auto i = 0u; i < processes.size() ; i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

private:
	std::ifstream myfile; 
	std::vector<ProcessParams *> processes;
};

#endif