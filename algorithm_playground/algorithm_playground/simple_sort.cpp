#include "xshare.h"
#include <stdio.h>

void ss_unit_test_case();

#ifdef SIMPLE_SORT
DECLARE_MAIN_ENTRY(ss_unit_test_case);
#endif

// http://blog.csdn.net/ryfdizuo/article/details/6057479
template<class Type>
void insert_sort(Type* ptr, int size)
{
	for (int i = 1; i < size; i++)
	{
		Type tmp = ptr[i];

		int j = 0;
		for (j = i - 1; j >= 0 && ptr[j] > tmp; j--)
		{
			ptr[j + 1] = ptr[j];		
		}	// 循环的基本理解，循环失败的条件：j < 0 || ptr[j] <= tmp

		ptr[j + 1] = tmp;	// 前一个位置放入tmp
	}

}

void ss_unit_test_case()
{
	const int kMaxSize = 10;
	const int kMaxValue = 100;

	int int_array[kMaxSize];

	fill_array(int_array, kMaxValue);
	print_array(int_array);

	insert_sort(int_array, kMaxSize);
	print_array(int_array);

}

