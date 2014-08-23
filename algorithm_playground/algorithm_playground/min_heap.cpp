#include "xshare.h"

using namespace std;

template< typename Type, int SIZE>
void make_min_heap( Type (&buffer)[SIZE] );

template< typename Type, int SIZE>
bool check_min_heap(Type(&buffer)[SIZE]);

int go_far_left(int fath, int num);
void mh_unit_test_case();

#ifdef HEAP_MAIN

DECLARE_MAIN_ENTRY(mh_unit_test_case);

#endif

void mh_unit_test_case()
{
	srand( time(NULL) );
	
	const int kMaxSize = 51;
	const int kMaxValue = 100;
	
	int int_array[kMaxSize];
	
	for (int k=0; k<kMaxSize; k++)
	{
		*(int_array + k) = rand() % kMaxValue;
	};
	print_array(int_array);

	// make_min_heap(int_array);

	print_array(int_array);
	
	if (check_min_heap(int_array))
	{
		cout << "Good Min Heap\n";
	}

}

// process negative case.
int left_child(int fath) 	{	return (fath << 1) + 1; }
int right_child(int fath) {	return (fath + 1) << 1;	}
int father(int chld) 		{	return (chld >> 1) - 1; }

int go_far_left(int fath, int num)	
{
	typedef int vt;

	vt pos = left_child(fath);
	vt ret_pos = pos;
	
	while (pos < num)
	{
		ret_pos = pos;
		pos = left_child(pos);	
	}

	return ret_pos;
}

template< typename Type>
void swap(Type& left, Type& right) 
{
	Type tmp = left; left = right; right = tmp;
}

// 注意是向下调整，cur = 5只负责后代结点。 cur = 0的时候可能会再次调整cur = 5的后代。
template< typename Type, int SIZE>
void adjust_down_heap(Type(&buffer)[SIZE], int cur)
{
	typedef int vt;

	vt left = left_child(cur);
	
	while (left < SIZE)
	{
		vt right = left + 1;
		vt pos = left;
		
		if (right < SIZE && buffer[right] < buffer[left])
		{
			pos = right;
		}

		if (buffer[cur] > buffer[pos])
		{
			::swap(buffer[cur], buffer[pos]);
		}
		else
		{
			break;
		}

		cur = pos;	// 继续向下调整
		left = left_child(cur);	
	}
	
}

// 后序遍历树，调整小顶堆
//	最后一个非叶子节点 N/2 - 1
template< typename Type, int SIZE>
void make_min_heap(Type(&buffer)[SIZE])
{
	int last_fath = SIZE / 2 - 1;
	for (int iter = last_fath; iter >= 0; iter--)
	{
		adjust_down_heap(buffer, iter);
	}
	
}

template< typename Type, int SIZE>
bool check_min_heap(Type(&buffer)[SIZE])
{
	int last_fath = SIZE / 2 - 1;
	
	int iter = 0;
	for ( ; iter <= last_fath; iter++)
	{
		int left = left_child(iter);
		int right = right_child(iter);

		int pos = left;
		if (right < SIZE && buffer[left] < buffer[right])
		{
			pos = right;
		}
		if (buffer[iter] > buffer[pos])
		{
			cout << "error in " << iter << endl;
			break;
		}
	}

	return iter > last_fath;
}

