#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_MAX 256

int main(){
	char command[BUFFER_MAX];
	char *prompt = "Prompt>>";

	while(1){
		fputs(prompt, stdout); //prompt 표준출력

		if(fgets(command, sizeof(command), stdin) == NULL) //표준입력으로 입력받아서 command에 저장
			break; //NULL입력 받으면 break

		system(command); //command실행 
	}

	fprintf(stdout, "Good bye...\n");
	fflush(stdout); //출력 버퍼 강제로 비우고 버퍼 안에 있는 자료 파일에 즉시 씀
	exit(0);
}
