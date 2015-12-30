#define _CRT_SECURE_NO_WARNINGS

#include "xshare.h"

void cpp11_unit_test();

#ifdef LOG_TEMPLATE
DECLARE_MAIN_ENTRY(cpp11_unit_test);
#endif

void using_test()
{
	using object_t = int;

	int ival = 4;
	using object_t = decltype(ival);

	float fval = 4.0f;
	using ftype_t = decltype(fval);

	using PF = void(*)(int, int);

}

void cpp11_unit_test()
{

}
