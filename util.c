#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int UserInput()
{
	int inputNum;

	printf("입력: ");
	scanf_s("%d", &inputNum);
	return inputNum;
}

void JustPrint(char* str) 
{
	printf("%s 이름을 입력 : ", str);
}

char* InputName_Malloc()
{
	
	// 찾아보니 한글 글자일 경우 2~3바이트라고 한다, 못해도 32글자 까지는 받고 싶어서 안전하게 64크기 배열만듬
	char temp[64];

	//%63s 로 해주는 이유는 scanf_s 함수에서 null 문자 받기위해 1바이트 남기는게 규칙이라고한다 
	scanf_s("%63s", temp, (unsigned)sizeof(temp)); 

	//strlen()함수를 통해 문자열 길이를 확인 +1 해주는 이유는 문자열 끝부분확인 -> name 변수의값 에다가 메모리 주소값 할당해준다
	char* name = (char*)malloc(strlen(temp) + 1); 
	
	//scrcpy_s 방법이 name의 크기를 확인하고 넘기는 방식이라 안전하자 -> scrcpy 로 해봤더니 버퍼오버플로우 오류남
	strcpy_s(name, strlen(temp) + 1, temp); //temp를 name 이 가리키는 메모리 주소로 temp+1의 크기만큼(바이트) 복사해라!

	printf("입력하신 이름은 %s 입니다\n\n", name);

	return name;
}


void TakeDamage(int* damage, int* health)//이미 윗쪽 지역변수 health 선언되어 있어서 따로 포인터 자료형변수로 안만듬
{
	*health -= *damage;
}
int Percent(int num1) // 확률조건을 출력해주는 함수
{
	return (rand() % 100) < num1; // 0에서99까지 랜덤하게 나오는데 < 70면 0~69까지 반환됨 -> 조건 자체가 반환된다.
	//0과 1로 판단 -> 조건이 참이면 실행되는거다!
}

int GetSubstractResultOrZero(int num1, int num2)
{
	int result = num1 - num2;

	return result >= 0 ?
		result : 0;
}

int GetAddResultOrZero(int num1, int num2, int max)
{
	int result = num1 + num2;

	return result >= max ?
		max : result;
}