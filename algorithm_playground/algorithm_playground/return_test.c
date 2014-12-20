#include <stdio.h>
#include <stdlib.h>

void exit_test()
{
	exit(1);
	
	// pthread_exit(NULL);
	
	printf("this is dead code...=r231@)_#$!\n");
}

void return_test()
{
	return;
	printf("this is dead code...=r231@)_#$!\n");
}

int main()
{
	return_test();

	exit_test();
	
	return 0;
	
}
