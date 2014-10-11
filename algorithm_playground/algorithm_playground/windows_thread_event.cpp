#include "xshare.h"

// http://www.codeproject.com/Articles/438/Introduction-to-Multi-threaded-Code
// http://www.codeproject.com/Articles/111/CThread-a-Worker-Thread-wrapper-class
// http://www.codeproject.com/Articles/21114/Creating-a-C-Thread-Class

#include <windows.h>
#include <process.h>
#include <stdio.h>

HANDLE hEvent1, hEvent2;
int a[5];

void Thread(void* pParams)
{
	int i, num = 0;

	while (TRUE)
	{
		WaitForSingleObject(hEvent2, INFINITE);
		for (i = 0; i < 5; i++) a[i] = num;
		
		printf("work_thread notify main thread.\n");

		SetEvent(hEvent1);
		num++;

		::Sleep(1000);

	}
}

#ifdef WINDOWS_THREAD_EVENT

int main(void)
{
	hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
	hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);

	_beginthread(Thread, 0, NULL);

	while (TRUE)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		printf("%d %d %d %d %d\n",
			a[0], a[1], a[2],
			a[3], a[4]);
		SetEvent(hEvent2);

		::Sleep(1000);

	}
	return 0;
}

#endif
