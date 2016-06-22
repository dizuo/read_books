#include "../xshare.h"

#include <thread>
#include <iostream>
#include <mutex>
#include <future>

#include <random>

#include <vector>
#include <stdlib.h>

#include "resource_mgr.h"

using namespace std;

void thread_main_entry();

void custom_test();
void simple_test();
void threadAsync();

#ifdef CPP11_THREAD_
DECLARE_MAIN_ENTRY(thread_main_entry)
#endif

class Base
{
public: 
	Base() {
		printf("base contr\n");
	}
	virtual ~Base() {
		printf("base destr\n");
	}
};

class Derive : public Base
{
public:

	Derive() {
		printf("derive contr\n");
	}

	~Derive() {
		printf("derive destr\n");
	}

};

void thread_main_entry()
{

	Base* ptr = new Derive();
	delete ptr;

	// simple_test();

	// threadAsync();
	
	typedef unsigned char GLubyte;
	int wid = 10;
	int hgh = 10;
	GLubyte* bytes = new GLubyte[wid * hgh * 4];
	for (int j = 0; j < hgh; j++)
	{
		for (int i = 0; i < wid; i++)
		{
			int low = i < wid/2 ? 0 : 1;
			int hghx = j < hgh/2 ? 0 : 1;

			int index = (hghx << 1) | (low);
			
			printf("%d ", index);
		}
		printf("\n");
	}
	printf("\n");

	custom_test();

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void custom_test()
{
	// add request.
	// ResourceManager::smart_test();
	
	ImageManager::unit_test();

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

static long
do_sum(vector<long> *arr, size_t start, size_t count){
	static mutex _m;
	long sum = 0;
	for (size_t i = 0; i < count; i++){
		sum += (*arr)[start + i];
	}
 {
	 lock_guard<mutex> _(_m);
	 cout << "thread " << this_thread::get_id()
		 << ", count=" << count
		 << ", sum=" << sum << endl;
 }
 return sum;
}
static void
threadAsync(){
# define COUNT 1000000
	vector<long> data(COUNT);
	for (size_t i = 0; i < COUNT; i++){
		data[i] = rand() & 0xff;
	}
	//
	vector< future<long> > result;
	size_t ptc = thread::hardware_concurrency() * 2;
	for (size_t batch = 0; batch < ptc; batch++){
		size_t batch_each = COUNT / ptc;
		if (batch == ptc - 1){
			batch_each = COUNT - (COUNT / ptc * batch);
		}
		result.push_back(async(do_sum, &data, batch * batch_each, batch_each));
	}
	long total = 0;
	for (size_t batch = 0; batch < ptc; batch++){
		total += result[batch].get();
	}
	cout << "total=" << total << endl;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void simple_test()
{
	std::mutex m;

	thread t1([&m]()
	{
		std::this_thread::sleep_for(chrono::seconds(1));

		for (int i = 0; i<10; i++)
		{
			m.lock();
			cout << "In t1 ThreadID : " << std::this_thread::get_id() << ":" << i << endl;
			m.unlock();
		}
	});

	thread t2([&m]()
	{
		std::this_thread::sleep_for(chrono::seconds(1));
		for (int i = 0; i < 10; i++)
		{
#if V0
			m.lock();
			cout << "In t2 ThreadID : " << std::this_thread::get_id() << ":" << i << endl;
			m.unlock();
#else
			if (m.try_lock())
			{
				cout << "In t2 ThreadID : " << std::this_thread::get_id() << ":" << i << endl;
				m.unlock();
			}
#endif
		}
	});

	t1.join();
	t2.join();

	cout << "Main Thread" << endl;

}