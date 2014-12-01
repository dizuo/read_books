/**
 * @file 	Point.cpp
 * @author 	peterliao(peterliao\@tencent.com)
 * @date 	2010/08/06 09:33:07
 * 
 * $id: Point.cpp,v 1.0.0 2010/08/06 09:33:07 peterliao Exp $
 * Copyright (C) 2010 Tencent, peterliao(peterliao\@tencent.com).
 *
 * @brief	
 */

#include "Point.h"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;


Point operator+(const Point &p1, const Point &p2)
{
    Point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;

    return p;
}

Point operator-(const Point &p1, const Point &p2)
{
    Point p;
    p.x = p1.x - p2.x;
    p.y = p1.y - p2.y;

    return p;
}

/** 
* dot product
* 
* @param p1 
* @param p2 
* 
* @return 
*/
double operator*(const Point &p1, const Point &p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}

/** 
* cross product
* 
* @param p1 
* @param p2 
* 
* @return 
*/
double operator^(const Point &p1, const Point &p2)
{
    return p1.x*p2.y - p1.y*p2.x;
}


bool operator==(const Point &p1, const Point &p2)
{
	return fabs(p1.x - p2.x) < numeric_limits<double>::epsilon() && fabs(p1.y - p2.y) < numeric_limits<double>::epsilon();
}

Point operator/(const Point &p, double k)
{
    return Point(p.x/k, p.y/k);
}

ostream& operator<<(ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

Point operator*(double k, const Point &p)
{
    return Point(p.x*k, p.y*k);
}

Point operator*(const Point &p, double k)
{
    return Point(p.x*k, p.y*k);
}
