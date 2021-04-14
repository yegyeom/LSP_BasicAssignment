#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void ssu_timestamp(char *str);

int main(void)
{
	int ret;

	ssu_timestamp("before sleep()"); //sleep 호출 전 시각 출력
	ret = sleep(10); //10초 동안 프로세스 중지
	ssu_timestamp("after sleep()"); //sleep 호출 후 시각 출력
	printf("sleep() returned %d\n", ret);
	exit(0);
}

void ssu_timestamp(char *str){
	time_t time_val;

	time(&time_val);
	printf("%s the time is %s\n", str, ctime(&time_val)); //시간을 문자열로 변환하여 출력
}
