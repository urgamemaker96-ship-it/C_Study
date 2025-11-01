
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//
//int main() {
//    int arr[5] = { 10, 20, 30, 40, 50 };
//
//    // 배열의 이름은 첫 번째 요소의 주소를 가리킴
//    int* ptr = arr;  // arr[0]을 가리킴
//
//    // 포인터 연산으로 3번째 요소 접근
//    int* third_element = ptr + 2;  // 0번째에서 2만큼 이동 → 2번 인덱스 (3번째 요소)
//
//    printf("배열 전체: ");
//    for (int i = 0; i < 5; i++) {
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
//
//    printf("3번째 요소 (arr[2]): %d\n", arr[2]);
//    printf("포인터 연산으로 찾은 값: %d\n", *third_element);
//    printf("0번째 요소의 주소 배열로: %p\n", arr);
//    printf("0번째 요소의 주소: %p\n", &arr[0]);
//    printf("0번째 요소의 주소 배열로: %p\n", arr + 1);
//    printf("0번째 요소의 주소: %p\n", &arr[1]);
//    printf("3번째 요소의 주소 배열로: %p\n", &arr[2]);
//    printf("3번째 요소의 주소: %p\n", third_element);
//
//    return 0;
//}

int main(void)
{
	char name[20];
	int input[10];
	printf("이름을 입력: ");
	scanf("%s", name);
	printf("이름: %s", name);


	printf("숫자를 입력: ");
	scanf("%d", input);
	printf("숫자: %d", input[0]);
}