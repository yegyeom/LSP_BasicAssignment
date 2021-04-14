#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	sigset_t sig_set;
	int count;

	sigemptyset(&sig_set); //sig_set 인자를 초기화
	sigaddset(&sig_set, SIGINT); //SIGINT 시그널을 sig_set인자에 추가
	sigprocmask(SIG_BLOCK, &sig_set, NULL);
	//sig_set 인자에 포함된 시그널인 SIGINT를 블록시킨다.
	for(count = 3 ; 0 < count ; count--){
		printf("count : %d\n", count);
		sleep(1);
	}
 
	printf("Ctrl-C에 대한 블록을 해제\n");
	sigprocmask(SIG_UNBLOCK, &sig_set, NULL); //for문 실행 중에 SIGINT 발생이 있을 경우
	printf("count중 Ctrl-C입력하면 이 문장은 출력 되지 않음\n");
	//SIGINT 발생 없다면 무한루프
	while(1);

	exit(0);
}
