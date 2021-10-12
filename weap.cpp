
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM			100000
//これから投入する紡がれた運命の数
#define NOW_STONE	1
//最後に星5を引いてから今までに星5以外を引いた回数
#define INIT_STONE	78
//神鋳軌定してから今までに星5以外を引いた回数(神鋳軌定する前に星5以外を何回か引いたならその数を加える)
#define ALL_INIT_STONE	238

int num[NUM] = { 0 };
int non_pickup[2] = { 0 };
int pickup[2] = { 0 };
int wanted = 0;
int unfortune = 0;
int now_stone = 0;


void init() {
	non_pickup[0] = 1;
	non_pickup[1] = 0;
	pickup[0] = 1;
	pickup[1] = 0;
	wanted = 0;
}

int sum() {
	int sum = non_pickup[0] + non_pickup[1] + pickup[0] + pickup[1];
	return sum;
}

void five_star(int i) {
	int p = rand() % 1000;
//	printf("p=%d\n", p);
//	printf("five_star\n");
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

int main() {
	srand((unsigned int)time(NULL));
	for (int j = 0; j < NUM; j++) {
		//初期化
		bool flag = false;
//		num[j] = INIT_STONE;
		init();
		bool initFlag = true;
		num[j] += ALL_INIT_STONE - INIT_STONE;

		for (int i = 0; i < 3; i++) {//切り捨て
			if (wanted != 0) break;
			int ini = 0;
			if (initFlag) ini = INIT_STONE;
			else ini = 0;
			for (int l = ini; l < 79; l++) {
				int p = rand() % 1000;
				//4star
				if (l % 10 == 9) continue;
//				if (p >= 10 && p < 20) continue;
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
//		if (num[j] > 240) printf("error!\n");
//		printf("\n");
	}

	int sum_stone = 0;
	for (int i = 0; i < NUM; i++) {
		sum_stone += num[i];
	}
	printf("mean_stone=%.1f\n", (double)sum_stone / (double)NUM - ALL_INIT_STONE);
	printf("unfortune_percent=%.1f[%%]\n", 100*(double)unfortune / (double)NUM);
	printf("now_stone_percent=%.2f[%%], NOW_STONE=%d\n", 100 * (double)now_stone / (double)NUM, NOW_STONE);
	return 0;
}
