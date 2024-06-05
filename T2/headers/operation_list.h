#ifndef OPERATION_LIST_H
#define OPERATION_LIST_H

#include <cstdint>

class OperationList {
 public:
        OperationList() {
            contents = new Operation*[DEFAULT_MAX];
            size_ = 0;
            max_size_ = DEFAULT_MAX;
        }

        void clear() {
            size_ = 0;
        }

        void push_back(Operation* data) {
            insert(data, size_);
        }
        
        void insert(Operation* data, std::size_t index) {
            if (index >= max_size_) {
                throw std::out_of_range("Índice maior que a lista");
            } else if (size_ == max_size_) {
                throw std::out_of_range("Lista cheia");
            } else {
                shift_to_right(index);
                contents[index] = data;
                size_++;
            }
        }

        Operation* pop(std::size_t index) {
            if (empty()) {
                throw std::out_of_range("Lista vazia");
            } else if (size_ > index) {
                Operation* aux = contents[index];
                shift_to_left(index);
                size_--;
                return aux;
            } else {
                throw std::out_of_range("Lista menor que o índice");
            }
        }

        Operation* pop_back() {
            return pop(size_-1);
        }

        Operation* pop_front() {
            return pop(0);
        }

        bool empty() const {
            return size_ == 0;
        }

        Operation* findById(int id) const {
            for (int i = 0; i < static_cast<int>(size_); i++) {
                if (contents[i]->getId() == id) {
                    return contents[i];
                }
            }
            throw std::out_of_range("ID não encontrado na lista");
        }

        std::size_t size() const {
            return size_;
        }

        Operation* operator[](std::size_t index) {
            return contents[index];
        }

        const Operation* operator[](std::size_t index) const {
            return contents[index];
        }

        void shift_to_right(std::size_t index) {
            for (int i = size_; i > static_cast<int>(index); i--) {
                contents[i] = contents[i-1];
            }
        }

        void shift_to_left(std::size_t index) {
            for (int i = index; i < static_cast<int>(size_)-1; i++) {
                contents[i] = contents[i+1];
            }
        }

 private:
        Operation** contents;
        std::size_t size_;
        std::size_t max_size_;

        static const auto DEFAULT_MAX = 1000u;
};


#endif
