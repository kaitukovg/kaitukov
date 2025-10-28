#pragma once

#include "structs.h"

// --- Базовые геометрические утилиты ---
double DistanceSq(Point p1, Point p2);

// --- Вычисления свойств фигур ---
double GetCircumference(Circle c);
double GetArea(Circle c);
double GetPerimeter(Square s);
double GetArea(Square s);

// --- Проверка принадлежности точки фигуре ---
// Строго внутри
bool IsPointInsideCircle(Point p, Circle c);
bool IsPointInsideSquare(Point p, Square s);

// Строго на контуре
bool IsPointOnCircle(Point p, Circle c);
bool IsPointOnSquare(Point p, Square s);

// --- Проверка пересечения фигур ---
// Достаточно одной общей точки контуров (границ).
bool IsCircleIntersectingCircle(Circle c1, Circle c2);
bool IsSquareIntersectingSquare(Square s1, Square s2);
bool IsCircleIntersectingSquare(Circle c, Square s);

// --- Проверка принадлежности фигуры фигуре (строго внутри) ---
bool IsCircleInCircle(Circle c1, Circle c2); // c1 внутри c2
bool IsSquareInSquare(Square s1, Square s2); // s1 внутри s2
bool IsSquareInCircle(Square s, Circle c); // s внутри c
bool IsCircleInSquare(Circle c, Square s); // c внутри s
