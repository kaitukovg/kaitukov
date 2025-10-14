#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>

// Константа точности: 10^-5
const double EPSILON = 1e-5;

// --- Утилиты сравнения плавающей запятой (прототипы) ---
bool IsEqual(double a, double b);
bool IsLess(double a, double b);
bool IsGreater(double a, double b);
bool IsLessOrEqual(double a, double b);
bool IsGreaterOrEqual(double a, double b);

// --- Структуры ---

struct Point {
    double x;
    double y;
};

struct Circle {
    Point center;
    double radius;
};

struct Square {
    Point top_left;
    double side_length;
};

// --- Функции ввода/вывода (прототипы) ---

// Point I/O
void ReadPoint(Point& p);
void PrintPoint(const Point& p);

// Circle I/O
void ReadCircle(Circle& c);
void PrintCircle(const Circle& c);

// Square I/O
void ReadSquare(Square& s);
void PrintSquare(const Square& s);
