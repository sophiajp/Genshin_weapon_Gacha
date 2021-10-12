
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

//���s��
#define NUM		100
//���ꂩ�瓊������a���ꂽ�^���̐�
int NOW_STONE;
//�Ō�ɐ�5�������Ă��獡�܂łɐ�5�ȊO����������
int INIT_STONE;
//�_���O�肵�Ă��獡�܂łɐ�5�ȊO����������(�_���O�肷��O�ɐ�5�ȊO�����񂩈������Ȃ炻�̐���������)
int ALL_INIT_STONE;

int N;
int M;
int num[NUM] = { 0 };
int non_pickup[2] = { 0 };
int pickup[2] = { 0 };
int wanted = 0;
int unfortune = 0;
int now_stone = 0;


void init() {
	for (int i = 0; i < 2; i++)
		non_pickup[i] = 0;
	for (int i = 0; i < 2; i++)
		pickup[i] = 0;
	for (int i = 0; i < N; i++)
		non_pickup[i] = 1;
	for (int i = 0; i < M; i++)
		pickup[i] = 1;
	wanted = 0;
}

int sum() {
	int sum = non_pickup[0] + non_pickup[1] + pickup[0] + pickup[1];
	return sum;
}

void five_star(int i) {
	int p = rand() % 1000;
	if (sum() == 2)
		wanted++;
	else if (non_pickup[0] == 0) {
		if (p % 2 == 0) {
			non_pickup[i]++;
//			printf("* non_pickup\n");
		}
		else {
			if (p % 10 < 5) {
				pickup[i]++;
//				printf("* pickup\n");
			}
			else {
				wanted++;
//				printf("* wanted\n");
			}
		}
	}
	else if (non_pickup[0] == 1) {
		if (p % 10 < 5) {
			pickup[i]++;
//			printf("pickup\n");
		}
		else {
			wanted++;
//			printf("wanted\n");
		}
	}
	else printf("error!\n");
}

void set() {
	cout << "���ꂩ�瓊������a���ꂽ�^���̐��F";
	cin >> NOW_STONE;

	cout << "\n�_���O�肵�Ă��獡�܂łɐ�5�ȊO����������\n(�_���O�肷��O�ɐ�5�ȊO�����񂩈������Ȃ炻�̐���������)�F";
	cin >> ALL_INIT_STONE;

	cout << "\n�Ō�ɐ�5�������Ă��獡�܂łɐ�5�ȊO���������񐔁F";
	cin >> INIT_STONE;

	cout << "\n�_���O�肵�Ă���s�b�N�A�b�v�ł͂Ȃ���5���������񐔁F";
	cin >> N;

	cout << "\n�_���O�肵�Ă���s�b�N�A�b�v�̐�5���������񐔁F";
	cin >> M;
	cout << "\n";

	for (int i = 0; i < N; i++)
		non_pickup[i] = 1;
	for (int i = 0; i < M; i++)
		pickup[i] = 1;
}

int main() {
	set();

	srand((unsigned int)time(NULL));
	for (int j = 0; j < NUM; j++) {
		//������
		init();
//		num[j] = INIT_STONE;
		bool initFlag = true;
		num[j] = ALL_INIT_STONE - INIT_STONE;

		for (int i = 0; i < 3; i++) {
			bool flag = false;
			if (wanted != 0) break;
			int Init = 0;
			if (initFlag) Init = INIT_STONE;
			else Init = 0;
			for (int l = Init; l < 79; l++) {
				int p = rand() % 1000;
				//4star
				if (l % 10 == 9) continue;
				//5star
				if (p < 7) {
//					if (initFlag)
//						num[j] += l + 1 - INIT_STONE;
//					else
					num[j] += l + 1;
//					printf("num[%d]=%d\n", j, num[j]);
					five_star(i);
					flag = true;
					break;
				}
			}
			if (flag) {
				flag = false;
				continue;
			}
//			if (initFlag)
//				num[j] += 80 - INIT_STONE;
//			else
			num[j] += 80;
//			printf("* num[%d]=%d\n", j, num[j]);
			five_star(i);
			initFlag = false;
		}
//		printf("wanted_num[%d]=%d\n", j, wanted_num[j]);
//		printf("stoneNum=%d\n", wanted_num[j]);
		if (num[j] == 240) unfortune++;
		if (num[j] <= NOW_STONE + ALL_INIT_STONE) now_stone ++;
		if (num[j] > 240) printf("error!\n");
//		printf("\n");
	}

	int sum_stone = 0;
	for (int i = 0; i < NUM; i++) {
		sum_stone += num[i];
	}
	double mean_stone = (double)sum_stone / (double)NUM - ALL_INIT_STONE;
	cout << NOW_STONE<<" �̐΂ŏ��Ȃ��Ƃ����5�������m���� " << 100.0 * (double)now_stone / (double)NUM << " %�ł�\n";
//	cout << "���ƕ��� " << mean_stone << " ��Ő�5�������܂�\n";
//	cout << "�����V��܂Ő�5�������Ȃ��m���� " << 100.0 * (double)unfortune / (double)NUM << " %�ł�\n";

	return 0;
}
