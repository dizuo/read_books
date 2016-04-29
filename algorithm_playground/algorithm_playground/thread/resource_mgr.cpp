#include "resource_mgr.h"

void ResourceManager::handleTasks()
{
	// release dead/

	Resource* missions[3];

	int num = 0;

	mMutex.lock();
	for (int k = 0; k < toLoadVec.size(); k++)
	{
		if (num >= 3)
			break;
		missions[num++] = toLoadVec[k];
	}

	toLoadVec.erase(toLoadVec.begin(), toLoadVec.begin() + num);
	mMutex.unlock();

	for (int k = 0; k < num; k++)
	{
		Resource* res = missions[k];
		if (res->getState() != None)
		{
			continue;
		}

		if (res->load())
		{
			res->SetState(Loaded);
		}

		loadedVec.push_back(res);
	}
}