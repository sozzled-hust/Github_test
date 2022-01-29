#include <iostream>
#include<vector>

using namespace std;

/* N^2比较，N^2交换 */
void selectSort(vector<int> &a)
{
    if (a.size() == 0)
        return;
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = i+1; j < a.size(); j++)
        {
            if(a[i] >= a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

/* N^2比较，N交换 */
void selectSort_N(vector<int> &a)
{
    if (a.size() == 0)
        return;
    for(int i = 0; i < a.size(); i++)
    {
        int min = i;
        for(int j = i+1; j < a.size(); j++)
        {
            if(a[i] > a[j])
            {
                min = j;
            }
            int temp = a[min];
            a[min] = a[i];
            a[i] = temp;
        }
    }
}

int main()
{
    vector<int> num  = {1,5,3,6,8,4,9,7,0};
    selectSort_N(num);
    for(int i = 0; i < num.size(); i++)
    {
        cout << num[i] << endl;
    }
}

