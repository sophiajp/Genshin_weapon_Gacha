
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

#define NUM		100000 //試行回数

int NOW_STONE;
int INIT_STONE;
int N;
int M;
int num[NUM] = { 0 };
int non_pickup[2] = { 0 };
int pickup[2] = { 0 };
int wanted = 0;
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
	cout << "これから投入する紡がれた運命の数：";
	cin >> NOW_STONE;

	cout << "\n最後に星5を引いてから今までに引いた回数：";
	cin >> INIT_STONE;

	cout << "\n神鋳軌定してからピックアップではない星5を引いた回数：";
	cin >> N;

	cout << "\n神鋳軌定してからピックアップの星5を引いた回数：";
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
		init();
		bool initFlag = true;

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
					if (initFlag) num[j] += l + 1 - INIT_STONE;
					else num[j] += l + 1;
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
			if (initFlag) num[j] += 80 - INIT_STONE;
			else num[j] += 80;
//			printf("* num[%d]=%d\n", j, num[j]);
			five_star(i);
			initFlag = false;
		}
		if (num[j] <= NOW_STONE) now_stone++;
//		printf("\n");
	}

	int sum_stone = 0;
	for (int i = 0; i < NUM; i++) {
		sum_stone += num[i];
	}
	double mean_stone = (double)sum_stone / (double)NUM;
	double p = 100.0 * (double)now_stone / (double)NUM;
	cout << NOW_STONE<<" 個の石で狙った星5を引く確率は " << setprecision(3) << p << " %です\n";
	cout << "平均 " << setprecision(3) << mean_stone << " 回で狙った星5が当たります\n";

	return 0;
}
