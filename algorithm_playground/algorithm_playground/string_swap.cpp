#include "xshare.h"

using namespace std;

void unit_test_case();

void swap_string(char* pstr);

#ifdef STRING_SWAP_MAIN

int main()
{
	unit_test_case();

	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}

#endif

void unit_test_case()
{
	char buffer[] = "hello world, i am a good man.";
	printf("0 : %s\n", buffer);
	swap_string(buffer);
	
	char short_buf[] = "one";
	printf("0 : %s\n", short_buf);
	swap_string(short_buf);
}

void inverse_string(char* pbeg, char* pend)
{
	if (!pbeg || !pend)
	{
		return;
	}

	while (pbeg < pend)
	{
		std::swap(*pbeg, *pend);
		++pbeg;
		--pend;
	}
}

void swap_string(char* pstr)
{
	if (!pstr)
	{
		return;
	}

	int str_len = strlen(pstr);
	char* pbeg = pstr;
	char* pend = pstr + str_len - 1;
	
	inverse_string(pbeg, pend);
	printf("1 : %s\n", pstr);

	pbeg = pstr;
	for (char* pch = pstr; *pch; pch++)
	{
		if (pch == pend || *(pch+1) == ' ')
		{
			inverse_string(pbeg, pch);
			pbeg = pch + 2;
		}
	}
	
	printf("2 : %s\n", pstr);

}


