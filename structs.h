#ifndef STRUCTS_H
#define STRUCTS_H

// Структура точки
struct Point {
    double x;
    double y;
};

// Структура круга
struct Circle {
    Point center;
    double radius;
};

// Структура квадрата
struct Square {
    Point leftTop;
    double side;
};

// Константа для сравнения вещественных чисел
const double EPSILON = 1e-5;

#endif