#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <operation.h>
#include <operation_list.h>

class File
{

public:
	File();
	OperationList read_file();
	long int getMemorySize();
	int getType();
	int getBlockSize();
	int getAlgorithm();
	~File();

private:
	std::ifstream myfile; 
	int type, blockSize, algorithm;
	long int memorySize;
};

#endif