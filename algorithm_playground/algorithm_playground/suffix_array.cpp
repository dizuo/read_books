#include "xshare.h"

void sa_unit_test_case();

#ifdef SUFFIX_ARRAY

int main()
{
	sa_unit_test_case();

	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}

#endif

// 二级指针
int str_cmp_func(const void* p1, const void* p2)
{
	char* pstr1 = *(char**)p1;
	char* pstr2 = *(char**)p2;

	int ret = strcmp(pstr1, pstr2);
	printf("%s, %s = %d\n", pstr1, pstr2, ret);

	return ret;
}

// 一级指针
int ch_cmp_func(const void* p1, const void* p2)
{
	return *(char*)p1 - *(char*)p2;
}

void sa_unit_test_case()
{
	char str[] = "peteryfren";

	int len = strlen(str);
	char** suffix_array_ptr = (char**)malloc(sizeof(char*) * len);

	for (int i = 0; i < len; i++)
	{
		suffix_array_ptr[i] = str + i;

		for (int k = 0; k < i; k++) printf(" ");

		printf("%s\n", suffix_array_ptr[i]);
	}
	
	qsort(suffix_array_ptr, len, sizeof(char*), str_cmp_func);

	for (int i = 0; i < len; i++)
	{
		int loc_len = strlen(suffix_array_ptr[i]);
		for (int k = 0; k < len - loc_len; k++) printf(" ");

		printf("%s\n", suffix_array_ptr[i]);
	}

	free(suffix_array_ptr);

	qsort(str, strlen(str), sizeof(str[0]), ch_cmp_func);
	printf("%s\n", str);

}