#include <iostream>
#include <cmath>
#include <typeinfo>
#include <stdexcept>
#include <vector>
#include <initializer_list>
#include <type_traits>

template<typename ElementType>
class MyArray {
    std::vector<ElementType> elements;

public:
    MyArray() = default;
    
    explicit MyArray(size_t count) : elements(count) {}
    
    MyArray(std::initializer_list<ElementType> init_values) : elements(init_values) {}
    
    ElementType& access(size_t position) {
        return elements[position];
    }
    
    const ElementType& access(size_t position) const {
        return elements[position];
    }
    
    ElementType& operator[](size_t position) {
        return access(position);
    }
    
    const ElementType& operator[](size_t position) const {
        return access(position);
    }
    
    size_t count() const {
        return elements.size();
    }
    
    void assignWithCheck(size_t position, const ElementType& value) {
        if (position >= count()) {
            throw std::out_of_range("Position exceeds array bounds");
        }
        elements[position] = value;
    }
    
    template<typename U = ElementType>
    typename std::enable_if<std::is_arithmetic<U>::value, double>::type
    computeSeparation(const MyArray<U>& otherArray) const {
        if (typeid(U) != typeid(otherArray[0])) {
            throw std::bad_typeid();
        }
        
        if (count() != otherArray.count()) {
            throw std::invalid_argument("Array dimensions must match");
        }
        
        double squaredSum = 0.0;
        for (size_t i = 0; i < count(); ++i) {
            // Check range for elements in the first array
            if (elements[i] < -100 || elements[i] > 100) {
                throw std::out_of_range("Element in first array is outside range [-100, 100]");
            }
            
            // Check range for elements in the second array
            if (otherArray[i] < -100 || otherArray[i] > 100) {
                throw std::out_of_range("Element in second array is outside range [-100, 100]");
            }
            
            double difference = static_cast<double>(elements[i]) - 
                               static_cast<double>(otherArray[i]);
            squaredSum += difference * difference;
        }
        
        return std::sqrt(squaredSum);
    }
    
    template<typename U = ElementType>
    typename std::enable_if<!std::is_arithmetic<U>::value, double>::type
    computeSeparation(const MyArray<U>& otherArray) const {
        throw std::bad_typeid();
    }
    
    friend std::ostream& output(std::ostream& stream, const MyArray<ElementType>& array) {
        stream << "[";
        for (size_t i = 0; i < array.elements.size(); ++i) {
            stream << array.elements[i];
            if (i != array.elements.size() - 1) {
                stream << ", ";
            }
        }
        stream << "]";
        return stream;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const MyArray<ElementType>& array) {
        return output(stream, array);
    }
};

int main() {
    try {
        std::cout << "=== Test 1: Valid arrays within range [-100, 100] ===\n";
        MyArray<int> firstArray = {1, 2, 3, 4, 5};
        MyArray<int> secondArray = {5, 4, 3, 2, 1};
        
        std::cout << "First array: " << firstArray << '\n';
        std::cout << "Second array: " << secondArray << '\n';
        
        double separationValue = firstArray.computeSeparation(secondArray);
        std::cout << "Separation between arrays: " << separationValue << '\n';
        
        std::cout << "\n=== Test 2: Arrays with negative values within range ===\n";
        MyArray<int> thirdArray = {-50, -25, 0, 25, 50};
        MyArray<int> fourthArray = {50, 25, 0, -25, -50};
        
        std::cout << "Third array: " << thirdArray << '\n';
        std::cout << "Fourth array: " << fourthArray << '\n';
        std::cout << "Separation: " << thirdArray.computeSeparation(fourthArray) << '\n';
        
        std::cout << "\n=== Test 3: Values at boundary of range ===\n";
        MyArray<int> fifthArray = {-100, 0, 100};
        MyArray<int> sixthArray = {100, 0, -100};
        
        std::cout << "Fifth array: " << fifthArray << '\n';
        std::cout << "Sixth array: " << sixthArray << '\n';
        std::cout << "Separation: " << fifthArray.computeSeparation(sixthArray) << '\n';
        
        std::cout << "\n=== Test 4: Value outside range (greater than 100) ===\n";
        MyArray<int> seventhArray = {1, 2, 101};  // 101 > 100
        MyArray<int> eighthArray = {1, 2, 3};
        
        std::cout << "Seventh array: " << seventhArray << '\n';
        std::cout << "Eighth array: " << eighthArray << '\n';
        
        try {
            double invalidSeparation = seventhArray.computeSeparation(eighthArray);
            std::cout << "Separation: " << invalidSeparation << '\n';
        } catch (const std::out_of_range& e) {
            std::cout << "Correctly caught exception: " << e.what() << '\n';
        }
        
        std::cout << "\n=== Test 5: Value outside range (less than -100) ===\n";
        MyArray<int> ninthArray = {-101, 0, 1};  // -101 < -100
        MyArray<int> tenthArray = {1, 0, -1};
        
        std::cout << "Ninth array: " << ninthArray << '\n';
        std::cout << "Tenth array: " << tenthArray << '\n';
        
        try {
            double invalidSeparation = ninthArray.computeSeparation(tenthArray);
            std::cout << "Separation: " << invalidSeparation << '\n';
        } catch (const std::out_of_range& e) {
            std::cout << "Correctly caught exception: " << e.what() << '\n';
        }
        
        std::cout << "\n=== Test 6: Arrays with double type ===\n";
        MyArray<double> eleventhArray = {-99.5, 50.25, 75.75};
        MyArray<double> twelfthArray = {99.5, -50.25, -75.75};
        
        std::cout << "Eleventh array: " << eleventhArray << '\n';
        std::cout << "Twelfth array: " << twelfthArray << '\n';
        std::cout << "Separation: " << eleventhArray.computeSeparation(twelfthArray) << '\n';
        
        std::cout << "\n=== Test 7: Arrays with non-arithmetic type (string) ===\n";
        MyArray<std::string> thirteenthArray = {"hello", "world"};
        MyArray<std::string> fourteenthArray = {"bye", "world"};
        
        std::cout << "Thirteenth array: " << thirteenthArray << '\n';
        
        try {
            double invalidSeparation = thirteenthArray.computeSeparation(fourteenthArray);
            std::cout << "Separation: " << invalidSeparation << '\n';
        } catch (const std::bad_typeid& e) {
            std::cout << "Correctly handled: bad_typeid for string arrays\n";
        }
        
        std::cout << "\n=== Test 8: Array size mismatch ===\n";
        MyArray<int> fifteenthArray = {1, 2, 3};
        MyArray<int> sixteenthArray = {1, 2};
        
        std::cout << "Fifteenth array: " << fifteenthArray << '\n';
        std::cout << "Sixteenth array: " << sixteenthArray << '\n';
        
        try {
            double mismatchSeparation = fifteenthArray.computeSeparation(sixteenthArray);
            std::cout << "Separation: " << mismatchSeparation << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << "Correctly caught size mismatch: " << e.what() << '\n';
        }
        
    } catch (const std::exception& error) {
        std::cerr << "Unexpected exception: " << error.what() << '\n';
    }
    
    return 0;
}
