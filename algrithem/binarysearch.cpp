#include <iostream>
#include <vector>
using namespace std;
int BinarySearch(int target, vector<int> & a)
{
    int lo = 0;
    int hi = a.size() - 1;
    while(lo <= hi)
    {
        int mid = lo + (hi - lo)/2;
        if(target < a[mid])
            hi = mid - 1;
        else if (target > a[mid]){
                        lo = mid + 1;
        }
        else
            return mid;
    }
    return  -1;
}
int main()
{
    vector<int> num  = {1,2,3,4,5,6,7,8,9,10,11,12};
    cout << BinarySearch(10, num) << endl;
}
    