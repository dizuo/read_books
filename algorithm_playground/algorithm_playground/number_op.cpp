#include "xshare.h"

void nb_unit_test_case();
void get_sequence_with_sum(int sum);
void rearrage_array(int(&buffer)[10], int length);

#ifdef NUMBER_MAIN

int main()
{
	nb_unit_test_case();

	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}

#endif

void nb_unit_test_case()
{
	srand(time(NULL));

	const int kMaxSize = 10;
	const int kMaxValue = 100;
	int buffer[kMaxSize];

	for (int k = 0; k < kMaxSize; k++)
	{
		buffer[k] = rand() % kMaxValue;
		printf("%d ", buffer[k]);
	} printf("\n");

	rearrage_array(buffer, kMaxSize);
	
	print_array(buffer);

}

void get_sequence_with_sum(int sum)
{
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