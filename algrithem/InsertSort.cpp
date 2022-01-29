#include <iostream>
#include <vector>
using namespace std;

void insertSort(vector<int> &a)
{
    int N = a.size();
    for(int i = 1; i < N; i++)
    {
        int j = i;
        int temp = a[i];
        while(j > 0 && a[j-1] > temp)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = temp;
    }
}
/*
例如:
1，2，3，4，5，6，0
循环到 i = j = 6
进入while循环
第1次：1，2，3，4，5，6，6
第2次：1，2，3，4，5，5，6
第3次：1，2，3，4，4，5，6
第4次：1，2，3，3，4，5，6
第5次：1，2，2，3，4，5，6
第6次：1，1，2，3，4，5，6
此时j--之后j=0跳出while循环
最后：0，1，2，3，4，5，6结束
*/

int main()
{
    vector<int> num  = {1,5,3,6,8,4,9,7,0};
    insertSort(num);
    for(int i = 0; i < num.size(); i++)
    {
        cout << num[i] << endl;
    }
    return 0;
}