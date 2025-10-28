#include "func.h"
#include <iostream>
#include <iomanip>

void RunDemo() {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "--- Demonstration of geometry library working ---" << std::endl;
    std::cout << "EPSILON is set as: " << EPSILON << std::endl;

    // --- Инициализация тестовых фигур ---

    // Точка для проверки
    Point p_test = {2.000001, 3.0};
    Point p_boundary_c = {10.0 + 5.0 / std::sqrt(2.0), 10.0 + 5.0 / std::sqrt(2.0)}; // На границе C1
    
    // Круг 1: Центр (10, 10), R=5
    Circle c1 = {{10.0, 10.0}, 5.0};
    // Круг 2: Центр (15, 10), R=5 (Касание/Пересечение)
    Circle c2 = {{15.0, 10.0}, 5.0};
    // Круг 3: Центр (10, 10), R=15 (Включает C1, C2)
    Circle c3 = {{10.0, 10.0}, 15.0};
    
    // Квадрат 1: Верхний левый (0, 10), L=10
    Square s1 = {{0.0, 10.0}, 10.0};
    // Квадрат 2: Верхний левый (5, 5), L=5 (Пересечение с S1)
    Square s2 = {{5.0, 5.0}, 5.0};
    // Квадрат 3: Верхний левый (1, 9), L=8 (Строго внутри S1)
    Square s3 = {{1.0, 9.0}, 8.0};

    // --- Тестирование базовых свойств ---
    std::cout << "\n Basic features:" << std::endl;
    std::cout << "Circle C1: "; PrintCircle(c1);
    std::cout << "\nC1 Area: " << GetArea(c1) << ", Circumference: " << GetCircumference(c1) << std::endl;
    std::cout << "Square S1: "; PrintSquare(s1);
    std::cout << "\nS1 Area: " << GetArea(s1) << ", Perimeter: " << GetPerimeter(s1) << std::endl;

    // --- Тестирование принадлежности точки ---
    std::cout << "\n Point (" << p_test.x << ", " << p_test.y << ") в S1:" << std::endl;
    std::cout << "   Inside S1 (Expected True): " << (IsPointInsideSquare(p_test, s1)? "True" : "False") << std::endl;
    
    std::cout << "\n Point on border C1 (" << p_boundary_c.x << ", " << p_boundary_c.y << "):" << std::endl;
    std::cout << "   On C1 Contour (Expected True): " << (IsPointOnCircle(p_boundary_c, c1)? "True" : "False") << std::endl;
    std::cout << "   Inside C1 (Expected False): " << (IsPointInsideCircle(p_boundary_c, c1)? "True" : "False") << std::endl;
    
    // --- Тестирование пересечения ---
    std::cout << "\n Intersection tests:" << std::endl;
    std::cout << "C1 vs C2 (Touching, Expected True): " << (IsCircleIntersectingCircle(c1, c2)? "True" : "False") << std::endl;
    std::cout << "S1 vs S2 (Overlapping, Expected True): " << (IsSquareIntersectingSquare(s1, s2)? "True" : "False") << std::endl;
    
    // Пересечение C1 (10, 10, R=5) и S1 (0, 10, L=10). Ближайшая точка S1 к (10, 10) это (10, 10) (верхний правый угол S1).
    std::cout << "C1 vs S1 (Touching Corner, Expected True): " << (IsCircleIntersectingSquare(c1, s1)? "True" : "False") << std::endl;

    // --- Тестирование принадлежности фигуры ---
    std::cout << "\n Affiliation tests (Stricly inside):" << std::endl;
    std::cout << "C1 in C3 (Concentric, R5 in R15, Expected True): " << (IsCircleInCircle(c1, c3)? "True" : "False") << std::endl;
    std::cout << "S3 in S1 (8x8 in 10x10, Expected True): " << (IsSquareInSquare(s3, s1)? "True" : "False") << std::endl;
    
    // Круг C1 (R=5) в Квадрате S_Large (TL: (-5, 15), L=30). R=5 < D_min=5.
    Square s_large = {{-5.0, 15.0}, 30.0};
    std::cout << "C1 in S_Large (Expected True): " << (IsCircleInSquare(c1, s_large)? "True" : "False") << std::endl;
    
    // Квадрат S_small (TL: 9, 11, L=2) в Круге C1 (R=5). Макс. расстояние до центра 10,10 равно sqrt(1^2 + 1^2) = 1.414. 1.414 < 5.
    Square s_small = {{9.0, 11.0}, 2.0};
    std::cout << "S_small in C1 (Expected True): " << (IsSquareInCircle(s_small, c1)? "True" : "False") << std::endl;
    
    // Крайний случай: C1 in C2 (Touching, D=10, R1+R2=10).
    std::cout << "C1 in C2 (Touching, Expected False, not strictly inside): " << (IsCircleInCircle(c1, c2)? "True" : "False") << std::endl;
}

int main() {
	setlocale(LC_ALL, "RU");
    RunDemo();
    return 0;
}
