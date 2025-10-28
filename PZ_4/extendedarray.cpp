#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
using namespace std;

class DynamicArray {
private:
    int* data_;
    size_t size_;

    static void checkValueRange(int value) {
        if (value < -100 || value > 100) {
            throw invalid_argument("Value must be in range [-100, 100].");
        }
    }

    static void checkIndex(size_t idx, size_t size) {
        if (idx >= size) {
            throw out_of_range("Index out of range.");
        }
    }

public:
    explicit DynamicArray(size_t size = 0)
        : data_(nullptr), size_(size)
    {
        if (size_ > 0) {
            data_ = new int[size_];
            fill(data_, data_ + size_, 0);
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
            copy(other.data_, other.data_ + size_, data_);
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        int* new_data = nullptr;
        if (other.size_ > 0) {
            new_data = new int[other.size_];
            copy(other.data_, other.data_ + other.size_, new_data);
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
        cout << "{ ";
        for (size_t i = 0; i < size_; ++i) {
            cout << data_[i];
            if (i + 1 < size_) cout << ", ";
        }
        cout << " } (size=" << size_ << ")\n";
    }

    void printSimple() const {
        for (size_t i = 0; i < size_; ++i) {
            cout << data_[i];
            if (i + 1 < size_) cout << ", ";
        }
        cout << endl;
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

class ExtendedArray : public DynamicArray {
public:
    using DynamicArray::DynamicArray;

    double average() const {
        if (size() == 0) {
            throw logic_error("Cannot calculate average of empty array");
        }
        
        double sum = 0;
        for (size_t i = 0; i < size(); ++i) {
            sum += get(i);
        }
        return sum / size();
    }

    double median() const {
        if (size() == 0) {
            throw logic_error("Cannot calculate median of empty array");
        }

        vector<int> sortedData;
        for (size_t i = 0; i < size(); ++i) {
            sortedData.push_back(get(i));
        }
        sort(sortedData.begin(), sortedData.end());

        size_t mid = sortedData.size() / 2;
        if (sortedData.size() % 2 == 0) {
            return (sortedData[mid - 1] + sortedData[mid]) / 2.0;
        } else {
            return sortedData[mid];
        }
    }

    int min() const {
        if (size() == 0) {
            throw logic_error("Cannot find min of empty array");
        }

        int minVal = get(0);
        for (size_t i = 1; i < size(); ++i) {
            if (get(i) < minVal) {
                minVal = get(i);
            }
        }
        return minVal;
    }

    int max() const {
        if (size() == 0) {
            throw logic_error("Cannot find max of empty array");
        }

        int maxVal = get(0);
        for (size_t i = 1; i < size(); ++i) {
            if (get(i) > maxVal) {
                maxVal = get(i);
            }
        }
        return maxVal;
    }
};

int main() {
    try {
        cout << "Task 1: " << endl;
        DynamicArray array3(3);
        array3.set(0, 15);
        array3.set(1, 25);
        array3.set(2, 35);
        cout << "array3: ";
        array3.printSimple();
        cout << "index 1: " << array3.get(1) << endl;

        cout << "\nTask 2:" << endl;
        cout << "array3: ";
        array3.printSimple();

        cout << "\nTask 3:" << endl;
        DynamicArray array5;
        array5.append(5);
        array5.append(15);
        array5.append(25);
        array5.append(35);
        array5.append(45);
        cout << "array5: ";
        array5.printSimple();

        cout << "\nTask 4:" << endl;
        DynamicArray A(3);
        A.set(0, 5);
        A.set(1, 10);
        A.set(2, 15);
        
        DynamicArray B(2);
        B.set(0, 2);
        B.set(1, 4);
        
        cout << "A: array3: ";
        A.printSimple();
        cout << "B: array2: ";
        B.printSimple();
        
        DynamicArray A_plus_B = A;
        A_plus_B.add(B);
        cout << "A + B: array3: ";
        A_plus_B.printSimple();
        
        DynamicArray A_minus_B = A;
        A_minus_B.subtract(B);
        cout << "A - B: array3: ";
        A_minus_B.printSimple();

        cout << "\nTest" << endl;
        DynamicArray C;
        C.append(100);
        
        DynamicArray D(4);
        D.set(0, 5);
        D.set(1, 10);
        D.set(2, 15);
        D.set(3, 20);
        
        cout << "C: array1: ";
        C.printSimple();
        cout << "D: array4: ";
        D.printSimple();
        
        DynamicArray C_plus_D = C;
        C_plus_D.add(D);
        cout << "C + D: array4: ";
        C_plus_D.printSimple();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}