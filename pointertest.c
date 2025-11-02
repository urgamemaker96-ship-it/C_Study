#include <stdio.h>

void variableUse(int num, int* numpointer)
// 포인터 이용해서 해당 함수가 실행 될때 num이라는 변수에 주소값에 접근해서 num값으로 재설정함
// 주소값을 변경해주고 함수 호출시 변수가 없어지나 메모리로 접근하여 값을 변경시켜줘서 numpointer 변수는 사라지나 값은 변경처리됨
{
	*numpointer = num;

}



int main(void) 
{
	int value = 5;
	int target = 10;

	variableUse(value, &target); //&변수로 받아 주는거다 int* 포인터 자료형을...
	printf("target 의 값은 : %d", target);
}