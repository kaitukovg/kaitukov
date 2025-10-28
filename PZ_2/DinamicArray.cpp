#include <iostream>
#include <stdexcept>
#include <algorithm>

class DynamicArray {
private:
    int* data_;
    size_t size_;

    static void checkValueRange(int value) {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Value must be in range [-100, 100].");
        }
    }

    static void checkIndex(size_t idx, size_t size) {
        if (idx >= size) {
            throw std::out_of_range("Index out of range.");
        }
    }

public:
    explicit DynamicArray(size_t size = 0)
        : data_(nullptr), size_(size)
    {
        if (size_ > 0) {
            data_ = new int[size_];
            std::fill(data_, data_ + size_, 0);
        }
    }

    ~DynamicArray() {
        delete[] data_;
    }

    DynamicArray(const DynamicArray& other)
        : data_(nullptr), size_(other.size_)
    {
        if (size_ > 0) {
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        int* new_data = nullptr;
        if (other.size_ > 0) {
            new_data = new int[other.size_];
            std::copy(other.data_, other.data_ + other.size_, new_data);
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        return *this;
    }

    size_t size() const { return size_; }

    int get(size_t idx) const {
        checkIndex(idx, size_);
        return data_[idx];
    }

    void set(size_t idx, int value) {
        checkIndex(idx, size_);
        checkValueRange(value);
        data_[idx] = value;
    }

    void print() const {
        std::cout << "{ ";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i + 1 < size_) std::cout << ", ";
        }
        std::cout << " } (size=" << size_ << ")\n";
    }

    void append(int value) {
        checkValueRange(value);
        int* new_data = new int[size_ + 1];
        for (size_t i = 0; i < size_; ++i) new_data[i] = data_[i];
        new_data[size_] = value;
        delete[] data_;
        data_ = new_data;
        ++size_;
    }

    void add(const DynamicArray& other) {
        for (size_t i = 0; i < size_; ++i) {
            int otherVal = (i < other.size_) ? other.data_[i] : 0;
            data_[i] += otherVal;
        }
    }

    void subtract(const DynamicArray& other) {
        for (size_t i = 0; i < size_; ++i) {
            int otherVal = (i < other.size_) ? other.data_[i] : 0;
            data_[i] -= otherVal;
        }
    }

    int& operator[](size_t idx) {
        checkIndex(idx, size_);
        return data_[idx];
    }
    const int& operator[](size_t idx) const {
        checkIndex(idx, size_);
        return data_[idx];
    }

};

int main() {
    try {
        DynamicArray a(5); // {0,0,0,0,0}
        a.set(0, 10);
        a.set(1, -5);
        a.set(4, 100);
        std::cout << "Initial a: "; a.print();

        DynamicArray b(3);
        b.set(0, 1);
        b.set(1, 2);
        b.set(2, 3);
        std::cout << "b: "; b.print();

        a.add(b);
std::cout << "After a.add(b): "; a.print();

        a.subtract(b);
        std::cout << "After a.subtract(b): "; a.print();

        a.append(-100);
        std::cout << "After a.append(-100): "; a.print();

        DynamicArray c = a;
        std::cout << "Copy c = a: "; c.print();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
