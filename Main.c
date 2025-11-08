/*
* 1. 입출력문
 
#include <stdio.h> // 포함하다 <헤더파일>

int main(void) // 메인 함수 프로그램의 시작점
{
	printf("Hello, World!\n"); // 출력 함수 ("문자열 서식문자");
	return 0; // 0을 반환하고 종료
}


printf도 함수다.
main도 함수다.

return 0;을 하는 이유?
운영체제라는 것이 없던 시절 도스 시절
프로그램의 시작을 사용자 입맛대로 매개변수를 통해 시작할 수 있는 옵션이 주어졌고
정상 종료되었을 때는 0코드를 반환하는 암묵적 룰이 있었다.



#define _CRT_SECURE_NO_WARNINGS << 이거 왜 쓰는가? 안쓰면 어찌 되는가?

#include <stdio.h>

int main(void)
{
	int inputNum = 0;
	printf("입력: ");
	scanf("%d", &inputNum); // 앰퍼샌드 연산자 왜 쓰는가?
	printf("입력한 수: %d", inputNum);
}
*/

/*
* 2. 변수에 대한 설명은 메모로 대체
*/

/*
* 3. 조건문과 4.분기문
* [조건문]
* if, else if, else
* 조건식 검사가 가능하다 (비교)
* 성능이 느리다
* 
* [분기문]
* switch~case
* 조건검사가 불가능하다
* 성능이 빠르다
* 가독성이 좋다

#include <stdio.h>
enum {Attack, Run};
int main(void)
{
	int a = 0;

	if (a < 10)
	{
		printf("10보다 작다");
	}
	else if (a > 10)
	{
		printf("10보다크다");
	}
	else
	{
		printf("10이다");
	}

	switch (a)
	{
	case Attack:
		printf("공격");
		break;
	case Run:
		printf("도망");
		break;
	case 11:
		printf("10보다크다");
		break;
	}
}
*/

/*5. 반복문
* 
* for, while, do~while

for(i = 0; i < 5; i++)
{
	printf("test");
}

while(true)
{
	printf("test");
	// 이 반복문 안에서 특정 조건이 완료 되었을 때 탈출
}

조건문 분기문은 명확한 다름이지만
반복문은 편의의 차이이다.


*/

/*
* 6. 함수
* 
*/

#include <stdio.h>

int dataA = 100;
int dataB = 200;
// 함수의 선언
void Add(int, int);
void PrintNum(int);

// 메인 함수
int main(void)
{	
	printf("a : %d  b : %d  ", dataA, dataB);
	dataA= 10;
	dataB = 20;
	// 함수의 호출
	printf("a : %d  b : %d ", dataA, dataB);
}

// 함수의 정의
void Add(int num1, int num2) // int num1 = a, int num2 = b
{
	PrintNum(num1 + num2);
}

void PrintNum(int result)
{
	printf("%d \n", result);
}