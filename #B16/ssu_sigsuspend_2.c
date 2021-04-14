#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

static void ssu_func(int signo);
void ssu_print_mask(const char *str);

int main(void){
	sigset_t new_mask, old_mask, wait_mask;
	ssu_print_mask("program start: ");

	if(signal(SIGINT, ssu_func) == SIG_ERR){ //SIGINT의 시그널 핸들러로 ssu_func등록
		fprintf(stderr, "signal(SIGINT) error\n");
		exit(1);
	}

	sigemptyset(&wait_mask); //wait_mask 초기화
	sigaddset(&wait_mask, SIGUSR1); //wait_mask에 SIGUSR1 추가
	sigemptyset(&new_mask); //new_mask 초기화
	sigaddset(&new_mask, SIGINT); //new_mask에 SIGINT 추가

	if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0){ //시그널 집합에 있는 시그널 블록
		fprintf(stderr, "SIG_BLOCK() error\n");
		exit(1);
	}

	ssu_print_mask("in critical region: ");

	if(sigsuspend(&wait_mask) != -1){ //기존 시그널 집합으로 시그널이 발생할 때까지 잠시 팬딩하다가 시그널 발생하면 시그널 핸들러 실행
		fprintf(stderr, "sigsuspend() error\n");
		exit(1);
	}

	ssu_print_mask("after return from sigsuspend: ");

	if(sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0){ //시그널 집합에 있는 시그널 블록
		fprintf(stderr, "SIG_SETMASK() error\n");
		exit(1);
	}

	ssu_print_mask("program exit: ");
	exit(0);
}

void ssu_print_mask(const char *str){
	sigset_t sig_set;
	int err_num;
	
	err_num = errno;

	if(sigprocmask(0, NULL, &sig_set) < 0){ //시그널 집합에 있는 시그널 블록
		fprintf(stderr, "sigprocmask() error\n");
		exit(1);
	}

	printf("%s", str);

	if(sigismember(&sig_set, SIGINT)) //SIGINT가 시그널 집합에 존재하는지
		printf("SIGINT ");
	
	if(sigismember(&sig_set, SIGQUIT)) //SIGQUIT가 시그널 집합에 존재하는지
		printf("SIGQUIT ");

	if(sigismember(&sig_set, SIGUSR1)) //SIGUSR1가 시그널 집합에 존재하는지
		printf("SIGUSR1 ");

	if(sigismember(&sig_set, SIGALRM)) //SIGALRM가 시그널 집합에 존재하는지
		printf("SIGALRM ");

	printf("\n");
	errno = err_num;
}

static void ssu_func(int signo){
	ssu_print_mask("\nin ssu_func: ");
}
