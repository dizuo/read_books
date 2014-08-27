#include "xshare.h"

#include <stdlib.h>
#include <stdio.h>

void ap_unit_test_case();

template< typename Type >
int binary_search(Type* buffer, int length, Type key);

#ifdef ARRAY_OP
DECLARE_MAIN_ENTRY(ap_unit_test_case);
#endif

int compare_int(const void* p1, const void* p2)
{
	return *(const int*)(p1) - *(const int*)(p2);
}

void ap_unit_test_case()
{
	int buffer[10];
	fill_array(buffer, 100);
	print_array(buffer);

	qsort(buffer, 10, sizeof(int), compare_int);
	print_array(buffer);

	int key = 75;
	printf("key = %d, ret = %d\n", key, binary_search(buffer, 10, key));

	// int tmp_buffer[5] = { 0, 0, 1, 4, 5 };
	int tmp_buffer[5] = { 0, 0, 1, 1, 1 };
	key = 0;
	printf("key = %d, ret = %d\n", key, binary_search(tmp_buffer, 5, key));

	key = 1;
	printf("key = %d, ret = %d\n", key, binary_search(tmp_buffer, 5, key));

	key = 2;
	printf("key = %d, ret = %d\n", key, binary_search(tmp_buffer, 5, key));

}

template< typename Type >
int binary_search(Type* buffer, int length, Type key)
{
	if (!buffer || !length)
	{
		return -1;
	}

	if (length == 1 && buffer[0] != key)
	{
		return 0;
	}

	int begin = 0;
	int end = length - 1;
	int pos = -1;

	while (begin < end)
	{
		int mid = (begin + end) >> 1;
		
		if (buffer[mid] == key)
		{
			pos = mid;
			break;
		}
		else if (buffer[mid] < key)
		{
			begin = mid + 1;
		}
		else
		{
			end = mid - 1;
		}

	}

	return pos;
}


