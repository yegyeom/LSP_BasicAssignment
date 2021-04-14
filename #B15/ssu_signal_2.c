#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void ssu_signal_handler(int signo);

int main(void){
	if(signal(SIGINT, ssu_signal_handler) == SIG_ERR){ //SIGINT에 대한 시그널 핸들러로 ssu_signal_handler 등록
		fprintf(stderr, "cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGTERM, ssu_signal_handler) == SIG_ERR){ //SIGTERM에 대한 시그널 핸들러로 ssu_signal_handler 등록
		fprintf(stderr, "cannot handle SIGTERM\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGPROF, SIG_DFL) == SIG_ERR){ //SIGPROF를 SIG_DFL로 등록 : SIGPROF발생 시 시그널에 대한 디폴트 액션 실행
		fprintf(stderr, "cannot reset SIGPROF\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGHUP, SIG_IGN) == SIG_ERR){ //SIGHUP를 SIG_IGN로 등록 : SIGHUP발생 시 시그널 무시
		fprintf(stderr, "cannot ignore SIGHUP\n");
		exit(EXIT_FAILURE);
	}

	while(1)
		pause();

	exit(0);
}

static void ssu_signal_handler(int signo){
	if(signo == SIGINT) //SIGINT 발생 시
		printf("caught SIGINT\n");
	else if(signo == SIGTERM) //SIGTERM 발생 시
		printf("caught SIGTERM\n");
	else{
		fprintf(stderr, "unexpected signal\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
