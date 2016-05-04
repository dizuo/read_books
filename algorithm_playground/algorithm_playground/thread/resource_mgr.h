#ifndef RES_MGR_H
#define RES_MGR_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

// shared_ptr, weaked_ptr
#include <memory>

using namespace std;

#define MAIN_T
#define DATA_T

enum State
{
	None,
	Loading,
	Loaded,
	Dead
};

class Resource
{
public:

	Resource() : mSt(None)
	{
		sCounter++;
		mId = sCounter;
	}

	~Resource()
	{
		sCounter--;
	}

	virtual DATA_T bool load() { return true; }

	void SetState(State st) { mSt = st; }
	State getState() { return mSt; }

	int getId() { return mId; }

private:

	static int sCounter;

	State mSt;
	int mId;
};

// ImageMaker

class ImageLoader : public Resource
{
public:

	ImageLoader() : Resource() {}

	bool load();

};

// DrawTile
// DrawText

class ResourceManager
{
public:

	typedef std::shared_ptr<Resource>	share_t;
	typedef std::weak_ptr<Resource>	weak_t;

	ResourceManager();
	~ResourceManager();

	DATA_T void handleTasks();

	// share_t addResource(Resource key)	// 重复请求会增加share_t的引用计数

	MAIN_T void addResourceRequest(Resource* res);

	MAIN_T void removeResource(Resource* res);
	
	MAIN_T void renderResource();

	static void smart_test();
	static void unit_test();

private:

	// http://en.cppreference.com/w/cpp/thread
	std::mutex mMutex;

	vector< share_t > resources;
	vector< weak_t > to_load_vec;

};

// 一次

#endif