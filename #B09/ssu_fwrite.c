#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct ssu_id{
	char name[64];
	int id;
};

int main(){
	struct ssu_id test1, test2;
	char *fname = "ssu_exam.dat";
	FILE *fp;

	if((fp = fopen(fname, "w")) == NULL){ //파일을 쓰기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}
	
	printf("Input ID>> ");
	scanf("%d", &test1.id);
	printf("Input name>> ");
	scanf("%s", test1.name);
	//id와 name 입력받아서 구조체에 저장
	if(fwrite(&test1, sizeof(struct ssu_id), 1, fp) != 1){ //파일에 구조체 test1의 내용 씀
		fprintf(stderr, "fwrite error\n");
		exit(1);
	}

	fclose(fp);

	if((fp = fopen(fname, "r")) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	if(fread(&test2, sizeof(struct ssu_id), 1, fp) != 1){ //파일에서 구조체 크기만큼 읽어서 test2에 넣음
		fprintf(stderr, "fread error\n");
		exit(1);
	}

	printf("\nID	name\n");
	printf(" ===========\n");
	printf("%d	%s\n", test2.id, test2.name); //파일에서 읽어온 데이터를 출력
	fclose(fp);
	exit(0);
}
