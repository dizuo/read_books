#ifndef RES_MGR_H
#define RES_MGR_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>

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

	bool load();

};

// DrawTile
// DrawText

class ResourceManager
{
public:

	ResourceManager();
	~ResourceManager();

	DATA_T void handleTasks();

	MAIN_T void addResourceRequest(Resource* res);

	MAIN_T void removeResource(Resource* res);

private:

	std::mutex mMutex;

	vector<Resource*> toLoadVec;
	vector<Resource*> loadedVec;

};

// Ò»´Î

#endif