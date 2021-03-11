#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Block {
	int t;
	int x;
	int y;

	Block(int t, int x, int y) {
		this->t = t;
		this->x = x;
		this->y = y;
	}
};

int map[2][6][4];

Block blue_block(Block b) {
	int t, y;

	if (b.t == 1) {
		t = 1;
		y = 3 - b.x;
	}
	else if (b.t == 2) {
		t = 3;
		y = 3 - b.x;
	}
	else if (b.t == 3) {
		t = 2;
		y = 2 - b.x;
	}

	return Block(t, 0, y);
}

void drop_block(Block b, int n, int map_i) {
	int t, x, y;
	t = b.t;
	x = b.x;
	y = b.y;


	// 원래 자리 지우기
	map[map_i][x][y] = 0;
	if (t == 2) {
		map[map_i][x][y + 1] = 0;
	}
	else if (t == 3) {
		map[map_i][x + 1][y] = 0;
		x += 1;
	}

	// 블록 내리기
	while (true) {
		if (x + 1 > 5 || map[map_i][x + 1][y] != 0) break;
		if (t == 2 && map[map_i][x + 1][y + 1] != 0) break;
		x += 1;
	}

	map[map_i][x][y] = n;
	if (t == 2) {
		map[map_i][x][y + 1] = n;
	}
	else if (t == 3) {
		map[map_i][x - 1][y] = n;
		x -= 1;
	}
}

bool is_full(int map_i, int x) {
	bool flag = true;
	for (int y = 0; y < 4; y++) {
		if (map[map_i][x][y] == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

void erase_line(int map_i, int x) {
	for (int y = 0; y < 4; y++) {
		map[map_i][x][y] = 0;
	}
}

void check01(int map_i) {
	int cnt = 0;

	for (int x = 0; x < 2; x++) {
		bool flag = false;
		for (int y = 0; y < 4; y++) {
			if (map[map_i][x][y] != 0) flag = true;
		}
		if (flag) cnt++;
	}

	for (int x = 5; x > 1; x--) {
		for (int y = 0; y < 4; y++) {
			map[map_i][x][y] = map[map_i][x - cnt][y];
		}
	}

	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 4; y++) {
			map[map_i][x][y] = 0;
		}
	}
}

int get_type(int map_i, int x, int y) {
	int n = map[map_i][x][y];
	int t = 1;
	if (y + 1 < 4 && map[map_i][x][y + 1] == n) t = 2;
	else if (x > 0 && map[map_i][x - 1][y] == n) t = 3; 

	return t;
}

int main(void)
{
	int N, t, x, y;
	int answer = 0;
	int cnt_gb = 0;

	cin >> N;

	for (int map_i = 0; map_i < 2; map_i++) {
		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 4; y++) {
				map[map_i][x][y] = 0;
			}
		}
	}

	for (int n = 1; n <= N; n++) {
		cin >> t >> x >> y;
		Block b = Block(t, x, y); // 블록 받아놓기
		for (int map_i = 0; map_i < 2; map_i++) {
			if (map_i == 1) b = blue_block(b); // 오른쪽 떨어트리기 위해 돌리기
			drop_block(Block(b.t, 0, b.y), n, map_i); // 받은 블럭 떨어트림
			bool flag = false; // 지우고 나서 다시 떨어뜨리기 위해
			while (true) {
				flag = true;
				for (int i = 5; i > 1; i--) {
					if (is_full(map_i, i)) { // 꽉찬 라인 생기면 지우기
						erase_line(map_i, i);
						answer++;
						flag = false;
					}
				}
				if (flag) break;
				for (int i = 5; i > 0; i--) { // 밑에서 위로 탐색하며 블록 다시 떨어뜨리기
					for (int j = 0; j < 4; j++) {
						int now_n = map[map_i][i][j];
						if (now_n == 0) continue;
						t = get_type(map_i, i, j);
						if (t == 3) drop_block(Block(t, i - 1, j), now_n, map_i);
						else drop_block(Block(t, i, j), now_n, map_i);
						if (t == 2) j++;
					}
				}
			}
			check01(map_i); // 01 라인 정리
		}
	}

	for (int map_i = 0; map_i < 2; map_i++) {
		for (int x = 2; x < 6; x++) {
			for (int y = 0; y < 4; y++) {
				if (map[map_i][x][y] != 0) cnt_gb++;
			}
		}
	}
	
	cout << answer << endl << cnt_gb << endl;

	return 0;
}