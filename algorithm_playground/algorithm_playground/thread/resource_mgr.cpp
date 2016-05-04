#include "resource_mgr.h"

#include <functional>
#include <algorithm>
#include <iostream>
using namespace std;

int Resource::sCounter = 0;

bool ImageLoader::load()
{
	printf("load exec...\n");
	std::this_thread::sleep_for(chrono::seconds(3));

	return true;
}

ResourceManager::ResourceManager()
{
}

#define DESTROY_VECTOR(vec) \
	for (int k = 0; k < vec.size(); k++) \
	{ \
		if (vec[k]) \
		{ \
			delete vec[k]; \
			vec[k] = 0; \
		} \
	}

ResourceManager::~ResourceManager()
{
	resources.clear();
	to_load_vec.clear();
}

void ResourceManager::removeResource(Resource* res)
{

}

void ResourceManager::addResourceRequest(Resource* res)
{
	std::lock_guard<std::mutex> lock(mMutex);
	
	// 在resource中查找是否重复

	share_t sp(res);
	resources.push_back(sp);
	to_load_vec.push_back( weak_t(sp) );

	res->SetState(Loading);
}

void ResourceManager::handleTasks()
{
	// release dead/
	weak_t missions[3];

	int num = 0;
	mMutex.lock();
	for (int k = 0; k < to_load_vec.size(); k++)
	{
		if (num >= 3)
			break;

		missions[num++] = to_load_vec[k];
	}

	to_load_vec.erase(to_load_vec.begin(), to_load_vec.begin() + num);
	mMutex.unlock();

	for (int k = 0; k < num; k++)
	{
		if (missions[k].expired())
			continue;
		share_t pres = missions[k].lock();

		if (pres->getState() != Loading)
		{
			continue;
		}
		if (pres->load())
		{
			pres->SetState(Loaded);
		}

	}

	printf("exit data thread...\n");	// Not safe.

}

// lambda : http://www.cnblogs.com/hujian/archive/2012/02/14/2350306.html

void ResourceManager::renderResource()
{
	int pass = 0;
	while (true)
	{
		int items = 0;

		for_each(resources.begin(), resources.end(), [&items](const share_t& sp) {
			if (sp->getState() == Loaded)
			{
				cout << "finish loaded resource " << sp->getId() << endl;
				items++;
			}
		});

		if (items == resources.size())
		{
			printf("Main thread run waiting for %d times...\n", pass);
			break;
		}

		pass++;
	}
}

void ResourceManager::unit_test()
{
	ResourceManager resMgr;

	resMgr.addResourceRequest(new ImageLoader());
	resMgr.addResourceRequest(new ImageLoader());

	std::thread data_thread(std::mem_fn(&ResourceManager::handleTasks), &resMgr);
	data_thread.detach();

	resMgr.renderResource();

	printf("prepare to exit main thread...\n");
}

void ResourceManager::smart_test()
{
#if 0
	shared_ptr<int> sptr(new int(100));

	weak_ptr<int> wptr(sptr);

	auto ptest = wptr.lock();
	shared_ptr<int> xx = wptr.lock();

	int times = ptest.use_count();	// 3
#endif

	weak_ptr<int> wptr;

	{
		shared_ptr<int> sptr(new int(100));

		int val = *sptr;

		wptr = sptr;		// _Ptr, _Rep, 

		auto ptest = wptr.lock();
		shared_ptr<int> xx = wptr.lock();
		int times = sptr.use_count();

		bool isempty = wptr.expired();

	}

	bool isempty = wptr.expired();

	auto ptest = wptr.lock();
	int times = ptest.use_count();

	int val = *(wptr._Get());		// bad value.

}
