#include "xshare.h"

using namespace std;

int fulfill_with_1(int a);

int get_one_num(int value);
int get_binary_one_num(int value);
void x1_unit_test_case();

#ifdef BINARY_MAIN
int main()
{
	x1_unit_test_case();
	
	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}
#endif

void x1_unit_test_case()
{
	for (int i = 0; i < 10; i++)
	{
		printf("[ %d ] num = %d\n", i, get_one_num(i));

		if (get_binary_one_num(i) != get_one_num(i))
		{
			printf("ERROR\n");
		}
	}

	int var = 4;
	if (7 != fulfill_with_1(var))
	{
		printf("ERROR\n");
	}

	var = 16;
	if (31 != fulfill_with_1(var))
	{
		printf("ERROR\n");
	}

}

int get_one_num(int value)
{
	int count = 0;
	while (value)
	{
		count += (value & 0x1);
		value >>= 1;
	}

	return count;
}

int get_binary_one_num(int value)
{
	int count = 0;
	while (value)
	{
		value = (value - 1) & value;
		count++;
	}

	return count;
}

// 把a中高位第一个1后面所有位都用1填充
int fulfill_with_1(int a)
{
	a |= a>>1;
	a |= a>>2;
	a |= a>>4;
	a |= a>>8;
	a |= a>>16;

	return a;
}



