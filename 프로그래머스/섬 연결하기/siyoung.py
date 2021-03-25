def findP(x, parents):
    if x not in parents or x == parents[x]:
        parents[x] = x
        return x
    parents[x] = findP(parents[x], parents)
    return parents[x]

def union(a, b, parents):
    a = findP(a, parents)
    b = findP(b, parents)
    a, b = sorted([a, b])
    parents[b] = a
    
def isUnion(parents):
    x = -1
    for no in parents:
        y = findP(no, parents)
        if x == -1:
            x = y
            continue
        if x != y:
            return False
        x = y
    return True
    
def solution(n, costs):
    answer = 0
    parents = {}
    costs.sort(key=lambda x:x[2])
    
    for cost in costs:
        a, b, w = cost
        parents[a] = a
        parents[b] = b
        
    for cost in costs:
        a, b, w = cost
        ap = findP(a, parents)
        bp = findP(b, parents)
        if ap == bp:
            continue
        answer += w
        union(ap, bp, parents)
        if isUnion(parents):
            break
    
    return answer