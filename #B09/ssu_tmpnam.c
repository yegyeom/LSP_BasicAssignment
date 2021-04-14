#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 4096

int main(void){
	char buf[MAX_LINE];
	char name[L_tmpnam];
	FILE *fp;

	printf("temp file 1 : %s\n", tmpnam(NULL)); //tmpnam() 으로 임시 파일 생성하고 그 이름 출력
	tmpnam(name); //임시 파일 생성하고 그 이름을 name변수에 저장
	printf("temp file 2 : %s\n", name); //name변수에 있는 값 출력

	if((fp = tmpfile()) == NULL){ //프로그램에서 사용할 임시 파일 생성하고 해당 파일을 오픈하고있는 파일 구조체 포인터의 값을 fp에 저장
		fprintf(stderr, "tmpfile error\n");
		exit(1);
	}

	fputs("tmpfile created temporary file.\n", fp); //파일에 문자열 씀
	fseek(fp, 0, SEEK_SET); //오프셋을 파일의 맨 처음으로 설정

	if(fgets(buf, sizeof(buf), fp) == NULL){ //해당파일을 buf 크기만큼 읽어서 buf에 저장
		fprintf(stderr, "fgets error\n"); 
		exit(1);
	}

	fputs(buf, stdout); //읽은 내용 표준 출력으로 출력
	exit(0);
}
