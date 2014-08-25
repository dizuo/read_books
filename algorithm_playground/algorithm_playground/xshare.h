#ifndef SHARE_201408141853_H
#define SHARE_201408141853_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

// #define HEAP_MAIN
// #define FAST_SORT_MAIN
// #define STRING_SWAP_MAIN
// #define LINKED_LIST_MAIN
// #define BINARY_MAIN
#define SEQUENCE
// #define SUFFIX_ARRAY
// #define NUMBER_MAIN
// #define STRING_MAIN

template< typename Type, int SIZE>
inline void print_array(Type(&buffer)[SIZE])
{
	using namespace std;
	for (int k = 0; k<SIZE; k++)
	{
		cout << *(buffer + k) << "\t";
	} cout << endl;
}

template< typename Type>
inline void print_array(Type* buffer, int size)
{
	using namespace std;
	for (int k = 0; k<size; k++)
	{
		cout << *(buffer + k) << "\t";
	} cout << endl;
}

#define DECLARE_MAIN_ENTRY(UNIT_TEST_FUNC)	\
int main()	\
{	\
	UNIT_TEST_FUNC();	\
		\
	printf("any key pressed to exit...\n");	\
	getchar();	\
		\
	return 0;	\
}

#endif		// file