#include "xshare.h"

#include <deque>
#include <vector>
using namespace std;

// http://zhedahht.blog.163.com/blog/static/25411174200732102055385/

void pp_unit_test_case();
void make_permutation(string& str, int k, int maxPos, vector<string>& perm_vec);
bool is_push_pop_sequence(string& seq_str, string& src_str);
void make_child_set(const char* str, vector<char>& res_set);

int gcd(int a, int b)
{
	if (a > b)
		::swap(a, b);

	// a < b
	while (!a)
	{
		int tmp = b % a;	// tmp < a 
		b = a;
		a = tmp;
	}

	return b;
}

#ifdef SEQUENCE

int main()
{
	pp_unit_test_case();
	
	printf("any key pressed to exit...\n");
	getchar();

	return 0;
}

#endif

// ref : http://blog.csdn.net/morewindows/article/details/7370155/
void make_permutation(string& str, int k, int maxPos, vector<string>& perm_vec)
{
	if (k == maxPos)
	{
		printf("%s\t", str.c_str());
		perm_vec.push_back(str);
	}
	else
	{
		for (int i = k; i <= maxPos; i++)
		{
			::swap(str[k], str[i]);
			
			make_permutation(str, k + 1, maxPos, perm_vec);

			::swap(str[k], str[i]);
		}
	}
}

bool is_push_pop_sequence(string& seq_str, string& src_str)
{
	deque<char> ch_stack;

	size_t idx = 0;
	size_t cursor = 0;

	while (idx < seq_str.size())
	{
		char ch = seq_str[idx];

		if (ch_stack.size() > 0 && ch_stack.back() == ch)
		{
			ch_stack.pop_back();
			idx++;
			continue;
		}

		size_t k = cursor;
		for (; k < src_str.size() && src_str[k] != ch; k++) ;
		if (k == src_str.size())
		{
			break;
		}
		
		for (int p = cursor; p <= k; p++)
		{
			ch_stack.push_back(src_str[p]);
		}

		cursor = k + 1;
		ch_stack.pop_back();

		idx++;
	}

	return idx == seq_str.size();

}

void make_child_set(const char* str, vector<char>& res_set)
{
	if (*str == '\0')
	{
		// if (res_set.size() == 5)
		{
			for (size_t k = 0; k < res_set.size(); k++) cout << res_set[k];
			cout << endl;
		}
		return;
	}

	res_set.push_back(str[0]);
	make_child_set(str + 1, res_set);

	res_set.pop_back();
	make_child_set(str + 1, res_set);
}

void pp_unit_test_case()
{
	// make 1-5 all child set.
	const char* str = "12345";
	vector<char> res_vec;

	// make_child_set(str, res_vec);

	vector<string> perm_vec;
	string src_str("1234");
	make_permutation(src_str, 0, src_str.size() - 1, perm_vec);
	printf("\n");	
	
	for (size_t iter = 0; iter != perm_vec.size(); iter++)
	{
		string& case_str = perm_vec[iter];
		if (is_push_pop_sequence(case_str, src_str))
		{
			printf("\"%s\" = TRUE\n", case_str.c_str());
		}
		else
		{
			printf("\"%s\" = FALSE\n", case_str.c_str());
		}
	}

}
