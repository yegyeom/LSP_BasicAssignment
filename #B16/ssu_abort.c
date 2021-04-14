#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("abort terminate this program\n");
	abort(); //자신에게 SIGABRT 발생
	printf("this line is never reached\n");
	exit(0);
}
