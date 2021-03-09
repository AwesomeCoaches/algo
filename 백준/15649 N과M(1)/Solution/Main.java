import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    static int N, M;
    static int[] number;
    static boolean[] visit;
    static StringBuilder result;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        // 입력
        result = new StringBuilder();
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        number = new int[M + 1];
        visit = new boolean[N + 1];
        permutation(1);

        System.out.println(result);
    }

    private static void permutation(int cnt) {
        if (cnt == M + 1) {
            for (int i = 1; i <= M; i++) {
                result.append(number[i]).append(' ');
            }
            result.append('\n');
            return;
        }

        for (int i = 1; i <= N; i++) {
            if (!visit[i]){
                number[cnt] = i;
                visit[i] = true;
                permutation(cnt+1);
                visit[i] = false;
            }
        }
    }
}
