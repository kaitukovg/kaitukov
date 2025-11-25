#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

class DynamicArray {
protected:
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

    virtual ~DynamicArray() {
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

    virtual void saveToFile() const {
        // Базовый класс не реализует сохранение
        std::cout << "Base class saveToFile() called\n";
    }

protected:
    std::string getCurrentDateTime() const {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");
        return ss.str();
    }
};

class ArrTxt : public DynamicArray {
public:
    using DynamicArray::DynamicArray;

    void saveToFile() const override {
        std::string filename = getCurrentDateTime() + ".txt";
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        for (size_t i = 0; i < size_; ++i) {
            file << data_[i];
            if (i < size_ - 1) file << " ";
        }
        file.close();
        std::cout << "Array saved to: " << filename << "\n";
    }
};

class ArrCSV : public DynamicArray {
public:
    using DynamicArray::DynamicArray;

    void saveToFile() const override {
        std::string filename = getCurrentDateTime() + ".csv";
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        for (size_t i = 0; i < size_; ++i) {
            file << data_[i];
            if (i < size_ - 1) file << ",";
        }
        file.close();
        std::cout << "Array saved to: " << filename << "\n";
    }
};

// Демонстрация полиморфизма
void saveArray(const DynamicArray& arr) {
    arr.saveToFile();
}

int main() {
    try {
        // Демонстрация работы с ArrTxt
        ArrTxt txtArray(3);
        txtArray.set(0, 1);
        txtArray.set(1, 2);
        txtArray.set(2, 3);
        txtArray.saveToFile();

        // Демонстрация работы с ArrCSV
        ArrCSV csvArray(3);
        csvArray.set(0, 10);
        csvArray.set(1, 20);
        csvArray.set(2, 30);
        csvArray.saveToFile();

        // Демонстрация полиморфизма
        std::cout << "\nPolymorphism demo:\n";
        DynamicArray* arrays[] = { &txtArray, &csvArray };
        for (auto arr : arrays) {
            arr->saveToFile();
        }

        // Или через функцию
        std::cout << "\nUsing function:\n";
        saveArray(txtArray);
        saveArray(csvArray);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}