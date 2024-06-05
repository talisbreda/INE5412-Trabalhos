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
	void read_file();
	OperationList getOperations();
	long int getMemorySize();
	int getType();
	int getBlockSize();
	int getAlgorithm();
	File& operator=(const File& other);
	~File();

private:
	std::ifstream myfile; 
	int type, blockSize, algorithm;
	long int memorySize;
	OperationList operations;
};

#endif