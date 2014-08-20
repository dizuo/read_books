#include "xshare.h"

using namespace std;

class FastSort
{
public:
	static void unit_test_case();

	template<typename Type>
	int part_impl(Type* buffer, int left, int right);

	template<typename Type>
	void sort_impl(Type* buffer, int begin, int end, int length);

	template<typename Type, int SIZE>
	void fast_sort(Type(&buffer)[SIZE]);
};

#ifdef FAST_SORT_MAIN
int main()
{
	// int a[9] = { 5, 4, 9, 1, 7, 6, 2, 3, 8 };
	int a[5] = { 5, 4, 3, 2, 1 };
	quickSort(a, 0, 4);
	for (int i = 0; i<sizeof(a)/sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	} printf("\n");

	FastSort::unit_test_case();

	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}

#endif

void FastSort::unit_test_case()
{
	srand(time(NULL));

	const int kMaxSize = 50;
	const int kMaxValue = 100;

	// bad case.
	// int int_array[kMaxSize] = { 75, 41, 38, 11, 11,87 };
	int int_array[kMaxSize];

	for (int k = 0; k<kMaxSize; k++)
	{
		*(int_array + k) = rand() % kMaxValue;
	};
	print_array(int_array);

	FastSort sort_app;
	sort_app.fast_sort(int_array);

	print_array(int_array);
}

//1 pivot选左边第一个元素，则从右边游标开始，right--
//2 两边游标移动 判断条件 buffer[*] >=(<=)是为了处理重复元素的case
//3 函数宏观来看是一个swap操作
//4 一次part_impl执行完成后pos位置的元素 完成归位（放到了排序以后的结果序列位置中去）
template<typename Type>
int FastSort::part_impl(Type* buffer, int left, int right)
{
	Type pivot = buffer[left];

	while (left < right)
	{
		while (right > left && buffer[right] >= pivot)
			--right;

		buffer[left] = buffer[right];
		
		while (left < right && buffer[left] <= pivot)
			++left;

		buffer[right] = buffer[left];
	}

	buffer[left] = pivot;
	
	return left;
}

template<typename Type>
void FastSort::sort_impl(Type* buffer, int begin, int end, int length)
{
	int pos = part_impl(buffer, begin, end);	// pos位置的元素已经归位！

	print_array(buffer, length);

	if (begin < pos-1)
	{
		sort_impl(buffer, begin, pos - 1, length);
	}

	if (pos + 1 < end)
	{
		sort_impl(buffer, pos + 1, end, length);
	}
}

template<typename Type, int SIZE>
void FastSort::fast_sort(Type(&buffer)[SIZE])
{
	sort_impl(buffer, 0, SIZE - 1, SIZE);
}

