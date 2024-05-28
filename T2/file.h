#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <operation.h>
#include <array_list.h>

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
	
		
		
		if (!myfile.is_open()) {
			std::cout << "Arquivo não está aberto!" << std::endl;
		}
		myfile >> this->type >> this->memorySize >> this->blockSize >> this->algorithm;

		char operationType;
		while (myfile >> operationType) {
			if (operationType == 'A') {
				int size, id;
				myfile >> size >> id;
				operations.push_back(Operation(0, id, size));
			} else if (operationType == 'D') {
				int id;
				myfile >> id;
				operations.push_back(Operation(1, id, -1));
			}
			else {
				std::cout << "Operação inválida!" << std::endl;
			}
		}

	}

	~File() {
		if (myfile.is_open()) {
			myfile.close();}
	}

private:
	std::ifstream myfile; 
	int type, blockSize, algorithm;
	long int memorySize;
	ArrayList<Operation> operations;
};

#endif