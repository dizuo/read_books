#define _CRT_SECURE_NO_WARNINGS

#include "xshare.h"

#include <vector>
#include <map>

void lt_unit_test();

#ifdef LOG_TEMPLATE
DECLARE_MAIN_ENTRY(lt_unit_test);
#endif

typedef std::map<std::string, std::string> map_t;

void trim_char(char* pbuf, char ch);
void split(char* pbuf, map_t& kv_mp);

void lt_unit_test()
{
	char my_str[] = "blockid = 27,  2, 10 & datasize:1423 | maprect = 224657408_109838336_224919552_110100480";

	puts(my_str);
	trim_char(my_str, ' ');
	puts(my_str);

	map_t res;
	split(my_str, res);

}

void trim_char(char* pbuf, char ch)
{
	char* pslow = pbuf;
	char* pfast = pbuf;
	while (*pfast)
	{
		if (*pfast == ch)
		{
			++pfast;
		}
		else
		{
			*pslow++ = *pfast++;
		}
	}
	*pslow = '\0';
}

// trim space chars.
// cell_token = "&|"
// item_token = "=:"
// val_token = ",_"
// 
void split(char* pbuf, map_t& kv_mp)
{
	// cell_token = "&|"
	// item_token = "=:"
	// val_token = ",_"
	// 
	const char* cell_token = "&|";
	const char* item_token = "=:";
	const char* val_token = ",_";

	char* pch = strtok(pbuf, cell_token);

	std::vector<char*> sections;

	printf("--------------------->\n");

	while (pch)
	{
		puts(pch);

		sections.push_back(pch);

		pch = strtok(NULL, cell_token);
	}

	printf("--------------------->\n");
	for (int k = 0; k < sections.size(); k++)
	{
		char* pch = sections[k];

		char* pkey = strtok(pch, item_token);
		char* pval = strtok(NULL, item_token);

		printf("key=%s, ", pkey);

		char* ptmp = strtok(pval, val_token);
		printf("val = %s,", ptmp);

		while (ptmp)
		{
			ptmp = strtok(NULL, val_token);
			if (ptmp)
				printf("%s,", ptmp);
		}

		printf("\n");
	}
}

