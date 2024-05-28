#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstdint>


template<typename T>
class ArrayList {
 public:
        ArrayList() {
            contents = new T[DEFAULT_MAX];
            size_ = 0;
            max_size_ = DEFAULT_MAX;
        }
        explicit ArrayList(std::size_t max_size) {
            contents = new T[max_size];
            size_ = 0;
            max_size_ = max_size;
        }
        ~ArrayList() {
            delete[] contents;
        }

        void clear() {
            size_ = 0;
        }
        void push_back(const T& data) {
            insert(data, size_);
        }
        void push_front(const T& data) {
            insert(data, 0);
        }
        void insert(const T& data, std::size_t index) {
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
        void insert_sorted(const T& data) {
            if (empty()) {
                push_front(data);
            } else if (full()) {
                throw std::out_of_range("Lista cheia");
            } else {
                std::size_t index = 0;
                for (int i = 0; i < static_cast<int>(size_); i++) {
                    if (data > contents[i]) {
                        index++;
                    }
                }
                insert(data, index);
            }
        }
        T pop(std::size_t index) {
            if (empty()) {
                throw std::out_of_range("Lista vazia");
            } else if (size_ > index) {
                T aux = contents[index];
                shift_to_left(index);
                size_--;
                return aux;
            } else {
                throw std::out_of_range("Lista menor que o índice");
            }
        }
        T pop_back() {
            return pop(size_-1);
        }
        T pop_front() {
            return pop(0);
        }
        void remove(const T& data) {
            for (int i = 0; i < static_cast<int>(size_); i++) {
                if (contents[i] == data) {
                    shift_to_left(i);
                    size_--;
                }
            }
        }
        bool full() const {
            return size_ == max_size_;
        }
        bool empty() const {
            return size_ == 0;
        }
        bool contains(const T& data) const {
            for (int i = 0; i < static_cast<int>(size_); i++) {
                if (contents[i] == data) {
                    return true;
                }
            }
            return false;
        }
        std::size_t find(const T& data) const {
            for (int i = 0; i < static_cast<int>(size_); i++) {
                if (contents[i] == data) {
                    return static_cast<int>(i);
                }
            }
            return size_;
        }
        std::size_t size() const {
            return size_;
        }
        std::size_t max_size() const {
            return max_size_;
        }
        T& at(std::size_t index) {
            if (size() > index) {
                return contents[index];
            }
            throw std::out_of_range("Índice não existe na lista");
        }
        T& operator[](std::size_t index) {
            return contents[index];
        }
        const T& at(std::size_t index) const {
            if (size() > index) {
                return contents[index];
            }
            throw std::out_of_range("Índice não existe na lista");
        }
        const T& operator[](std::size_t index) const {
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
        T* contents;
        std::size_t size_;
        std::size_t max_size_;

        static const auto DEFAULT_MAX = 10u;
};


#endif
