#include<bits/stdc++.h>
using namespace std;

class segTree {
    vector<long long> segMax, lazy, pre, suff, sum;
    int siz;
public:
    segTree(vector<long long> &arr)
    {
        siz = arr.size() - 1;
        segMax.resize(4 * siz + 10);
        pre.resize(4 * siz + 10);
        suff.resize(4 * siz + 10);
        sum.resize(4 * siz + 10);
        lazy.resize(4 * siz + 10);
        buildTree(arr, 0, 0, siz);
    }

    void compute(int index)
    {
        sum[index] = sum[2 * index + 1] + sum[2 * index + 2];
        pre[index] = max(pre[2 * index + 1], sum[2 * index + 1] + pre[2 * index + 2]);
        suff[index] = max(suff[2 * index + 2], sum[2 * index + 2] + suff[2 * index + 1]);
        segMax[index] = max({segMax[2 * index + 1], segMax[2 * index + 2], suff[2 * index + 1] + pre[2 * index + 2]});
    }

    void buildTree(vector<long long> &arr, int index, int l, int r)
    {
        if (l == r)
        {
            segMax[index] = arr[l];
            pre[index] = arr[l];
            suff[index] = arr[l];
            sum[index] = arr[l];
            lazy[index] = INT_MAX;
            return;
        }
        int mid = (l + r) / 2;
        buildTree(arr, 2 * index + 1, l, mid);
        buildTree(arr, 2 * index + 2, mid + 1, r);
        compute(index);
        lazy[index] = INT_MAX;
    }

    void UpdateHelper(int l, int r, long long val, int index, int le, int re)
    {
        if (lazy[index] != INT_MAX)
        {
            sum[index] =  lazy[index] * (re - le + 1);
            pre[index] = max(1LL * 0, lazy[index] * (re - le + 1));
            suff[index] = max(1LL * 0, lazy[index] * (re - le + 1));
            segMax[index] = max(1LL * 0, lazy[index] * (re - le + 1));
            if (le != re)
            {
                lazy[2 * index + 1] = lazy[index];
                lazy[2 * index + 2] = lazy[index];
            }
            lazy[index] = INT_MAX;
        }
        if (l <= le and r >= re)
        {
            sum[index] = 1LL * val * (re - le + 1) ;
            pre[index] = max(1LL * val * (re - le + 1), 1LL * 0);
            suff[index] = max(1LL * val * (re - le + 1), 1LL * 0);
            segMax[index] = max(1LL * 0, 1LL * val * (re - le + 1));
            if (le != re)
            {
                lazy[2 * index + 1] = val;
                lazy[2 * index + 2] = val;
            }
            return;
        }
        if (l > re or r < le)
            return;
        int mid = (le + re) / 2;
        UpdateHelper(l, r, val, 2 * index + 1, le, mid);
        UpdateHelper(l, r, val, 2 * index + 2, mid + 1, re);
        compute(index);
    }

    void update(int l, int r, int val)
    {
        UpdateHelper(l, r, val, 0, 0, siz);
    }

    long long query()
    {
        return segMax[0];
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<long long> arr(n, 0);
    segTree tree(arr);
    while (m--)
    {
        int l, r, val;
        cin >> l >> r >> val;
        r--;
        tree.update(l, r, val);
        cout << tree.query() << endl;
    }
}