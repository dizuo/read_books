#include <iostream>
#include <cassert>
using namespace std;

/*
#python
#np++

res = 0
x = 1
while x < 9:
	res = (res<<4) | x

	str = bin(res)[2:]
	xlen = 4 - len(str) % 4
	prefix = ''
	for i in range(xlen):
	prefix += '0'
	print res, prefix + str

	x = x + 1
*/

// index 和 msc 都是unsigned 循环移位

template<class KEY, class VALUE>
class LRUCache
{
	enum
	{
		SIZE = 8,
	};
public:
	struct  cache_slot
	{
		KEY   key;
		VALUE val;
	};

private:
	unsigned    index;        //  We will use this to store the order in 1 based nibbles.
	//  0 will be used for unasigned cache slots
	//  We will store de most recent accesed index on the least 
	//  significant bit.
	cache_slot  cache[SIZE];

public:
	LRUCache() : index(0) {}

	inline  void  reset()
	{
		index = 0;
	}

	inline  bool  find(const  KEY& _key, VALUE& val_)
	{
		unsigned    msc = 0xffffffff; // auxiliary value we need to move one nibble from the middle
		// of the dword to the begining 
		unsigned    idx = index;
		cache_slot* ptr = (cache - 1);  // prepare to access on 1 based index's
		while (idx)
		{
			unsigned hit = idx & 0xf;
			//assert(hit<=8);
			msc <<= 4;
			if (ptr[hit].key == _key)
			{
				//  key found, we move it to the "begining" so we find it faster next time.
				index = (index&msc) | ((index << 4)&(~msc)) | hit;
				val_ = ptr[hit].val;
				return(true);
			}
			idx >>= 4;
		}
		return(false);
	}

	inline  void  insert(const  KEY& _key, const VALUE& _val)
	{
		cache_slot* ptr = cache - 1;    // prepare to access on 1 based index's
		unsigned    hit = index >> 28;  // we remove the most significant nibble from the index table
		if (!hit)    //  only when filling de cache.
		{
			hit = 1;
			unsigned idx = index;
			while (idx & 0xf)  { idx >>= 4, ++hit; }
			//assert(hit<=SIZE);
		}
		ptr[hit].key = _key;
		ptr[hit].val = _val;
		index = (index << 4) | hit;
		return;
	}

};

void main()
{
	LRUCache<int,int>  lru;

	lru.reset();

	int runs = 1000;
	int range = 256;
	int hits = 0;
	for (int i = 0; i < 500; ++i)
	{
		if (i == 8)
		{
			int s = 0;
		}

		int key = rand() % range;
		// int key = i % range;
		int val = -1;
		if (!lru.find(key, val))
		{
			lru.insert(key, key);
			printf("%d ", key);
		}
		else
		{
			assert(key == val);
			++hits;
		}
	}
	
	printf("any key pressed to exit...\n");
	getchar();

}

