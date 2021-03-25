function solution(arr) {
    const minOfRange = (x, y) => {
        if (minDP[x][y]) return minDP[x][y];
        let min = Infinity;
        for (let i = x; i < y; i++) {
            if (op[i] === "+") {
                min = Math.min(min, minOfRange(x, i) + minOfRange(i + 1, y));
            } else {
                min = Math.min(min, minOfRange(x, i) - maxOfRange(i + 1, y));
            }
        }
        minDP[x][y] = min;
        return min;
    };

    const maxOfRange = (x, y) => {
        if (maxDP[x][y]) return maxDP[x][y];
        let max = -Infinity;
        for (let i = x; i < y; i++) {
            if (op[i] === "+") {
                max = Math.max(max, maxOfRange(x, i) + maxOfRange(i + 1, y));
            } else {
                max = Math.max(max, maxOfRange(x, i) - minOfRange(i + 1, y));
            }
        }
        maxDP[x][y] = max;
        return max;
    };

    let nums = [];
    let op = [];
    for (let i = 0; i < arr.length; i++) {
        if (i % 2 == 0) nums.push(arr[i]);
        else op.push(arr[i]);
    }
    let N = nums.length;
    nums = nums.map((x) => x * 1);
    let maxDP = Array.from({ length: N }, () => new Array(N));
    let minDP = Array.from({ length: N }, () => new Array(N));
    for (let i = 0; i < N; i++) {
        maxDP[i][i] = nums[i];
        minDP[i][i] = nums[i];
    }

    let answer = maxOfRange(0, N - 1);

    return answer;
}
