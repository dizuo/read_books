#include "xshare.h"

void str_trim(char* src_str, char* token);

void str_unit_test_case();

#ifdef STRING_MAIN

DECLARE_MAIN_ENTRY(str_unit_test_case);

#endif

void str_unit_test_case()
{
	char str[] = "dizuo renyafei";
	char* token = "def";

	printf("source string = %s\n", str);
	str_trim(str, token);
	printf("trimmed string = %s\n", str);

	str_trim(NULL, token);
	str_trim(token, NULL);

	str[0] = '\0';
	str_trim(str, token);
	printf("trimmed string = %s\n", str);

}

void str_trim(char* src_str, char* token)
{
	if (!src_str || !token)
	{
		return;
	}

	char hash[256] = { 0 };
	char* curp = token;
	while (*curp) 
	{
		hash[*curp++] = 1;
	}

	char* fastp = src_str;
	char* slowp = src_str;

	while (*fastp)
	{
		if (hash[*fastp] == 1)
		{
			++fastp;
			continue;
		}

		*slowp++ = *fastp++;
	}
	*slowp++ = '\0';

}

