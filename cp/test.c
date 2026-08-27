#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#if 0

int main() {
	int score;
	char* G = "FFFFFFDCBAA";
	scanf("%d", &score);
	printf("%c\n", G[score / 10]);

	int a = 90;
	char s;
	switch (a / 10) {
	case 10:
	case 9:
		s = 'A';
		break;
	case 8:
		s = 'B';
		break;
	case 7:
		s = 'C';
		break;
	case 6:
		s = 'D';
		break;
	default:
		s = 'F';
	}
	printf("%c\n", s);
	return 0;
}

#endif


// �հ�, �����, ���հ�
#if 1

void checkPass(int score) {
	char* res[3] = { 
		"�հ��Դϴ�.\n�����մϴ�.\n", 
		"����躸����.\n�����մϴ�.\n", 
		"���հ��Դϴ�.\n�����մϴ�.\n" };

	printf("%s", score >= 70 ? res[0] : score >= 60 && score < 70 ? res[1] : res[2]);
}

int main(void) {
	int score;
	(void)scanf("%d", &score);
    /*
    printf 겹침 + score 조건 겹침
    
     */
    char* res;
	if (score >= 70 && score <= 100) printf("�հ��Դϴ�. ");
	else if (60 <= score && score < 70) printf("����躸����. ");
	else if (0 <= score && score < 60) printf("���հ��Դϴ�. ");
	else printf("�߸��� �Է��Դϴ� �ٽ� �Է����ּ��� ");
    printf("%s",res);
	printf("�����մϴ�.\n");


	printf("%s�Դϴ�. �����մϴ�.\n", 
		score >= 70 ? "�հ�" : (score >= 60 ? "�����" : "���հ�"));
    /*
    
        printf 너무 많음


     */
	if (score >= 70) printf("�հ��Դϴ�.");
	else if (score >= 60) printf("����躸����.");
	else printf("���հ��Դϴ�.");
	printf("\n�����մϴ�.");
    /*
    조건문이 잘못대서 먼가 대입을 마니한다
     */
	char* msg[3] = { "�հ��Դϴ�", "����躸����", "���հ��Դϴ�" };
	int i = 0;
  
	if (score < 70) {
		i = 1;
		if (score < 60) {
			i = 2;
		}
	}
	printf("%s �����մϴ�.", msg[i]);
    /*
    
     */
	char* c[] = { "���հ��Դϴ�.","������Դϴ�.","�հ��Դϴ�." };
	printf("%s\n", c[(score >= 60) + (score >= 70)]);
	return 0;
}
#endif

#if 1
int main(){
    int a= 0;
    int input = 0;
    int num = 0;
    /*
    printf 남발
    elseif 2개 필요없음
     */
	if (a % 2 == 0) {
		printf("2");
	}
	else if (a % 3 == 0) {
		printf("3");
	}
	else if (a % 5 == 0) {
		printf("5");
	}
	else if (a % 2 == 0 && a % 3 == 0) {
		printf("2");
	}
	else if (a % 3 == 0 && a % 5 == 0) {
		printf("3");
	}
	else {
		printf("0");
	}

    /*
        printf 남발
    elseif 2개 필요없음

    
     */
	if (num % 2 == 0) printf("2");
	else if (num % 3 == 0) printf("3");
	else if ((num % 2 == 0) && (num % 3 == 0)) printf("2");
	else if (num % 5 == 0) printf("5");
	else if ((num % 3 == 0) && (num % 5 == 0)) printf("3");
	else printf("0");
 /*
        printf 남발
    elseif 2개 필요없음

    
     */
	if (input == 0)
		printf("0");
	else if (input % 5 == 0)
		printf("5\n");
	else if ((input % 2 == 0) || (input % 2 == 0 && input % 3 == 0))
		printf("2\n");
	else if ((input % 3 == 0) || (input % 3 == 0 && input % 5 == 0))
		printf("3\n");
	else
		printf("0");


    return 0;
}
#endif
#if 1

/*
if 마다 return 씀
 */
int mul01(int arr2)
{
	if (arr2 % 2 == 0)
		return 2;
	else if (arr2 % 3 == 0)
		return 3;
	else if (arr2 % 5 == 0)
		return 5;
	else
		return 0;
	// ���� ���� �� ���� ��ġ

}

int mul02(int arr2)
{
	if (arr2 % 2 == 0)
		return 2;
	if (arr2 % 3 == 0)
		return 3;
	if (arr2 % 5 == 0)
		return 5;
	return 0;
}

int main(void) {
	mul01(100);

	return 0;
}

char grade_calc(int score)
{
	switch (score / 10)
	{
	case 10:
	case 9:
		return 'A';
		break;

	case 8:
		return 'B';
		break;

	case 7:
		return 'C';
		break;

	case 6:
		return 'D';
		break;

	default:
		return 'F';
		break;
	}
}

int main2(void) {
	int a;
	int i;
	(void)scanf("%d", &a);
	
	i = 0;
	if (a % 2 == 0) {
		i = 2;
	}
	else if (a % 3 == 0) {
		i = 3;
	}
	else if (a % 5 == 0) {
		i = 5;
	}
	printf("%d\n", i);


	if (a % 2 == 0) {
		printf("2");
	}
	else if (a % 3 == 0) {
		printf("3");
	}
	else if (a % 5 == 0) {
		printf("5");
	}
	else {
		printf("0");
	}

	int score = 50;
	char* msg[5] = { "A", "B", "C", "D", "F" };

	if (score < 90) {
		i = 1;
		if (score < 80) {
			i = 2; {
				if (score < 70) {
					i = 3;
					if (score < 60) {
						i = 4;
					}
				}
			}
		}
	}
	printf("%s\n", msg[i]);
	char* grade[] = { 'A','B','C','D','F' };
	char answer = 0;
	switch (score / 10) {
	case 10:
	case 9:
		answer = grade[0];
		break;
	case 8:
		answer = grade[1];
		break;
	case 7:
		answer = grade[2];
		break;
	case 6:
		answer = grade[3];
		break;
	default:
		answer = grade[4];
		break;
	}
	printf("%c\n", answer);
	return 0;
}
#endif


// Ȧ��, ¦�� ���
#if 0
int main(void) {
	int a;
	char* msg[2] = { "¦��", "Ȧ��" };

	(void)scanf("%d", &a);
	printf("%s�Դϴ�.", msg[a % 2]);

	printf("%s\n", a % 2 == 0 ? "¦���Դϴ�" : "Ȧ���Դϴ�");

	char* c = 0;
	if (a % 2 == 0) {
		c = "Ȧ��";
	}
	else {
		c = "¦��";
	}
	printf("%s�Դϴ�\n", c);

	if (a % 2 == 0) {
		printf("Ȧ���Դϴ�\n");
	}
	else {
		printf("¦���Դϴ�\n");
	}

	
	return 0;
}
#endif


// if ~ else,  ���׿�����
#if 0
int main(void) {
	int a = 10, b = 5;
	int c[2] = { -1, 1 };

	printf("%d\n", c[a > b]);

	if (a > b)
		printf("%d\n", a);
	else
		printf("%d\n", b);

	int t;
	if (a > b)
		t = a;
	else
		t = b;
	printf("%d\n", t);

	t = a > b ? a : b;
	printf("%d\n", t);

	//(a > b) ? printf("%d", a) : printf("%d", b);
	printf("%d", a > b ? a : b);
	return 0;
}
#endif