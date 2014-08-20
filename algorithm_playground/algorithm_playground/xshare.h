#ifndef SHARE_201408141853_H
#define SHARE_201408141853_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

// #define HEAP_MAIN
// #define FAST_SORT_MAIN
// #define STRING_SWAP_MAIN
// #define REVERT_LIST_MAIN
// #define BINARY_MAIN
// #define SEQUENCE
#define SUFFIX_ARRAY

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

#endif