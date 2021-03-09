#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    priority_queue<int> pq;
    
    for(int i : priorities){
        pq.push(i);
    }
    
    bool flag = true;
    int cnt = 0;
    while(flag){
        
        for(int i = 0; i < priorities.size(); i++){
            if(priorities[i] == 0) continue;
            if(priorities[i] == pq.top()){
                priorities[i] = 0;
                pq.pop();
                cnt++;
                
                if(i == location){
                    flag = false;
                    answer = cnt;
                    break;
                }
            }
        }
    }
    
    
    return answer;
}
