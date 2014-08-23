#include "xshare.h"

void nb_unit_test_case();
void get_sequence_with_sum(int dst_sum);
void rearrage_array(int(&buffer)[10], int length);

// C语言的取模：http://blog.csdn.net/yingbinchina/article/details/2715549
void c_mod_test();

#ifdef NUMBER_MAIN

DECLARE_MAIN_ENTRY(nb_unit_test_case);

#endif

void nb_unit_test_case()
{
	srand((unsigned int)(time(NULL)));

	const int kMaxSize = 10;
	const int kMaxValue = 100;
	int buffer[kMaxSize];

	int dst_sum = 15;
	printf("sum equal [%d], sequences are : \n", dst_sum);
	get_sequence_with_sum(dst_sum);

	for (int k = 0; k < kMaxSize; k++)
	{
		buffer[k] = rand() % kMaxValue;
		printf("%d ", buffer[k]);
	} printf("\n");

	rearrage_array(buffer, kMaxSize);
	
	print_array(buffer);

	int arr[5] = { 1, 2, 3, 2, 1 };
	int res = arr[0];
	for (int iter = 1; iter < 5; iter++)
	{
		res ^= arr[iter];
	}
	printf("res = %d\n", res);
	
	c_mod_test();

}

void get_sequence_with_sum(int dst_sum)
{
	int left = 0;
	int right = 0;
	long long sum = 0;
	while (right < dst_sum)
	{
		if (sum == dst_sum)
		{
			for (int k = left; k < right; k++) printf("%d\t", k);
			printf("\n");
		}

		if (sum < dst_sum)
		{			
			sum += right;
			right++;

			continue;
		}

		sum -= left;
		++left;
	}

}

void rearrage_array(int(&buffer)[10], int length)
{
	int left = 0;
	int right = length - 1;

	int temp = 0;

	while (left < right)
	{
		while (left < right && buffer[left] % 2 == 0)	// 
		{
			++left;
		}

		temp = buffer[left];

		while (right > left && buffer[right] % 2 == 1)	// 
		{
			--right;
		}		

		buffer[left] = buffer[right];
		buffer[right] = temp;

	}

}

void mod_impl(int a, int b)
{
	if (!b)
	{
		printf("%d\tmod\t%d\t#ERROR\n", a, b);
		return;
	}

	printf("%d\tmod\t%d\t=\t%d\n", a, b, (a%b));
}

// a = b * (a/b) + (a % b)

void c_mod_test()
{
	printf("===C_MOD_TEST===\n");

	// # a, b 同号 #

	// a > 0 , b > 0
	mod_impl(5, 3);	// a > b
	mod_impl(5, 8);	// a < b
	mod_impl(0, 3);	// a == 0
	mod_impl(5, 0);	// b == 0

	// a < 0 , b < 0
	mod_impl(-5, -3);	// a < b
	mod_impl(-5, -8);	// a > b
	mod_impl(0, -3);	// a == 0
	mod_impl(-5, 0);	// b == 0

	// # a, b 异号

	// a < 0 , b > 0
	mod_impl(-5, 3);	
	mod_impl(-5, 8);	
	
	// a > 0 , b < 0
	mod_impl(5, -3);	
	mod_impl(5, -8);

	printf("===C_MOD_TEST===\n");

}
