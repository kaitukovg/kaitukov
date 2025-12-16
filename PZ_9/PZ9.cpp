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
        MyArray<int> firstArray = {1, 2, 3, 4, 5};
        MyArray<int> secondArray = {5, 4, 3, 2, 1};
        
        std::cout << "First array: " << firstArray << '\n';
        std::cout << "Second array: " << secondArray << '\n';
        
        firstArray.assignWithCheck(0, 10);
        std::cout << "Modified first array: " << firstArray << '\n';
        
        double separationValue = firstArray.computeSeparation(secondArray);
        std::cout << "Separation between arrays: " << separationValue << '\n';
        
        MyArray<double> thirdArray = {1.5, 2.5, 3.5};
        MyArray<double> fourthArray = {0.5, 1.5, 2.5};
        
        std::cout << "\nThird array: " << thirdArray << '\n';
        std::cout << "Fourth array: " << fourthArray << '\n';
        std::cout << "Separation: " << thirdArray.computeSeparation(fourthArray) << '\n';
        
        MyArray<std::string> fifthArray = {"hello", "mam"};
        MyArray<std::string> sixthArray = {"by", "dad"};
        
        std::cout << "\nFifth array: " << fifthArray << '\n';
        
        try {
            double invalidSeparation = fifthArray.computeSeparation(sixthArray);
            std::cout << "Separation: " << invalidSeparation << '\n';
        } catch (const std::bad_typeid& e) {
            std::cout << "Properly handled bad_typeid for string arrays" << '\n';
        }
        
        MyArray<int> seventhArray = {1, 2, 3};
        MyArray<int> eighthArray = {1, 2};
        
        try {
            double mismatchSeparation = seventhArray.computeSeparation(eighthArray);
            std::cout << "Separation: " << mismatchSeparation << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << "Properly caught size mismatch: " << e.what() << '\n';
        }
        
    } catch (const std::exception& error) {
        std::cerr << "Exception occurred: " << error.what() << '\n';
    }
    
    return 0;
}
