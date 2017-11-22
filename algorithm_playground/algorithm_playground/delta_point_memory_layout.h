#ifndef D_P_M_L_H
#define D_P_M_L_H

#include <time.h>
#include <stdlib.h>
#include <vector>

template< class T >
struct cPoint
{
	T x;
	T y;
};

typedef cPoint<int> pnt_t;
typedef cPoint<char> delta_pnt_t;

struct cPolyline
{
	short absolute_cnt;
	short pnt_cnt;
	pnt_t points[1];
};

static void Transform(cPolyline* polyline, std::vector<pnt_t>& src_vec);

#endif