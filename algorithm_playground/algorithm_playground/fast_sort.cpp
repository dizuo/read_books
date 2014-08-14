#include "share.h"

using namespace std;

void unit_test_case();

template<typename Type, int SIZE>
void fast_sort(Type(&buffer)[SIZE]);


#ifdef FAST_SORT_MAIN
int main()
{
	unit_test_case();

	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}

#endif

template<typename Type>
void sort_impl(Type* buffer, int left, int right)
{
	int middle = (left >> 1) + (right >> 1);


}

template<typename Type, int SIZE>
void fast_sort(Type(&buffer)[SIZE])
{
	sort_impl(buffer, 0, SIZE - 1);
}

