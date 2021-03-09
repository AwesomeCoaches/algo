# inputs
priorities = [2, 1, 3, 2]
location = 2

# solution
def solution(priorities, location):
    num = len(priorities)
    nums = list(range(-num, 0))
    target = nums[location]
    result = []
    _result = []
    last = 0
    _last = 0
    while priorities:
        first = priorities.pop(0)
        _first = nums.pop(0)
        for priority in priorities:
            if first < priority:
                last = first
                _last = _first
                break
        if last:
            priorities.append(last)
            nums.append(_last)
        else:
            result.append(first)
            _result.append(_first)
        last = 0
    answer = _result.index(target) + 1
    return answer

# run
solution(priorities, location)