#include "xshare.h"

using namespace std;

int fulfill_with_1(int a);

int get_one_num(int value);
int get_binary_one_num(int value);
void x1_unit_test_case();

template<class Type>
void dump_val_hex_loop(Type val)	// 0xfc000000 => printf : 00 00 00 fc
{
	while (val)
	{
		unsigned char low_byte = val & 0xFF;
		// printf("0x%02x ", low_byte);
		printf("%02x ", low_byte);

		val = (val >> 8);
	} printf("\n");
}

template<class Type> void dump_val_hex_recur(Type val)	
{
	if (val == 0)
	{
		return;
	}

	unsigned char byte = val & 0xFF;

	dump_val_hex_recur(val >> 8);

	printf("%02x ", byte);
}

template <class Type> void dump_val_hex(Type val) // 0xfc000000 => printf : fc 00 00 00	
{
	if (val == 0)
	{
		printf("%02x\n", 0);
		return;
	}

	dump_val_hex_recur(val); printf("\n"); 
}

void dump_hex_val_test();

#ifdef BINARY_MAIN
int main()
{
	x1_unit_test_case();
	dump_hex_val_test();
	
	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}
#endif

void dump_hex_val_test()
{
	printf("======================>dump_hex_val_test\n");

	dump_val_hex(0x0);

	dump_val_hex(0xfe00);

	dump_val_hex(0xfe0000);

	dump_val_hex(0xfe000000);

	dump_val_hex(0xfe00fe);
}

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

	unsigned char buf[] = { 8, 190, 65, 252, 0, 0, 0, 0 };
	union xx
	{
		unsigned long long val;
		unsigned char arr[8];
	};

	xx test;
	test.val = 4232166920;

	unsigned int ui_val = test.val;

	unsigned int ival = 0x000000fc << 24;
	dump_val_hex(ival);

	unsigned long long max_val = 0xffffffffffffffff;
	dump_val_hex(max_val);

	unsigned long long val = 0xfcULL << 24;	
	dump_val_hex(val);

	val = 0xfcUL << 8;
	
	val = 0xfc00 >> 8;
	dump_val_hex(val);

	val = 0xfc000000;
	dump_val_hex(val);

	val = buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);	// error
	dump_val_hex(val);

	val = (unsigned int)( buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24) );	// good
	dump_val_hex(val);

	val = 0;
	for (int k = 0; k < sizeof(buf); k++)
	{
		val += ( buf[k] << (8*k) );
	}

	int stop = 0;

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



