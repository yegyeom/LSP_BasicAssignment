#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register);

static jmp_buf glob_buffer; 

int main(void){
	register int loc_register;
	register int loc_volatile;
	int loc_var;

	loc_var = 10; //최적화 옵션 사용 시 register
	loc_volatile = 11; //memory
	loc_register = 12; //stack
//최적화 옵션 사용하지 않으면 모두 memory에 저장
	if(setjmp(glob_buffer) != 0){ //최적화 옵션 있을 경우 : longjmp에서 왔을 때 register변수, stack변수 복구됨
		printf("after longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register); //컴파일 시 최적화 옵션 유무에 따라 출력 다름
		
		exit(0);
	}

	loc_var = 80;
	loc_volatile = 81;
	loc_register = 83;
	ssu_nested_func(loc_var, loc_volatile, loc_register);
	exit(0);
}

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register){
	printf("before longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
	longjmp(glob_buffer, 1); //1이 glob_buffer로 점프할 때 리턴 값
}
