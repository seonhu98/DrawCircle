#include <iostream>
#include <string>
#include <vector>
// 양꼬치 1인분 12,000원, 음료수 2,000원 
// n은 양꼬치 인분, k는 음료수 개수
using namespace std;

#define SHEEP 12000;
#define DRINK 2000;

int solution(int n, int k)
{
    int answer = 0;
    int sheep_p = 0;
    int drink_p = 0;
    int drink_num =  n / 10;

    if(n > 0 && n < 1000)
    {
        sheep_p = n * SHEEP;
    }
    
    if(drink_num > 0 && k < 1000)
    {
        drink_p = (k - drink_num) * DRINK;
    }
    
    else if(drink_num == 0 && k < 1000)
    {
        drink_p = k * DRINK;
    }

    answer = sheep_p + drink_p;

    return answer;
}
