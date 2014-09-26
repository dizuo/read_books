#include "xshare.h"

void cc_unit_test_case();

#ifdef CCPP_OP

DECLARE_MAIN_ENTRY(cc_unit_test_case);

#endif

void pointer_test()
{
	typedef unsigned short ushort_t;
	typedef unsigned int uint_t;

	ushort_t* psht = new ushort_t;
	*psht = 20;
	delete psht;
	// psht = 0;

	*psht = 20;

	uint_t* pint = new uint_t;
	*pint = 9000;

	printf("psht = %x, pint = %x\n", psht, pint);	
	
	printf("*psht = %d, *pint = %d\n", *psht, *pint);

	delete pint;
}

void cc_unit_test_case()
{
	pointer_test();
}

