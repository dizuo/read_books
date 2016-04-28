#include "xshare.h"


void macro_unit_test();

#ifdef MACRO_SHOW_
DECLARE_MAIN_ENTRY(macro_unit_test);
#endif

// in MSVC good.
// in XCode error.
#define SETUP_POD_MEMBERS_(className, firstSmallName, firstBigName, type) \
    type m##firstBigName;    \
    type get##firstBigName() const { return m##firstBigName;} \
	className##* firstSmallName(type t) { m##firstBigName = t; return this; }

class Test
{
public:

	int mFontSize;
	Test* fontSize(int t) { mFontSize = t; return this; }
	int getFontSize() const { return mFontSize; }

	SETUP_POD_MEMBERS_(Test, frontColor, FrontColor, int);

};

void macro_unit_test()
{
	Test test;
	Test* ptest = test.fontSize(12)->frontColor(10);

	int fs = ptest->getFontSize();
	int fc = ptest->getFrontColor();
	printf("%d, %d\n", fs, fc);

}

