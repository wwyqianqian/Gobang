#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define N 15

int chessboard[N + 1][N + 1] = {0}; // 设置为16x16（算上表头）的标志变量，标准棋盘是 15x15，全部把 flag 变量先归零
int whoseturn = 0; // 判断轮到谁下棋

 //○●
void printcheckerboard() { // 打印棋盘：初始空棋盘打印，以及游戏进行时落子的打印
	int i, j;
	for (i = 0; i <= N; i++) {
		for (j = 0; j <= N; j++) {
			if (i == 0 && j < 11) { // 初始打印
				printf(" %d", j); 
			} else if (i == 0 && j > 10) { // 粗暴地控制格式
                printf("1112131415");
                break;
			} else if (j == 0) {
				printf("%2d", i); 
			} else if (chessboard[i][j] == 1 ) { // 玩家1，使用 X 代表高亮黑棋子
				printf(" ");
				printf("\033[43;30mX\033[0m");
			} else if (chessboard[i][j] == 2 ) { // 玩家2，使用 O 代表高亮白棋子
				printf(" ");
				printf("\033[40;33mO\033[0m");
			} else {
				printf(" *"); // 未落子的空棋盘用 * 表示
			}
		}
		cout << endl;
	}
}

void init() {
	system("clear");
	printcheckerboard();
}

int judge(int x, int y) {
	int i, j;
	int t = 2 - whoseturn % 2; // 设置变量判断棋子种类和玩家是否匹配
	for (i = x - 4, j = y; i <= x; i++) { // 判断横排
		if (i >= 1 && i <= N - 4 && t == chessboard[i][j] 
			&& t == chessboard[i + 1][j] && t == chessboard[i + 2][j] 
			&& t == chessboard[i + 3][j] && t == chessboard[i + 4][j]) {
			return 1;
		}		
	}
	for (i = x, j = y - 4; j <= y; j++) { // 判断竖排
		if (j >= 1 && j <= N - 4 && t == chessboard[i][j] 
			&& t == chessboard[i][j + 1] && t == chessboard[i][j + 2] 
			&& t == chessboard[i][j + 3] && t == chessboard[i][j + 4]) {
			return 1;
		}
	}
	for (i = x - 4, j = y - 4; i <= x, j <= y; i++, j++) { // 判断左斜方
		if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 
			&& t == chessboard[i][j] && t == chessboard[i + 1][j + 1] 
			&& t == chessboard[i + 2][j + 2] && t == chessboard[i + 3][j + 3] 
			&& t == chessboard[i + 4][j + 4]) {
			return 1;
		}
	}
	for (i = x + 4, j = y - 4; i >= 1, j <= y; i--, j++) { // 判断右斜方
		if (i >= 5 && i <= N && j >= 1 && j <= N - 4 
			&& t == chessboard[i][j] && t == chessboard[i - 1][j + 1] 
			&& t == chessboard[i - 2][j + 2] && t == chessboard[i - 3][j + 3] 
			&& t == chessboard[i - 4][j + 4]) {
			return 1;
		}
	}
	return 0;
}

void playchess() {
	int i, j;
	if (whoseturn % 2 == 1) { // 玩家 1 先开始下黑子
		cout << "Player1's turn. Input the coordinate: " << endl;
		cin >> i >> j;
		while (chessboard[i][j] == 1 || chessboard[i][j] == 2) {
			printf("Player1's turn. Illegal input. Input the coordinate again:\n");
			cin >> i >> j;
		}
		chessboard[i][j] = 1;
	} else { // 玩家 2 白子
		cout << "Player2's turn. Input the coordinate: " << endl;
		cin >> i >> j;
        while (chessboard[i][j] == 1 || chessboard[i][j] == 2) {
			printf("Player2's turn. Illegal input. Input the coordinate again:\n");
			cin >> i >> j;
		}
		chessboard[i][j] = 2;
	}

	init(); // 下完之后要重新打印新的棋盘

	if (judge(i, j)) { // 打印之后要判断胜负情况，judge == 1 时，说明有了胜负结果
		if (whoseturn % 2 == 1) {
			cout << "Player1 WON!" << endl;
			exit(0);
		} else { // 判定胜负后直接暴力退出整个程式
			cout << "Player2 WON!" << endl;
			exit(0);
		}
	}
}


int main() {
	init();
	while (1) {
		whoseturn++; // 利用奇数偶数特性方便判断轮到谁落子
		playchess();
	}

	return 0;
}