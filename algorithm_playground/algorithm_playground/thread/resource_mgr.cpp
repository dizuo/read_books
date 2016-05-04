#include "resource_mgr.h"

#include <functional>
#include <algorithm>
#include <iostream>
using namespace std;

int Resource::sCounter = 0;

void dbg_printf(const char *fmt, ...)
{
	static mutex smutex;
	smutex.lock();

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	smutex.unlock();
}

bool ImageLoader::load()
{
	dbg_printf("load exec...%d\n", getId());
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

void ResourceManager::deleteResource(share_t& pres)
{
	std::lock_guard<std::mutex> lock(mMutex);

	map<str_t, share_t>::iterator it = resources.begin();
	while (it != resources.end() && it->second != pres)
		it++;
	if (it == resources.end())
		return;

	dbg_printf("delete resource %s : %d\n", it->first.c_str(), it->second->getId());
	resources.erase(it);

	// clear Resource refercen in to_load_vec.
	// vector<weak_t>::iterator xit = to_load_vec.begin();
	// 
}

ResourceManager::share_t ResourceManager::createResource()
{
	return createResourceImpl();
}

ResourceManager::share_t ResourceManager::addResource(const str_t& key)
{
	std::lock_guard<std::mutex> lock(mMutex);
	
	share_t pres;

	map<str_t, share_t>::iterator iter = resources.find(key);
	if (iter == resources.end())
	{
		pres = createResource();
		
		resources.insert(std::make_pair(key, pres));		
		pres->SetState(Loading);

		to_load_vec.push_back(weak_t(pres));
	}
	else
	{
		pres = iter->second;
	}

	return pres;
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
	std::lock_guard<std::mutex> lock(mMutex);
	
	int pass = 0;
	while (true)
	{
		int items = 0;

		for (const auto& kv : resources) 
		{
			if (kv.second->getState() == Loaded)
			{
				// cout << "finish loaded resource " << kv.second->getId() << endl;
				items++;
			}
		}

#if 0
		for_each(resources.begin(), resources.end(), [&items](const share_t& sp) {
			if (sp->getState() == Loaded)
			{
				cout << "finish loaded resource " << sp->getId() << endl;
				items++;
			}
		});
#endif

		if (items == resources.size())
		{
			printf("Main thread run waiting for %d times...\n", pass);
			break;
		}

		pass++;
	}
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

ImageManager::share_t ImageManager::createResourceImpl()
{
	dbg_printf("create imageloaded\n");
	return share_t(new ImageLoader());
}

// create resource.
// use resource if loaded.
// destroy resource.

void ImageManager::unit_test()
{
	ResourceManager* resMgr = new ImageManager();

	typedef ImageManager::share_t share_t;
	share_t pres1 = resMgr->addResource("first");
	share_t pres2 = resMgr->addResource("second");
	share_t pres3 = resMgr->addResource("first");

	std::thread data_thread(std::mem_fn(&ImageManager::handleTasks), resMgr);
	data_thread.detach();

	resMgr->deleteResource(pres3);

	resMgr->renderResource();

	printf("prepare to exit main thread...\n");

	delete resMgr;
}
