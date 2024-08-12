// a,b 받아서 문자열 더하가처럼 합쳐지게끔
// a+b || b+a 둘 중 큰 것만 리턴하는 함수 만들기
// a,b는 1과 10000사이의 정수이다.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

int solution(int a, int b)
{

    int answer = 0;
    int aanswer, banswer = 0;
    string s_a, s_b, aresult, bresult;
    if (1 <= a, b < 10000)
    {
        s_a = to_string(a);
        s_b = to_string(b);
        aresult = s_a + s_b;
        bresult = s_b + s_a;

        aanswer = stoi(aresult);
        banswer = stoi(bresult);
        if (aanswer >= banswer)
        {
            answer = aanswer;
        }
        else if (aanswer < banswer)
        {
            answer = banswer;
        }
    }
    return answer;
}
