function removeZero(s) {
    let cnt = 0;
    let nextString = "";
    for (let c = 0; c < s.length; c++) {
        if (s.charAt(c) === "0") cnt++;
        else nextString += s.charAt(c);
    }
    return [nextString, cnt];
}

function solution(s) {
    let removed = 0;
    let rm = 0;
    let cnt = 0;
    while (s !== "1") {
        [s, rm] = removeZero(s);
        s = s.length.toString(2);
        cnt++;
        removed += rm;
    }
    return [cnt, removed];
}
