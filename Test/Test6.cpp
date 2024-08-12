#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> arr, vector<int> query)
{
    vector<int> answer = arr; 
    for (int i = 0; i < query.size(); i++)
    {
        int len = answer.size();
        int num = query[i];
        if (i % 2 == 0)
        {
            for (int j = num; j < len-1; j++)
            {
                answer.pop_back();
            }
        }
        else
        {
            for (int z = 0; z < num; z++)
            {
                answer.erase(answer.begin());
            }
        }
    }

    return answer;
}
