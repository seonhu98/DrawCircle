#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, int k)
{
    int answer = 0;
    int line = board.size();
    int row = board[0].size();
    int second;
    int z = 0;
    for (int i = 0; i < line; i++)
    {
        for (int count = 0; count < row; count++)
        {
            second = board[i][count];

            if (i + count <= k)
            {
                answer = answer + second;
            }
        }
    }
    return answer;
}