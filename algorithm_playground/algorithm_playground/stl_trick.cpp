#include "xshare.h"

#include <vector>
#include <string>
#include <locale>

#include <fstream>  
#include <map>  
#include <sstream>  
#include <iostream>  

using namespace std;

void stl_trick_unit_test();

#ifdef STL_TRICK
DECLARE_MAIN_ENTRY(stl_trick_unit_test);
#endif

void vector_grow_test()
{
	int _MaxSize = 1073741823;
	int _Capacity = 0;

	for (int k = 0; k < 500; k++)
	{
		if (k + 1 <= _Capacity)
		{
			continue;
		}

		if (_Capacity < 2)
		{
			_Capacity++;
			continue;
		}

		_Capacity = _MaxSize - _Capacity / 2 < _Capacity
			? 0 : _Capacity + _Capacity / 2;	// try to grow by 50%
		printf("%d ", _Capacity);
	}

}

void cin_test()
{
	typedef ctype<char> ctype_t; 	std::locale loc;
	for (int k = 0; k < 128; k++)
		if (use_facet<ctype_t>(loc).is(ctype_t::space,  k))
			cout << k << ",";

	typedef std::string str_t;
	str_t key, value;
	cin >> key >> value;
	cout << "key = " << key << endl;
	cout << "value = " << value << endl;

}

void stl_trick_unit_test()
{
	cin_test();

	vector_grow_test();
}
