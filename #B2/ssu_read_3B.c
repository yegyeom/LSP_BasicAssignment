#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char character;
	int fd;
	int line_count = 0;

	if((fd = open("ssu_test.txt", O_RDONLY)) < 0) { //읽기 전용으로 파일 오픈
		fprintf(stderr, "open error for %s\n", "ssu_test.txt"); //에러체크
		exit(1);
	}

	while(1){
		if(read(fd, &character, 1) > 0){ 
			if(character == '\n')
				line_count++; //개행문자의 개수 셈
		}
		else 
			break;
	}

	printf("Total line : %d\n", line_count); //파일의 내용이 총 몇줄인지 출력
	exit(0);
}
