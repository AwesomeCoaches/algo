#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <queue>
#include <memory.h>

using namespace std;

#define MAX_VALUE 999999

int N, Q;
int map_size;
int map[65][65];
int tmp[65][65];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void rotate(int r, int c, int L) {
	for (int i = r; i < r + (int)pow(2, L); i++) {
		for (int j = c; j < c + (int)pow(2, L); j++) {
			tmp[j - c][r + (int)pow(2, L) - 1 - i] = map[i][j];
		}
	}
	for (int i = r; i < r + (int)pow(2, L); i++) {
		for (int j = c; j < c + (int)pow(2, L); j++) {
			map[i][j] = tmp[i - r][j - c];
		}
	}
}

bool melt(int r, int c) {
	int cnt = 0;
	for (int dir = 0; dir < 4; dir++) {
		int nr = r + dx[dir];
		int nc = c + dy[dir];
		if (nr < 0 || nc < 0 || nr > map_size - 1 || nc > map_size - 1) continue;
		if (map[nr][nc] > 0) cnt++;
	}
	if (cnt > 2) return true;
	else return false;
}

int get_max(int r, int c, int answer2) {
	queue< pair<int, int> > q;
	q.push(make_pair(r, c));
	tmp[r][c] = 1;
	int cnt = 1;
	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();


		for (int dir = 0; dir < 4; dir++) {
			int nr = now.first+ dx[dir];
			int nc = now.second + dy[dir];
			if (nr < 0 || nc < 0 || nr > map_size - 1 || nc > map_size - 1) continue;
			if (tmp[nr][nc] == 1 || map[nr][nc] == 0) continue;
			tmp[nr][nc] = 1;
			q.push(make_pair(nr, nc));
			cnt++;
		}
	}

	if (cnt > answer2) return cnt;
	else return answer2;
}

int main(void)
{
	cin >> N >> Q;

	map_size = (int)pow(2, N);

	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			cin >> map[i][j];
		}
	}

	int L;

	for (int i = 0; i < Q; i++) {
		cin >> L;
		for (int r = 0; r < map_size; r += (int)pow(2, L)) {
			for (int c = 0; c < map_size; c += (int)pow(2, L)) {
				rotate(r, c, L);
			}
		}
		for (int r = 0; r < map_size; r++) {
			for (int c = 0; c < map_size; c++) {
				if (melt(r, c)) tmp[r][c] = 0;
				else tmp[r][c] = 1;
			}
		}
		for (int r = 0; r < map_size; r++) {
			for (int c = 0; c < map_size; c++) {
				if (map[r][c] == 0) continue;
				map[r][c] -= tmp[r][c];
			}
		}
	}

	int answer1 = 0;
	int answer2 = 0;

	memset(tmp, 0, sizeof(tmp));

	for (int r = 0; r < map_size; r++) {
		for (int c = 0; c < map_size; c++) {
			answer1 += map[r][c];
			if (map[r][c] == 0 || tmp[r][c] == 1) continue;
			answer2 = get_max(r, c, answer2);
		}
	}

	cout << answer1 << endl << answer2 << endl;

	return 0;
}