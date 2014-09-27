#include <iostream>

#include "xshare.h"
#include "android_hwui.h"

using namespace std;

void model_test();

#ifdef ANDROID_HWUI_MODEL
int main()
{
	model_test();

	cout << "press any key to exit...\n";
	cin.get();
	return 0;
}

#endif

void model_test()
{
	SKWriter32::skwriter_test();
}
