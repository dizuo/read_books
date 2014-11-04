#include "xshare.h"

void cc_unit_test_case();

#ifdef CCPP_OP

DECLARE_MAIN_ENTRY(cc_unit_test_case);

#endif

typedef struct _xjmp_buf
{
	int _jb[_JBLEN + 1]; 
} xjmp_buf[1];

void test_jmp_buf(xjmp_buf decay_ptr)
{
	printf("%d\n", sizeof(decay_ptr));

	xjmp_buf var;
	printf("%d\n", sizeof(var));
}

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

void array_pointer_test()
{
	typedef int arr3_t[3];
	typedef int(*arr3_ptr_t)[3];

	arr3_t loc_arr;
	loc_arr[0] = 1; loc_arr[2] = 3;

	arr3_ptr_t parr = &loc_arr;
	(*parr)[1] = 100;

	int matrix[4][3];
	parr = matrix;	// right. int (*)[3] assignment.
	parr = &matrix[1];	// Equal.

	int* prow = matrix[1];	//
	int* phead = &matrix[0][0];

	int** pptr = &prow;	// secondary pointer.

	// int** pptr = matrix;	// ERROR.
}

void cc_unit_test_case()
{
	// pointer_test();

	xjmp_buf obj;
	test_jmp_buf(obj);

	array_pointer_test();
}

