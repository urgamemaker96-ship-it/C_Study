#include "util.h"
#include <string.h> //strcpy_s 사용위해서
#include <stdio.h>
#include <stdlib.h>
#include "Struct.h"
#include <stdbool.h> // bool 타입 써줄려면 헤더파일 추가해줘야됨

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

char* InputName_Malloc() // 말그대로 malloc 동적할당
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

// 다마고치 선택 함수
int SelectDamagochiType() {
	int choice; //입력받을 수 변수 선언

	printf("\n=== 다마고치 선택 ===\n");
	printf("1. 기본 다마고치\n");
	printf("2. 이상해씨 - 높은 체력\n");
	printf("3. 파이리 - 높은 공격력\n");
	printf("4. 꼬북이 - 높은 마나\n");

	scanf_s("%d", &choice); //scanf_s 써야 오류안뜸
	

	return choice;
}
void InitializeSkills(damagochi* type, int inputnum)
{
	switch (inputnum) { // 일부러 2, 3, 4 순으로 맞춰준거임 메인에서 1번은 기본 다마고치라서
	case 2: // 이상해씨
		strcpy_s(type->skill_isanghaessi.name, sizeof(type->skill_isanghaessi.name), "덩굴채찍");
		type->skill_isanghaessi.level = 1; // 구조체에서 기본스킬레벨 1로 초기화
		type->skill_isanghaessi.bonus_ratio = 0.2f; // 구조체에서 레벨업시 스킬공격력 증가 배수
		type->skill_isanghaessi.mana_cost = 50; // 구조체에서 마나코스트 가져옴 -> 이걸로 구조체 다마고치가 가진 마나를 빼줄거임
		break;
	case 3: // 파이리
		strcpy_s(type->skill_paili.name, sizeof(type->skill_isanghaessi.name), "화염방사");
		type->skill_paili.level = 1;// 구조체에서 기본스킬레벨 1로 초기화
		type->skill_paili.bonus_ratio = 0.2f;// 구조체에서 레벨업시 스킬공격력 증가 배수
		type->skill_paili.mana_cost = 50;// 구조체에서 마나코스트 가져옴 -> 이걸로 구조체 다마고치가 가진 마나를 빼줄거임
		break;
	case 4: // 꼬부기
		strcpy_s(type->skill_kkobugi.name, sizeof(type->skill_isanghaessi.name), "물대포");
		type->skill_kkobugi.level = 1;// 구조체에서 기본스킬레벨 1로 초기화
		type->skill_kkobugi.bonus_ratio = 0.2f;// 구조체에서 레벨업시 스킬공격력 증가 배수
		type->skill_kkobugi.mana_cost = 50;	 // 구조체에서 마나코스트 가져옴 -> 이걸로 구조체 다마고치가 가진 마나를 빼줄거임
		break;
	}
}

// 스킬 데미지 계산 함수 (실제 마나는 소모하지 않음) -> 스킬함수 로직 그대로 가져와서 계산만함
int CountSkillDamage(damagochi* type, int skill_type, bool Isnextlevel)
{
	switch (skill_type)
	{
	case 1: // 이상해씨 스킬
	{
		damaskill* skill = &type->skill_isanghaessi;
		// Isnextlevel에 따라 level_bonus 계산 방식 변경
		float level_bonus = 1.0f + ((skill->level - (Isnextlevel ? 0 : 1)) * 0.2f); // Isnextlevel 참이면 0 아니면 1
		return (int)((type->specialattack * level_bonus) +
			(type->Maxhealth * skill->bonus_ratio));
	}
	case 2: // 파이리 스킬
	{
		damaskill* skill = &type->skill_paili;
		float level_bonus = 1.0f + ((skill->level - (Isnextlevel ? 0 : 1)) * 0.2f); //Isnextlevel 참이면 0 아니면 1
		return (int)((type->specialattack * level_bonus) +
			(type->gochiattack * skill->bonus_ratio));
	}
	case 3: // 꼬부기 스킬
	{
		damaskill* skill = &type->skill_kkobugi;
		float level_bonus = 1.0f + ((skill->level - (Isnextlevel ? 0 : 1)) * 0.2f);//Isnextlevel 참이면 0 아니면 1
		return (int)((type->specialattack * level_bonus) +
			(type->mana * skill->bonus_ratio));
	}
	}
}

//다시 할당 해주는 거니깐 이번엔 메모리 할당크기를 좀 늘려봄 -> realloc 씀
void RenameCharacter(damagochi* selected, bool IsDamagochi)
{
	
	// 현재 이름과 새로운 이름 입력 메시지를 조건에 따라 다르게 출력
	char* currentName = IsDamagochi ? selected->damaname : selected->mastername; //IsDamagochi 다마고치 참이면 다마고치이름 거짓이면 주인이름
	char* nameType = IsDamagochi ? "다마고치" : "주인"; //IsDamagochi 다마고치 참이면 다마고치이름 거짓이면 주인이름

	printf("현재 %s 이름: %s\n", nameType, currentName);
	printf("새로운 %s 이름을 입력하세요: ", nameType);

	char temp[128];
	scanf_s("%127", temp, (unsigned)sizeof(temp));

	// realloc으로 메모리 재할당
	size_t new_size = strlen(temp) + 1;
	char** targetName = IsDamagochi ? &selected->damaname : &selected->mastername;

	char* new_name = (char*)realloc(*targetName, new_size);

	*targetName = new_name;
	strcpy_s(*targetName, new_size, temp);
	printf("%s 이름이 %s로 변경되었습니다.\n", nameType, *targetName);
}

// 메모리 할당 및 복사 함수 -> 다마고치 이름 받아서 처리간편화 하기 위해 만듬
char* AllocateAndCopyName(char* source)
{
	size_t len = strlen(source) + 1; // 다마고치보다 무조건 1칸큼
	char* new_name = (char*)malloc(len); // 길이만큼 동적할당해줌
	if (new_name != NULL) {
		strcpy_s(new_name, len, source); //받은 이름을 그대로 복사 붙어넣기로 값 초기화 해줌
	}
	return new_name;
}

// 모든 이름 메모리 해제
void FreeDamagochiNames(damagochi* selected)
{
	if (selected != NULL) {
		if (selected->damaname != NULL) {
			free(selected->damaname);
			selected->damaname = NULL;
		}
		if (selected->mastername != NULL) {
			free(selected->mastername);
			selected->mastername = NULL;
		}
	}
}


void TakeDamage(int damage, int* health)//이미 윗쪽 지역변수 health 선언되어 있어서 따로 포인터 자료형변수로 안만듬
{
	*health -= damage;
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

