#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct ssu_pirate{
	unsigned long booty;
	unsigned int beard_length;
	char name[128];
};

int main(){
	struct ssu_pirate blackbeard = {950, 48, "Edward Teach"}, pirate;
	char *fname = "ssu_data";
	FILE *fp1, *fp2;

	if((fp2 = fopen(fname, "w")) == NULL){ //파일을 쓰기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	if(fwrite(&blackbeard, sizeof(struct ssu_pirate), 1, fp2) != 1){ //blackbeard의 내용을 구조체의 크기만큼 파일에 씀
		fprintf(stderr, "fwrite error\n");
		exit(1);
	}

	if(fclose(fp2)){ //오픈된 파일스트림 닫음
		fprintf(stderr, "fclose error\n");
		exit(1);
	} 

	if((fp1 = fopen(fname, "r")) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error\n");
		exit(1);
	}

	if(fread(&pirate, sizeof(struct ssu_pirate), 1, fp1) != 1){ //파일의 내용을 구조체 크기만큼 읽어서 pirate에 저장
		fprintf(stderr, "fread error\n");
		exit(1);
	}

	if(fclose(fp1)){ //오픈된 파일스트림 닫음
		fprintf(stderr, "fclose error\n");
		exit(1);
	}

	printf("name=\"%s\" booty=%lu beard_length=%u\n", pirate.name, pirate.booty, pirate.beard_length);
	exit(0);
}
