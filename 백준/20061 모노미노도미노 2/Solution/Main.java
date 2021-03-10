import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    static int N;
    static int score, allBlockCount;
    static int[][] map;
    static int[][] calcMap;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        // 입력
        N = Integer.parseInt(br.readLine());
        map = new int[10][10];
        calcMap = new int[10][10];

        for (int block = 0; block < N; block++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int type = Integer.parseInt(st.nextToken());
            int row = Integer.parseInt(st.nextToken());
            int col = Integer.parseInt(st.nextToken());
            int r = 0, c = 0;
            switch (type) {
                case 1:
                    map[row][col] = 1;
                    // green 계산
                    copyMap(true);
                    moveBlock(1, row, col);
                    getScore();
                    check();
                    reverseMap(true);

                    // blue 계산
                    copyMap(false);
                    top:
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (calcMap[i][j] == 1) {
                                r = i;
                                c = j;
                                break top;
                            }
                        }
                    }
                    moveBlock(1, r, c);
                    getScore();
                    check();
                    reverseMap(false);
                    break;
                case 2:
                    map[row][col] = 1;
                    map[row][col + 1] = 1;

                    // green 계산
                    copyMap(true);
                    moveBlock(2, row, col);
                    getScore();
                    check();
                    reverseMap(true);

                    // blue 계산
                    copyMap(false);
                    top:
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (calcMap[i][j] == 1) {
                                r = i;
                                c = j;
                                break top;
                            }
                        }
                    }
                    moveBlock(3, r, c);
                    getScore();
                    check();
                    reverseMap(false);
                    break;
                case 3:
                    map[row][col] = 1;
                    map[row + 1][col] = 1;

                    // green 계산
                    copyMap(true);
                    moveBlock(3, row, col);
                    getScore();
                    check();
                    reverseMap(true);

                    // blue 계산
                    copyMap(false);
                    top:
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (calcMap[i][j] == 1) {
                                r = i;
                                c = j;
                                break top;
                            }
                        }
                    }
                    moveBlock(2, r, c);
                    getScore();
                    check();
                    reverseMap(false);
                    break;
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    map[i][j] = 0;
                }
            }
        }
        getBlockCount();
        System.out.println(score);
        System.out.println(allBlockCount);
    }

    private static void getBlockCount() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (map[i][j + 6] == 1) {
                    allBlockCount++;
                }
                if (map[i + 6][j] == 1) {
                    allBlockCount++;
                }
            }
        }
    }

    private static void check() {
        for (int i = 0; i < 4; i++) {
            if (calcMap[5][i] == 1) {
                down(4, 9);
                i = -1;
            }
        }
    }

    private static void getScore() {
        for (int i = 4; i < 10; i++) {
            int sum = 0;
            for (int j = 0; j < 4; j++) {
                if (calcMap[i][j] == 1) {
                    sum++;
                }
            }
            if (sum == 4) {
                score++;
                down(4, i);
                i = 4;
            }
        }
    }

    private static void down(int startRow, int endRow) {
        for (int i = endRow; i > startRow; i--) {
            for (int j = 0; j < 4; j++) {
                calcMap[i][j] = calcMap[i - 1][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            calcMap[startRow][i] = 0;
        }
    }

    private static void moveBlock(int type, int row, int col) {
        switch (type) {
            case 1:
                // 쭉 내리기
                while (isIn(row + 1, col) && calcMap[row + 1][col] != 1) {
                    row++;
                }
                calcMap[row][col] = 1;
                break;
            case 2:
                while (isIn(row + 1, col) && isIn(row + 1, col + 1) && calcMap[row + 1][col] != 1 && calcMap[row + 1][col + 1] != 1) {
                    row++;
                }
                calcMap[row][col] = 1;
                calcMap[row][col + 1] = 1;
                break;
            case 3:
                while (isIn(row + 2, col) && calcMap[row + 2][col] != 1) {
                    row++;
                }
                calcMap[row][col] = 1;
                calcMap[row + 1][col] = 1;
                break;
        }
    }

    private static boolean isIn(int row, int col) {
        return 0 <= row && row < 10 && 0 <= col && col < 10;
    }

    private static void copyMap(boolean type) {
        if (type) { // 그대로 복사
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 4; j++) {
                    calcMap[i][j] = map[i][j];
                }
            }
        } else {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    calcMap[i][j] = map[9 - j][i];
                }
            }
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 4; j++) {
                    calcMap[i][j] = calcMap[i][j + 6];
                }
            }
        }
    }

    private static void reverseMap(boolean type) {
        if (type) { // 그대로 복사
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 4; j++) {
                    map[i][j] = calcMap[i][j];
                }
            }
        } else {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 4; j++) {
                    map[3 - j][i] = calcMap[i][j];
                }
            }
        }
    }
}