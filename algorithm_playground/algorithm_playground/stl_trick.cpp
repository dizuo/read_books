#include "xshare.h"

#include <vector>
#include <string>
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

void stl_trick_unit_test()
{
	vector_grow_test();
}
