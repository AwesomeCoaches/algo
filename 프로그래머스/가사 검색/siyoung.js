class Node {
    constructor(char) {
        this.char = char;
        this.childs = {};
        this.totalBranch = 1;
    }

    append(char) {
        this.childs[char] = new Node(char);
    }
}

class Tree {
    constructor() {
        this.head = new Node("");
        this.head.totalBranch = 0;
    }

    readWord(word) {
        let pos = this.head;
        let path = [pos];
        let flag = true;
        for (let i = 0; i < word.length; i++) {
            let next = word.charAt(i);
            if (!pos.childs.hasOwnProperty(next)) {
                pos.append(next);
                flag = false;
            }
            pos = pos.childs[next];
            if (flag) path.push(pos);
        }
        for (let node of path) {
            node.totalBranch += 1;
        }
    }

    getWord(word) {
        let pos = this.head;
        for (let i = 0; i < word.length; i++) {
            let char = word.charAt(i);
            if (char === "?") break;
            if (!pos.childs.hasOwnProperty(char)) return 0;
            pos = pos.childs[char];
        }
        return pos.totalBranch;
    }
}

function solution(words, queries) {
    let answer = [];
    let tree = {};
    let reverseTree = {};

    words.forEach((word) => {
        let reversed = word.split("").reverse().join("");
        if (!tree.hasOwnProperty(word.length)) tree[word.length] = new Tree();
        tree[word.length].readWord(word);
        if (!reverseTree.hasOwnProperty(reversed.length))
            reverseTree[word.length] = new Tree();
        reverseTree[word.length].readWord(reversed);
    });

    queries.forEach((query) => {
        if (!tree.hasOwnProperty(query.length)) answer.push(0);
        else {
            if (query.charAt(0) === "?") {
                query = query.split("").reverse().join("");
                answer.push(reverseTree[query.length].getWord(query));
            } else {
                answer.push(tree[query.length].getWord(query));
            }
        }
    });

    return answer;
}
