function solution(land, height) {
    let delta = [
        [0, 1],
        [1, 0],
        [-1, 0],
        [0, -1],
    ];
    let N = land.length;
    let no = 0;

    const isWall = (r, c) => !(0 <= r && r < N && 0 <= c && c < N);

    const bfs = (r, c, no) => {
        let stack = [];
        stack.push([r, c]);
        visit[r][c] = no;
        while (stack.length) {
            [r, c] = stack.pop();

            for (let [dr, dc] of delta) {
                let nr = r + dr;
                let nc = c + dc;
                if (isWall(nr, nc) || visit[nr][nc] !== -1) continue;
                if (Math.abs(land[nr][nc] - land[r][c]) > height) continue;
                stack.push([nr, nc]);
                visit[nr][nc] = no;
            }
        }
    };
    const findP = (x) => {
        if (x === parents[x]) return x;
        parents[x] = findP(parents[x]);
        return parents[x];
    };

    const union = (a, b) => {
        a = findP(a);
        b = findP(b);
        [a, b] = [a, b].sort((x, y) => x - y);
        parents[b] = a;
    };

    const isUnion = () => {
        for (let i = 0; i < parents.length; i++) {
            if (findP(parents[i]) != 0) return false;
        }
        return true;
    };

    let visit = Array.from({ length: N }, () => new Array(N).fill(-1));

    for (let r = 0; r < N; r++) {
        for (let c = 0; c < N; c++) {
            if (visit[r][c] !== -1) continue;
            bfs(r, c, no++);
        }
    }

    let parents = visit;
    delta = [
        [0, 1],
        [1, 0],
    ];

    let edges = {};

    for (let r = 0; r < N; r++) {
        for (let c = 0; c < N; c++) {
            for (let [dr, dc] of delta) {
                let nr = r + dr;
                let nc = c + dc;
                if (isWall(nr, nc) || parents[nr][nc] === parents[r][c])
                    continue;
                let key = [parents[nr][nc], parents[r][c]].sort();
                if (!edges.hasOwnProperty(key)) edges[key] = Infinity;
                edges[key] = Math.min(
                    edges[key],
                    Math.abs(land[r][c] - land[nr][nc])
                );
            }
        }
    }

    // console.log(parents);
    // console.log(edges);

    parents = new Array(no).fill(0).map((v, i) => i);
    edges = Object.entries(edges).sort((a, b) => a[1] - b[1]);

    let answer = 0;

    for (let i = 0; !isUnion(); i++) {
        let [key, dist] = edges[i];
        let [a, b] = key.split(",");
        a *= 1;
        b *= 1;
        a = findP(a);
        b = findP(b);
        if (a === b) continue;
        answer += dist;
        union(a, b);
    }

    return answer;
}
