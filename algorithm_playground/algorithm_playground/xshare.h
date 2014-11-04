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
#define BINARY_MAIN
// #define SEQUENCE
// #define SUFFIX_ARRAY
// #define NUMBER_MAIN
// #define STRING_MAIN
// #define ARRAY_OP
// #define CCPP_OP
// #define GRAB_HTML_APP

// #define ANDROID_HWUI_MODEL
// #define SIMPLE_SORT

// #define DEEP_IN_CPP

// #define WINDOWS_THREAD_EVENT

template< typename Type, int SIZE >
inline void fill_array(Type(&buffer)[SIZE], int max_value)
{
	unsigned int seeds = static_cast<unsigned int>(time(NULL));
	srand(seeds);	
	for (int k = 0; k < SIZE; k++)
	{
		*(buffer + k) = rand() % max_value;
	}
}

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

template< typename Type >
void show_value_layout(Type val)
{
	const size_t cLen = sizeof Type;

/*	unsigned char ch_arr[cLen] = { 0 };
	memcpy(ch_arr, &val, cLen);
	for (int k = cLen - 1; k >= 0; k--) printf("0x%02x ", ch_arr[k]);
*/	
	typedef unsigned char* byte_pointer;
	byte_pointer curp = (byte_pointer)(&val);
	for (int k = cLen - 1; k >= 0; k--) printf("0x%02x ", curp[k]);

	printf("\n");
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