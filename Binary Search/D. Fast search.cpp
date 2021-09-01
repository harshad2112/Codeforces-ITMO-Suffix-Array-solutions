#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> &arr, int val)
{
    int l = 0, r = arr.size() - 1, mid, index;
    index = r + 1;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (arr[mid] >= val)
        {
            index = mid;
            r = mid - 1;
        }
        else if (arr[mid] < val)
        {
            l = mid + 1;
        }
    }
    return index;

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, q;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    cin >> q;
    while (q--)
    {
        int val1, val2;
        cin >> val1 >> val2;
        val2++;
        cout << binarySearch(arr, val2) - binarySearch(arr, val1) << endl;
    }
}