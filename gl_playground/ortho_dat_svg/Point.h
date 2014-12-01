/**
 * @file 	Point.h
 * @author 	peterliao(peterliao\@tencent.com)
 * @date 	2010/08/06 09:19:37
 * 
 * $id: Point.h,v 1.0.0 2010/08/06 09:19:37 peterliao Exp $
 * Copyright (C) 2010 Tencent, peterliao(peterliao\@tencent.com).
 *
 * @brief	
 */


#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>

class Point
{
            friend Point operator+(const Point &p1, const Point &p2);
            friend Point operator-(const Point &p1, const Point &p2);
            friend double operator*(const Point &p1, const Point &p2);
            friend double operator^(const Point &p1, const Point &p2);
            friend bool operator==(const Point &p1, const Point &p2);
            friend Point operator/(const Point &p, double k);
            friend Point operator*(double k, const Point &p);
            friend Point operator*(const Point &p, double k);

            friend std::ostream& operator<<(std::ostream &os, const Point &p);
        
        
    public:
        double x;
        double y;

        Point(double xCoor = 0.0, double yCoor = 0.0):x(xCoor), y(yCoor)
        {
            
        }
};

Point operator+(const Point &p1, const Point &p2);
Point operator-(const Point &p1, const Point &p2);

/** 
* dot product
* 
* @param p1 
* @param p2 
* 
* @return 
*/
double operator*(const Point &p1, const Point &p2);

/** 
* cross product
* 
* @param p1 
* @param p2 
* 
* @return 
*/
double operator^(const Point &p1, const Point &p2);


bool operator==(const Point &p1, const Point &p2);


Point operator*(double k, const Point &p);
Point operator*(const Point &p, double k);

#endif

