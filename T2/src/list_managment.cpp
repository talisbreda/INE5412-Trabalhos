#include <list_managment.h>
#include <linkedList.h>
#include <file.h>
#include <algorithm>

void ListManagment::execute(){  
    OperationList operations = this->file.getOperations();
    for (auto i = 0u; i < operations.size(); i++){
        Operation* op = operations[i];
        if (op->getType() == 0){
            allocate_block(op->getBytesSize(), op->getId(), op->getBlocksSize());
        } else if (op->getType() == 1){
            //std::cout << freeBlocks.get_size() << std::endl;
            deallocate_block(op->getId());
        } else {
            std::cout << "Operação inválida." << std::endl;
        }
    }
    print_list();
}

void ListManagment::allocate_block(int program_size, int id, int block_size) { //provavelmente dá pra tirar o ultimo argumento
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
                memory_list.remove(current);
                memory_list.remove(current->next);
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