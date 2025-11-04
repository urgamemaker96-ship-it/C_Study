#include <stdio.h>
//오류 뜨는 원인도 찾아보고 오류 처리된 다음 함수 서로 비교해보기
//같은 name 인지 다른 name 지도 확인 필요! 
// -> 같은 name 변수다 다만 값만 다르게 초기화 된것임
// 1. 초기화 된 과정 -> char 타입 name이란 이름을 가졌고  값이 홍길동으로 초기화
// 2. char* 타입이고 name이란 이름을 가졌고 값이 입력받은 값으로 초기화
// 3. char에다 *만 붙여줬지만 새로운 포인터 타입으로 변함 
// -> 해당 변수가 존재하는 메모리 위치에 시작점을 찍었다는 의미
// -> 포인터라는 의미는 변수가 존재하는 메모리 위치에 주소(시작점)를 찍었다. 새로 공간 할당은 하지않음 => 단지 주소만 찍었다.

void ShowStatus(char*);
void UserNameInput1(char*, int);
char* UserNameInput2(void);


int main(void)
{
	char name[20] = "홍길동"; // char 타입의 변수, 홍길동으로 값 초기화
	printf("%s", name);// char 타입의, 변수 홍길동으로 값 초기화
	strcpy(name, UserNameInput2()); // name 변수의 메모리 주소에서 값만 바꿔주고 싶어서 이렇게 했으나 오류라고 뜸!
	ShowStatus(name); //char* 타입의 변수로 입력받은 값으로 초기화 되어 출력됨
}

void ShowStatus(char* name)
{
	printf("===================================================\n");
	printf("상태창\n");
	printf("전달받은 이름은 : % s\n", name); // 어차피 배열은 포인터라 &안적어도된다..
	printf("===================================================\n");
}

//void 타입으로 만든 이름입력함수
void UserNameInput1(char* name, int size)
{


	scanf_s("%s", name, size); // scanf_s("%s", name,size); 오류로 확인되며 3번째에 반드시 버퍼크기를 적어줘야지 오류를 줄일 수 있기 때문에 입력이 강제된다.
	printf("\n입력하신 이름은 : %s 입니다\n", name);
}

char* UserNameInput2(void) 
{
	static char name[20] = "송경일";
	return name;

}



//void variableUse(int num, int* numpointer)
// 포인터 이용해서 해당 함수가 실행 될때 num이라는 변수에 주소값에 접근해서 num값으로 재설정함
// 주소값을 변경해주고 함수 호출시 변수가 없어지나 메모리로 접근하여 값을 변경시켜줘서 numpointer 변수는 사라지나 값은 변경처리됨
//{
	//*numpointer = num;
	//------------------------------------------------메인함수에다가 넣어줄것
	//int value = 5; 
	//int target = 10;

	//variableUse(value, &target); //&변수로 받아 주는거다 int* 포인터 자료형을...
	//printf("target 의 값은 : %d", target);
	//-----------------------------------------------
//}




