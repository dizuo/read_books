#include "svg_maker.h"

#if 0
int main()
{
	SvgMaker app(100, 100);

	int pts[] = {10,10, 90,10, 90,90, 10,90};
	int ptsNum = 4;

	app.open("path.svg");
	app.WritePath(pts, ptsNum, true);
	app.close();

	return 0;
}

#endif
