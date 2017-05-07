#include "polygonpartation.h"

#include <list>

void make_poly(float* buf, int pnt_sz, TPPLPoly& poly)
{
	poly.Init(pnt_sz);

	for (int k(0); k < pnt_sz; k++)
	{
		poly[k].x = buf[2 * k];
		poly[k].y = buf[2 * k + 1];
	}

	if (poly.GetOrientation() == TPPL_CW)
	{
		poly.SetHole(true);
	}

}

int main()
{
	TPPLPoly poly;
	{
		float x = 2.0f;
		float buf[] = { -x, -x, x, -x, x, x, -x, x };
		make_poly(buf, 4, poly);
	}

	TPPLPoly hole;
	{
		float x = 1.0f;
		// float buf[] = { -x, -x, x, -x, x, x, 0, 0, -x, x };
		float buf[] = {-x,-x, -x,x, 0,0, x,x, x,-x};
		make_poly(buf, 5, hole);
	}

	std::list< TPPLPoly > list;
	list.push_back(poly);
	list.push_back(hole);

	std::list< TPPLPoly > triangles;

	TPPLPartition pp;
	if (!pp.Triangulate_EC(&list, &triangles))
	{
		printf("failed\n");
	}

	return 0;
}