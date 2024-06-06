#include <file.h>
#include <operation.h>

File::File() {
    myfile.open("entrada.txt");
    if (!myfile.is_open()) {
        std::cout << "Erro ao abrir o arquivo!\n";
    }
}

void File::read_file() {
    if (!myfile.is_open()) {
        std::cout << "Arquivo não está aberto!" << std::endl;
    }
    myfile >> this->type >> this->memorySize >> this->blockSize >> this->algorithm;

    char operationType;
    while (myfile >> operationType) {
        if (operationType == 'A') {
            int size, id;
            myfile >> size >> id;
            operations.push_back(new Operation(0, id, size));
        } else if (operationType == 'D') {
            int id;
            myfile >> id;
            operations.push_back(new Operation(1, id, -1));
        }
        else {
            std::cout << "Operação inválida!" << std::endl;
        }
    }
}

OperationList File::getOperations() {
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

File& File::operator=(const File& other) {
    if (this != &other) {
        this->type = other.type;
        this->memorySize = other.memorySize;
        this->blockSize = other.blockSize;
        this->algorithm = other.algorithm;
        this->operations = other.operations;
    }
    return *this;
}

File::~File() {
    if (myfile.is_open()) {
        myfile.close();}
}