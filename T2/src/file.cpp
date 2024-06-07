#include <file.h>
#include <operation.h>

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        std::cout << "Erro ao abrir o arquivo!\n";
    }
}

OperationList File::read_file() {
    if (!myfile.is_open()) {
        std::cout << "Arquivo não está aberto!" << std::endl;
    }
    myfile >> this->type >> this->memorySize >> this->blockSize >> this->algorithm;

    OperationList operations;
    char operationType;
    while (myfile >> operationType) {
        if (operationType == 'A') {
            int size, id;
            myfile >> size >> id;
            if (size <= 0 || id < 0) {
                std::cout << "Operação inválida!" << std::endl;
                continue;
            }
            Operation* op = new Operation(0, id, size);
            operations.push_back(op);
        } else if (operationType == 'D') {
            int id;
            myfile >> id;
            if (id < 0) {
                std::cout << "Operação inválida!" << std::endl;
                continue;
            }
            Operation* op = new Operation(1, id, 0);
            operations.push_back(op);
        }
        else {
            std::cout << "Operação inválida!" << std::endl;
        }
    }
    return operations;
}


long int File::getMemorySize() {
    return memorySize;
}

int File::getType() {
    return type;
}

int File::getBlockSize() {
    return blockSize;
}

int File::getAlgorithm() {
    return algorithm;
}

File::~File() {
    if (myfile.is_open()) {
        myfile.close();
    }
}