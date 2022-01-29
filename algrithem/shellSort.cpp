#include <iostream>
#include <vector>
using namespace std;

void shellSort(vector<int> &a)
{
    int N = a.size();
    int h = 1;
    while(h < N/3)
    {
        h = 3*h +1;
    }
    while(h >= 1)
    {
        for(int i = h; i < N; i++)
        {
            for(int j = i; j >= h && a[j] < a[j-h]; j -= h)
            {
                int temp = a[j];
                a[j] = a[j - h];
                a[j - h] = temp;
            }
            h = h/3;
        }
    }
}

int main()
{
    vector<int> num  = {1,5,3,6,8,4,9,7,0};
    shellSort(num);
    for(int i = 0; i < num.size(); i++)
    {
        cout << num[i] << endl;
    }
    return 0;
}
