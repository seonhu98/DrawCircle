// 정수 n번째 이후의 원소부터 앞으로 옮겨올거임
// 리스트의 길이는 2~30 사이
// 원소는 1~9 사이의 정수
// n은 1~리스트길이 사이의 정수

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> num_list, int n)
{
    vector<int> answer = num_list;
    int temp_amswer;
    int size = answer.size();
    int vec_num = n - 1;
    if(2 <= size && size <= 30 && 1 <= n  && n <= size)
    {
        for (int i = 0; i < n; i++)
        {
            if(1 <= answer[i] && answer[i] <= 9)
            {
                temp_amswer = answer[0];
                answer.push_back(temp_amswer);
                answer.erase(answer.begin());
            }
        }
    }
    return answer;
}
