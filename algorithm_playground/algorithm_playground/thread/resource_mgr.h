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

	DATA_T bool load();

	void SetState(State st) { mSt = st; }
	State getState() { return mSt; }

	State mSt;
};

// ImageMaker
// ImageLoaded
// DrawTile
// DrawText

class ResourceManager
{
public:

	DATA_T void handleTasks();

	MAIN_T void addResourceRequest(Resource* res);

private:

	std::mutex mMutex;

	vector<Resource*> toLoadVec;
	vector<Resource*> loadedVec;

};

// Ò»´Î

#endif