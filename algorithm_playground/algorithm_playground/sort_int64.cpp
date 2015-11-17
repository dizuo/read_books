#include "xshare.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long int64_t;

void sort_int64_entry();

#ifdef SORT_INT_64
DECLARE_MAIN_ENTRY(sort_int64_entry);
#endif

void test()
{
	typedef unsigned long long uint64_t;
	typedef unsigned int uint32_t;

	uint64_t long_val = 9605602001633;

	uint64_t low = long_val % INT_MAX;
	uint64_t high = long_val / INT_MAX;

	uint64_t new_val = low + high * INT_MAX;

	if (low >= INT_MAX || high >= INT_MAX || new_val != long_val)
	{
		printf("test failed\n");
	}
	else
	{
		printf("%I64d, %I64d\n", long_val, new_val);
	}
	
}

int bad_cmp(const void* a, const void* b)
{
	const int64_t p1 = *(const int64_t*)a;
	const int64_t p2 = *(const int64_t*)b;
	return p1 - p2;
}

int good_cmp(const void* a, const void* b)
{
	const int64_t p1 = *(const int64_t*)a;
	const int64_t p2 = *(const int64_t*)b;
	if (p1 < p2)
		return -1;
	else if (p1 == p2)
		return 0;
	return 1;
}

void dump(int64_t* array, int size)
{
	for (int k = 0; k < size; k++)
		printf("%I64d ", array[k]);
	printf("\n");
}

void random(int64_t* array, int size)
{
	srand(time(NULL));

	for (int k = 0; k < size; k++)
	{
		int left = rand() % size;
		int right = rand() % size;
		if (left == right)
			continue;

		int tmp = array[left];
		array[left] = array[right];
		array[right] = tmp;
	}
}

typedef struct _Cell
{
	int val;
	int other_stuff[1024];
}Cell;
int complex_compare(const void * a, const void * b)
{
	Cell* p1 = *((Cell**)a);
	Cell* p2 = *((Cell**)b);
	return p1->val - p2->val;
}
int simple_compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}
int test_main()
{
	int values[] = { 40, 10, 100, 90, 20, 25 };
	const int NUM = sizeof(values) / sizeof(values[0]);
	Cell* ptr_array[NUM];
	int n;
	for (n = 0; n < NUM; n++)
	{
		ptr_array[n] = (Cell*)malloc(sizeof(Cell));
		ptr_array[n]->val = values[n];
	}

	qsort(values, NUM, sizeof(int), simple_compare);
	for (n = 0; n<6; n++)
		printf("%d ", values[n]);
	printf("\n");

	qsort(ptr_array, NUM, sizeof(Cell*), complex_compare);
	for (n = 0; n<6; n++)
		printf("%d ", ptr_array[n]->val);
	printf("\n");

	for (n = 0; n<6; n++)
		free(ptr_array[n]);

	return 0;
}

void sort_int64_entry()
{
	int64_t array[] = { 4110259597, 4110259597, 1384161, 1384161, 1384163, 
		1393169, 1393171, 1393171, 1393172, 1393172, 1393173, 1393173, 
		1393221, 1393223, 1393228, 1393229, 1393232, 1393233, 1393236, 
		1393237, 1393973, 1396404, 1396404, 1396406, 1396406, 1405300, 
		1405301, 1406172, 1406172, 1406173, 1406173, 1406181, 1406183, 
		1406185, 1406187, 1406190, 1406192, 1406195, 1406197, 1406205, 
		1406205, 1406208, 1406208, 1406464, 1406464, 1406467, 1406467,
		1406470, 1406471, 1406472, 1406473, 1406474, 1406475, 1406478, 
		1406479, 1406480, 1406480, 1406481, 1406481, 1414766, 1415274, 
		1415274, 1415276, 1415276, 1417933, 1421260, 28236400, 175878012, 
		175878013, 175878016, 175878017, 175878018, 175878019 };

	int size = sizeof(array) / sizeof(array[0]);

	test_main();

	test();

	printf("====> first pass\n");
	random(array, size);
	dump(array, size);

	printf("====> second pass\n");
	qsort(array, size, sizeof(int64_t), bad_cmp);
	dump(array, size);

	printf("====> third pass\n");
	random(array, size);
	dump(array, size);

	printf("====> fourth pass\n");
	qsort(array, size, sizeof(int64_t), good_cmp);
	dump(array, size);
}
