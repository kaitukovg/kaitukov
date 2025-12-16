#include <iostream>
#include <stdexcept>
#include <algorithm>

class DynamicArray {
private:
    int* data_;
    size_t size_;

    // Static validation methods for reusability
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
    // Constructor - initializes with zeros (all values within valid range)
    explicit DynamicArray(size_t size = 0)
        : data_(nullptr), size_(size)
    {
        if (size_ > 0) {
            data_ = new int[size_];
            std::fill(data_, data_ + size_, 0); // 0 is within range [-100, 100]
        }
    }

    ~DynamicArray() {
        delete[] data_;
    }

    // Copy constructor
    DynamicArray(const DynamicArray& other)
        : data_(nullptr), size_(other.size_)
    {
        if (size_ > 0) {
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    // Assignment operator
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

    // Get array size
    size_t size() const { return size_; }

    // Get value by index (with validation)
    int get(size_t idx) const {
        checkIndex(idx, size_); // Validation: std::out_of_range
        return data_[idx];
    }

    // Set value by index (with validation)
    void set(size_t idx, int value) {
        checkIndex(idx, size_);        // Validation: std::out_of_range
        checkValueRange(value);        // Validation: std::invalid_argument
        data_[idx] = value;
    }

    // Print array
    void print() const {
        std::cout << "{ ";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i + 1 < size_) std::cout << ", ";
        }
        std::cout << " } (size=" << size_ << ")\n";
    }

    // Append element to the end (with value validation)
    void append(int value) {
        checkValueRange(value); // Validation: std::invalid_argument
        int* new_data = new int[size_ + 1];
        for (size_t i = 0; i < size_; ++i) new_data[i] = data_[i];
        new_data[size_] = value;
        delete[] data_;
        data_ = new_data;
        ++size_;
    }

    // Element-wise addition
    void add(const DynamicArray& other) {
        for (size_t i = 0; i < size_; ++i) {
            int otherVal = (i < other.size_) ? other.data_[i] : 0;
            // Result of addition may exceed [-100, 100] range
            // This is not validated as it's a result of an operation
            data_[i] += otherVal;
        }
    }

    // Element-wise subtraction
    void subtract(const DynamicArray& other) {
        for (size_t i = 0; i < size_; ++i) {
            int otherVal = (i < other.size_) ? other.data_[i] : 0;
            // Result of subtraction may exceed [-100, 100] range
            // This is not validated as it's a result of an operation
            data_[i] -= otherVal;
        }
    }

    // Index access operator (with validation)
    int& operator[](size_t idx) {
        checkIndex(idx, size_); // Validation: std::out_of_range
        return data_[idx];
    }
    
    const int& operator[](size_t idx) const {
        checkIndex(idx, size_); // Validation: std::out_of_range
        return data_[idx];
    }
};

// Demonstration of exception handling
int main() {
    try {
        std::cout << "=== Testing basic functionality ===\n";
        DynamicArray a(5);
        a.set(0, 10);
        a.set(1, -5);
        a.set(4, 100);
        std::cout << "Array a: ";
        a.print();

        DynamicArray b(3);
        b.set(0, 1);
        b.set(1, 2);
        b.set(2, 3);
        std::cout << "Array b: ";
        b.print();

        a.add(b);
        std::cout << "After a.add(b): ";
        a.print();

        a.subtract(b);
        std::cout << "After a.subtract(b): ";
        a.print();

        a.append(-100);
        std::cout << "After a.append(-100): ";
        a.print();

        std::cout << "\n=== Testing exceptions ===\n";
        
        // Test 1: Attempt to set value outside range
        try {
            std::cout << "Attempting to set value 150...\n";
            a.set(0, 150); // Should throw std::invalid_argument
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }

        // Test 2: Attempt to access non-existent index
        try {
            std::cout << "Attempting to get a.get(10)...\n";
            int val = a.get(10); // Should throw std::out_of_range
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }

        // Test 3: Attempt to append invalid value
        try {
            std::cout << "Attempting to append value -101...\n";
            a.append(-101); // Should throw std::invalid_argument
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }

        // Test 4: Testing operator[] with exception
        try {
            std::cout << "Attempting a[20] = 5...\n";
            a[20] = 5; // Should throw std::out_of_range
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }

        std::cout << "\nAll tests completed successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
