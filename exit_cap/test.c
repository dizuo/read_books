#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc <= 1)
	{
		printf("please input parameter...\n");
		exit(13);
	}
	
	printf("argv1 = %s\n", argv[1]);
	return 0;
}
