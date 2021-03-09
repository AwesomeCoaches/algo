```
import java.util.*;

public int solution(int[] priorities, int location) {

	int[] prints = new int[priorities.length];

	List<int[]> list = new ArrayList<>();
	for (int i = 0; i < priorities.length; i++) {
		list.add(new int[] { i + 1, priorities[i] });
	}

	int priority = 0;
	while (!list.isEmpty()) {
		int index = 0;
		boolean flag = false;
		for (int j = index + 1; j < list.size(); j++) {
			if (list.get(index)[1] < list.get(j)[1]) { // 우선순위 비교 중 우선순위가 높은 것이 있다면
				int[] temp = list.remove(index); // 순서를 맨 뒤로
				list.add(temp);
				flag = true;
				break;
			}
		}

		if (!flag) {
			prints[list.remove(index)[0] - 1] = priority + 1;
			priority++;
		}
		index++;
	}

	return prints[location];
}
```
