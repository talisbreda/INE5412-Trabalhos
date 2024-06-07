#include <list_managment.h>
#include <operation_list.h>
#include <linkedList.h>
#include <file.h>
#include <algorithm>
#include <Node.h>

void ListManagment::execute(OperationList operations){  
    if (this->algorithm == 1) {
        for (auto i = 0u; i < operations.size(); i++){
            Operation* op = operations[i];
            
            if (op->getType() == 0){
                first_fit(op->getBytesSize(), op->getId(), op->getBlocksSize());
            } else if (op->getType() == 1){
                //std::cout << freeBlocks.get_size() << std::endl;
                deallocate_block(op->getId());
            } else {
                std::cout << "Operação inválida." << std::endl;
            }
        }
    } else if (this->algorithm == 2) {
        for (auto i = 0u; i < operations.size(); i++){
            Operation* op = operations[i];
            
            if (op->getType() == 0){
                best_fit(op->getBytesSize(), op->getId(), op->getBlocksSize());
            } else if (op->getType() == 1){
                //std::cout << freeBlocks.get_size() << std::endl;
                deallocate_block(op->getId());
            } else {
                std::cout << "Operação inválida." << std::endl;
            }
        }
    } else {
        std::cout << "Algoritmo inválido." << std::endl;
    }
    print_list();
}

void ListManagment::first_fit(int program_size, int id, int block_size) { //provavelmente dá pra tirar o ultimo argumento
    Node* current = memory_list.get_head();
    program_size = std::max(block_size, program_size);
    while(current != nullptr){
        if (current->ID == -1 && current->data_size >= program_size){
            current->ID = id;
            if (current->data_size > program_size){
                current->ID = id;
                Node* newNode = new Node(current->data_size - program_size, -1);
                memory_list.insert_after(newNode, current);
            }
            current->data_size = program_size;
            break;
        }
        current = current->next;
    }
}

void ListManagment::best_fit(int program_size, int id, int block_size) {
    Node* current = memory_list.get_head();
    program_size = std::max(block_size, program_size);
    Node* bestFit = nullptr;
    while(current != nullptr){
        if (current->ID == -1 && current->data_size >= program_size){
            if (bestFit == nullptr || current->data_size < bestFit->data_size){
                bestFit = current;
            }
        }
        current = current->next;
    }
    if (bestFit != nullptr){
        bestFit->ID = id;
        if (bestFit->data_size > program_size){
            Node* newNode = new Node(bestFit->data_size - program_size, -1);
            memory_list.insert_after(newNode, bestFit);
        }
        bestFit->data_size = program_size;
    }
}

// Desaloca um bloco dado seu índice
void ListManagment::deallocate_block(int id) {
    Node* current = memory_list.get_head();
    while (current != nullptr) {
        if (current->ID == id) {
            if ((current->prev == nullptr || current->prev->ID != -1) && (current->next == nullptr || current->next->ID != -1)){
                current->ID = -1;
            } else if ((current->prev == nullptr || current->prev->ID != -1) && current->next != nullptr && current->next->ID == -1){
                current->next->data_size += current->data_size;
                memory_list.remove(current);
            } else if ((current->next == nullptr || current->next->ID != -1) && current->prev != nullptr && current->prev->ID == -1){
                current->prev->data_size += current->data_size;
                memory_list.remove(current);
            } else if (current->next != nullptr && current->next->ID == -1 && current->prev != nullptr && current->prev->ID == -1){
                current->prev->data_size += current->data_size + current->next->data_size;
                memory_list.remove(current->next);
                memory_list.remove(current);
            } else {
                std::cerr << "Deu ruim" << std::endl;
            }
            break;
        } else {
            current = current->next;
        }
    }
}

void ListManagment::print_list(){
    Node* current = memory_list.get_head();
    while (current)
    {
        std::cout << current->data_size << " " << (current->ID == -1?"0":"1") << std::endl;
        current = current->next;
    }
}

void ListManagment::printSummary(OperationList operations) {
    int usedBytes = 0;
    int allocatedBytes = 0;
    int deallocatedBytes = 0;

    Node* current = memory_list.get_head();
    while (current != nullptr) {
        if (current->ID != -1) {
            usedBytes += current->data_size;
        } else {
            deallocatedBytes += current->data_size;
        }
        allocatedBytes += current->data_size;
        current = current->next;
    }

    std::cout << usedBytes << std::endl;
    std::cout << allocatedBytes << std::endl;
    std::cout << deallocatedBytes << std::endl;


    int allocations = 0;
    int deallocations = 0;

    for (auto i = 0u; i < operations.size(); i++) {
        if (operations[i]->getType() == 0) {
            allocations++;
        } else if (operations[i]->getType() == 1) {
            deallocations++;
        }
    }

    std::cout << allocations << std::endl;
    std::cout << deallocations << std::endl;
}