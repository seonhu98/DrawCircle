#include <iostream>
#include <string>
#include <vector>
#include <string.h>

//접두사인지 확인하기
//각 string의 길이는 1과 100사이이며, 영소문자로만 이루어져 있음.
//참이면 1, 거짓이면 0반환

using namespace std;

int solution(string my_string, string is_prefix)
{
    int answer = 0;
    int my_string_len = my_string.length();
    int is_prefix_len = is_prefix.length();
    if(my_string_len >= is_prefix_len && 1 <= my_string_len && my_string_len <= 100)
    {
        char cmy_string[my_string_len];
        char cis_prefix[is_prefix_len];
        strcpy(cmy_string, my_string.c_str());
        strcpy(cis_prefix, is_prefix.c_str());

        for(int i = 0; i < is_prefix_len; i++)
        {
            if(cmy_string[i]==cis_prefix[i])
            {
                answer = 1;
            }
            else if (cmy_string[i]!=cis_prefix[i])
            {
                answer = 0;
                i = 0;
                break;
            }
        }
    }
    return answer;
}