#include "func.h"
#include <iostream>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool IsEqual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

bool IsLess(double a, double b) {
    return a < b - EPSILON;
}

bool IsGreater(double a, double b) {
    return a > b + EPSILON;
}

bool IsLessOrEqual(double a, double b) {
    return a <= b + EPSILON;
}

bool IsGreaterOrEqual(double a, double b) {
    return a >= b - EPSILON;
}

void ReadPoint(Point& p) {
    if (!(std::cin >> p.x >> p.y)) {}
}

void PrintPoint(const Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ")";
}

void ReadCircle(Circle& c) {
    ReadPoint(c.center);
    if (!(std::cin >> c.radius)) {}
}

void PrintCircle(const Circle& c) {
    std::cout << "Center: ";
    PrintPoint(c.center);
    std::cout << ", Radius: " << c.radius;
}

void ReadSquare(Square& s) {
    ReadPoint(s.top_left);
    if (!(std::cin >> s.side_length)) {}
}

void PrintSquare(const Square& s) {
    std::cout << "Top-Left: ";
    PrintPoint(s.top_left);
    std::cout << ", Side: " << s.side_length;
}

double DistanceSq(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

double GetCircumference(Circle c) {
    return 2.0 * M_PI * c.radius;
}

double GetArea(Circle c) {
    return M_PI * c.radius * c.radius;
}

double GetPerimeter(Square s) {
    return 4.0 * s.side_length;
}

double GetArea(Square s) {
    return s.side_length * s.side_length;
}


bool IsPointInsideCircle(Point p, Circle c) {
    double distSq = DistanceSq(p, c.center);
    double radiusSq = c.radius * c.radius;
    return IsLess(distSq, radiusSq);
}

bool IsPointInsideSquare(Point p, Square s) {
    double x_min = s.top_left.x;
    double x_max = s.top_left.x + s.side_length;
    double y_max = s.top_left.y;
    double y_min = s.top_left.y - s.side_length;

    bool inside_x = IsGreater(p.x, x_min) && IsLess(p.x, x_max);
    bool inside_y = IsGreater(p.y, y_min) && IsLess(p.y, y_max);

    return inside_x && inside_y;
}
bool IsPointOnCircle(Point p, Circle c) {
    double distSq = DistanceSq(p, c.center);
    double radiusSq = c.radius * c.radius;
    return IsEqual(distSq, radiusSq);
}

bool IsPointOnSquare(Point p, Square s) {
    // 1. Не должно быть строго внутри
    if (IsPointInsideSquare(p, s)) {
        return false; 
    }

    double x_min = s.top_left.x;
    double x_max = s.top_left.x + s.side_length;
    double y_max = s.top_left.y;
    double y_min = s.top_left.y - s.side_length;

    // 2. Должно находиться в пределах AABB (включая границы)
    bool within_bounds = IsGreaterOrEqual(p.x, x_min) && IsLessOrEqual(p.x, x_max) &&
                         IsGreaterOrEqual(p.y, y_min) && IsLessOrEqual(p.y, y_max);

    if (!within_bounds) {
        return false;
    }

    // 3. Должно лежать на одной из границ
    bool on_x_boundary = IsEqual(p.x, x_min) |

	IsEqual(p.x, x_max);
    bool on_y_boundary = IsEqual(p.y, y_min) |

	IsEqual(p.y, y_max);

    return on_x_boundary |

	on_y_boundary;
}
bool IsCircleIntersectingCircle(Circle c1, Circle c2) {
    double R_sum = c1.radius + c2.radius;
    double distSq = DistanceSq(c1.center, c2.center);
    double R_sum_sq = R_sum * R_sum;
    
    return IsLessOrEqual(distSq, R_sum_sq);
}

bool IsSquareIntersectingSquare(Square s1, Square s2) {
    double s1_x_min = s1.top_left.x;
    double s1_x_max = s1.top_left.x + s1.side_length;
    double s1_y_min = s1.top_left.y - s1.side_length;
    double s1_y_max = s1.top_left.y;

    double s2_x_min = s2.top_left.x;
    double s2_x_max = s2.top_left.x + s2.side_length;
    double s2_y_min = s2.top_left.y - s2.side_length;
    double s2_y_max = s2.top_left.y;

    bool overlap_x = IsGreaterOrEqual(s1_x_max, s2_x_min) && IsGreaterOrEqual(s2_x_max, s1_x_min);
    
    bool overlap_y = IsGreaterOrEqual(s1_y_max, s2_y_min) && IsGreaterOrEqual(s2_y_max, s1_y_min);

    return overlap_x && overlap_y;
}

bool IsCircleIntersectingSquare(Circle c, Square s) {
    double x_min = s.top_left.x;
    double x_max = s.top_left.x + s.side_length;
    double y_max = s.top_left.y;
    double y_min = s.top_left.y - s.side_length;

    double closest_x = std::max(x_min, std::min(c.center.x, x_max));
    double closest_y = std::max(y_min, std::min(c.center.y, y_max));

    Point closest_point = {closest_x, closest_y};

    double distSq = DistanceSq(closest_point, c.center);
    double radiusSq = c.radius * c.radius;

    // Пересечение, если квадрат расстояния <= квадрата радиуса
    return IsLessOrEqual(distSq, radiusSq);
}

bool IsCircleInCircle(Circle c1, Circle c2) {
    double dist = std::sqrt(DistanceSq(c1.center, c2.center));

	return IsLess(dist + c1.radius, c2.radius);
}

bool IsSquareInSquare(Square s1, Square s2) {
    double s1_x_min = s1.top_left.x;
    double s1_x_max = s1.top_left.x + s1.side_length;
    double s1_y_min = s1.top_left.y - s1.side_length;
    double s1_y_max = s1.top_left.y;

    double s2_x_min = s2.top_left.x;
    double s2_x_max = s2.top_left.x + s2.side_length;
    double s2_y_min = s2.top_left.y - s2.side_length;
    double s2_y_max = s2.top_left.y;

    bool containment_x = IsGreater(s1_x_min, s2_x_min) && IsLess(s1_x_max, s2_x_max);
    bool containment_y = IsGreater(s1_y_min, s2_y_min) && IsLess(s1_y_max, s2_y_max);

    return containment_x && containment_y;
}

bool IsSquareInCircle(Square s, Circle c) {
    Point p_tl = s.top_left;
    Point p_tr = {s.top_left.x + s.side_length, s.top_left.y};
    Point p_bl = {s.top_left.x, s.top_left.y - s.side_length};
    Point p_br = {s.top_left.x + s.side_length, s.top_left.y - s.side_length};

    return IsPointInsideCircle(p_tl, c) &&
           IsPointInsideCircle(p_tr, c) &&
           IsPointInsideCircle(p_bl, c) &&
           IsPointInsideCircle(p_br, c);
}

bool IsCircleInSquare(Circle c, Square s) {
    double x_min = s.top_left.x;
    double x_max = s.top_left.x + s.side_length;
    double y_max = s.top_left.y;
    double y_min = s.top_left.y - s.side_length;

    double dist_left = c.center.x - x_min;
    double dist_right = x_max - c.center.x;
    double dist_bottom = c.center.y - y_min;
    double dist_top = y_max - c.center.y;

    double min_dist_to_edge = dist_left;
    min_dist_to_edge = std::min(min_dist_to_edge, dist_right);
    min_dist_to_edge = std::min(min_dist_to_edge, dist_bottom);
	min_dist_to_edge = std::min(min_dist_to_edge, dist_top);

    return IsLess(c.radius, min_dist_to_edge);
}