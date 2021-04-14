#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	char name[L_tmpnam];
	FILE *fp;

	printf("Temporary filename <<%s>>\n", tmpnam(name)); //임시 파일 생성하고 이름을 name변수에 저장하여 출력

	if((fp = tmpfile()) == NULL){ //프로그램에서 사용할 임시 파일 생성하고 해당파일을 오픈하고 있는 파일 구조체 포인터의 값을 fp에 저장
		fprintf(stderr, "tmpfile create error!!\n");
		exit(1);
	}

	fputs("create tmpfile success!!\n", fp); //파일에 문자열의 내용 씀
	rewind(fp); //오프셋을 파일의 맨 처음으로 이동
	fgets(buf, sizeof(buf), fp); //파일에서 buf의 크기만큼 읽어서 buf에 씀
	puts(buf); //buf의 내용을 표준 출력으로 출력(개행 추가함)
	exit(0);
}
