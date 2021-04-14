#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 128
#define BUFFER_SIZE 1024
 
int main(int argc, char *argv[])
{
	static struct{
		long offset;
		int length;
	}table [TABLE_SIZE];
	char buf[BUFFER_SIZE];
	long offset;
	int entry;
	int i;
	int length;
	int fd;

	if(argc < 2){
		fprintf(stderr, "open error for %s\n", argv[1]); //에러체크
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) < 0){ //읽기 전용으로 파일 오픈
		fprintf(stderr, "open error for %s\n", argv[1]); //에러체크
		exit(1);
	}

	entry = 0;
	offset = 0;
	while((length = read(fd, buf, BUFFER_SIZE)) > 0){ //buffersize만큼 읽고 값을 변수에 넣음
		for(i = 0 ; i < length ; i++){ //해당 줄까지의 문자열 길이, 오프셋 저장
			table[entry].length++;
			offset++;

			if(buf[i] == '\n')
					table[++entry].offset = offset;
		}
	}

#ifdef DEBUG
	for(i = 0 ; i < entry ; i++)
		printf("%d : %ld, %d\n", i + 1, table[i].offset, table[i].length);
#endif

		while(1){
			printf("Enter line number : ");
			scanf("%d", &length);

			if(--length < 0) //음수 입력받으면 종료
				break;

			lseek(fd, table[length].offset, 0); //오프셋 위치 이동

			if(read(fd, buf, table[length].length) <= 0)
			continue;

			buf[table[length].length] = '\0';
			printf("%s", buf); //내용 출력
			}

		close(fd);
		exit(0);
		}
