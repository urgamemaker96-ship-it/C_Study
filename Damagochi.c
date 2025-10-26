#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable:4996) 

//전역변수들

enum { HungrtyState, StressState ,HealthState};
int look; // 스테이터스 확인용

//다마고치 초기상태로 값 초기화
int hungry = 10; //만복도
int poo= 10; // 배변활동
int health= 10; // 체력
int stress= 10; // 지랄력
int exp= 0 ; // 경험치
int currentlevel = 1; //현제 레벨


// 함수들 선언
void Feed(int, int, int);
void  Poo();
void OutPlay(int, int, int);
void ThugPlay(int, int, int);


//문제점 1.전투 발생 시스템을 어떻게 만들어야 되는지 감이 안잡힌다 -> while문을 사용해보는 시도를 해보자...
//       2.승리 조건를 만들어야 클리어 되든 할텐데 승리 조건은 전투발생과 연결지어 만들어야 될것같다...

//문제 해결 된 것들 : 함수를 만들어서 해당 기능들이 변수의 값을 바꿔주는 것이 가능해짐
// -> 이 기능들을 어떻게 응용해서 다마고치 게임을 만들어야하는가?

int main(void)
{ // 산책이나 터그 놀이 하다가 중간에 전투 발생 -> 1번 물기, 2번 몸통 박치기, 상대방 체력 떨어지고 나도 체력 떨어지고
  //  ㄴ 위의 기능은 랜덤을 이용하여 만들어야 됨...	

		
		

		
		 // 매개변수의 값이 설정대로 변수가 변하지 않고 전역변수 값으로 나온다. -> 전역변수 컴파일시 0으로 초기화
						  // 이러는 원인이 뭔가? 함수에서 값이 변하지 않는 것으로 확인... 어떻게 처리 해야하는가? 
						// 해결됨 -> 지역변수랑 매개변수를 동일하게 쓰지마라 -> 매개변수를 num1 ,num2,num3 으로 처리하니깐 정상작동함
		printf("0을 눌러 현재 당신의 예완견의 상태는를 확인하시오....\n");
		scanf("%d", &look);
	
		printf("1을 눌러 현재 당신의 예완견에게 먹이를 주세요.\n");
		scanf("%d", &look+1);


		printf("2을 눌러 현재 당신의 예완견에게 화장실을 대려다 주세요.\n");
		scanf("%d", &look + 2);

		printf("3을 눌러 현재 당신의 예완견에게 산책을 대려다 주세요.\n");
		scanf("%d", &look + 3);
		
		printf("4을 눌러 현재 당신의 예완견에게 터그게임을 시켜 주세요.\n");
		scanf("%d", &look + 3);


		Feed(100,100,100);
		

		// 현재 상태 보임
		switch (look) // look은 어차피ㅏ 전역변수 컴파일 시 0으로 초기화 되서 0값이다.
		{
		case HungrtyState: //0이고 , enum 열거형으로 순서대로 만들어서

			printf("배고픔은 %d 입니다\n", hungry);
			break;

		case StressState: //1이다

			printf("스트레스정도는 %d 이고 배변활동은 %d 입니다\n", stress,poo);
			break;
		case HealthState://2이다

			printf("체력상태는 %d 입니다\n", health);
			break;
		}
	




		// 사망판정 조건문
		if (health <= 0 || poo >= 100 || hungry <= 0 || stress >= 100)
		{
			printf("당신의 애완견은 사망했습니다.\n");
		}


		// 레벨업 조건문
		if (exp >= 100*currentlevel*1.2) 
		{	
			exp = 0; // 레벨업 시 경험치 초기화
			currentlevel += 1; // 경험치만족해서 1 증가
			printf("당신의 애완견의 레벨이 %d로증가했습니다.\n",currentlevel);

		}



}

//밥주는함수 -> 체력증가, 만복도 증가, 배변활동 증가
void Feed(int num1, int num2, int num3) 
{
	

	health += num1;
	hungry += num2;
	poo += num3;
	
	return health, hungry, poo;
}

//배변함수 -> 배변 활동 0으로 정상화
void Poo()
{	
	return poo = 0;

}

//산책 함수 -> 체력감소, 만복도 감소, 경험치 증가
void OutPlay(int num1, int num2, int num3)
{
	health -= num1;
	hungry -= num2;
	exp += num3;
	return health, hungry, exp;
}

//터그놀이 -> 배고픔 증가, 지랄력 감소, 경험치 증가
void ThugPlay(int num1, int num2, int num3)
{
	hungry -= num1;
	stress -= num2;
	exp += num3;

	return hungry, stress, exp;
}




