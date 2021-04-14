#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>

int ssu_daemon_init(void);

int main(void)
{
	printf("daemon process initialization\n");

	if(ssu_daemon_init() < 0){
		fprintf(stderr, "ssu_daemon_init failed\n");
		exit(1);
	}

	while(1){ //5초마다 로그 메시지를 남김
		openlog("lpd", LOG_PID, LOG_LPR); //각 메시지마다 프로세스 id를 기록, 라인 프린터 시스템
		syslog(LOG_ERR, "open failed lpd %m");
		closelog();
		sleep(5);
	}

	exit(0);
}

int ssu_daemon_init(void){
	pid_t pid;
	int fd, maxfd;

	if((pid = fork()) < 0){ //자식 프로세스 생성
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid != 0)
		exit(0); //부모 프로세스 죽음

	pid = getpid();
	printf("process %d running as daemon\n", pid); //자식 프로세스의 id 
	setsid(); //자식 프로세스가 새로운 세션의 리더
	signal(SIGTTIN, SIG_IGN); //터미널 입력 시그널 무시
	signal(SIGTTOU, SIG_IGN); //터미널 출력 시그널 무시
	signal(SIGTSTP, SIG_IGN); //터미널 중지 시그널 무시
	maxfd = getdtablesize();

	for(fd = 0 ; fd < maxfd ; fd++)
		close(fd); //모든 fd를 닫음

	umask(0); //파일 모드 생성 마스크 해제
	chdir("/"); //현재 작업 디렉토리를 루트 디렉토리로 설정
	fd = open("/dev/null", O_RDWR); //표준 입출력과 표준 에러를 /dev/null로 재지정
	dup(0);
	dup(0);
	return 0;
}
