#include <bits/stdc++.h>
using namespace std;

class segmentTree {
    vector<long long> segMax;
    vector<long long> suff;
    vector<long long> pre;
    vector<long long> sum;
    int left, right, siz;
public:
    segmentTree(vector<int> &arr)
    {
        siz = arr.size() - 1;
        segMax.resize(siz * 4 + 10);
        suff.resize(siz * 4 + 10);
        pre.resize(siz * 4 + 10);
        sum.resize(siz * 4 + 10);
        left = 0, right = siz;
        buildTree(0, siz, 0, arr);
    }

    void compute(int index)
    {
        sum[index] = sum[2 * index + 1] + sum[2 * index + 2];
        pre[index] = max(pre[2 * index + 1], sum[2 * index + 1] + pre[2 * index + 2]);
        suff[index] = max(suff[2 * index + 2], sum[2 * index + 2] + suff[2 * index + 1]);
        segMax[index] = max({segMax[2 * index + 2], segMax[2 * index + 1], suff[2 * index + 1] + pre[2 * index + 2]});
    }

    void buildTree(int l, int r, int index, vector<int> &arr)
    {
        if (l == r)
        {
            segMax[index] = arr[l];
            suff[index] = arr[l];
            pre[index] = arr[l];
            sum[index] = arr[l];
            return;
        }
        int mid = (l + r) / 2;

        buildTree(l, mid, 2 * index + 1, arr);
        buildTree(mid + 1, r, 2 * index + 2, arr);
        compute(index);
    }

    void updateHelper(int pos, int val, int l, int r, int index)
    {
        if (r == l)
        {
            segMax[index] = val;
            suff[index] = val;
            pre[index] = val;
            sum[index] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos >= l and pos <= mid)
            updateHelper(pos, val, l, mid, 2 * index + 1);
        else
            updateHelper(pos, val, mid + 1, r, 2 * index + 2);
        compute(index);
    }

    void update(int pos, int val)
    {
        updateHelper(pos, val, 0, right, 0);
    }

    long long queryHelper(int l, int r, int index, int le, int re)
    {
        if (l <= le and r >= re) {
            return segMax[index];
        }
        if (l > re or r < le or l>r)
        {
            return 0;
        }
        int mid = (le + re) / 2;
        return max(queryHelper(l, r, 2 * index + 1, le, mid), queryHelper(l, r, 2 * index + 2, mid + 1, re));
    }

    long long query(int l, int r)
    {
        return queryHelper(l, r, 0, 0, siz);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (auto &i : arr)
    {
        cin >> i;
    }
    segmentTree tree(arr);
    cout << max(tree.query(0, n - 1), (long long)0) << endl;
    while (q--)
    {
        int i, v;
        cin >> i >> v;
        tree.update(i, v);
        cout << max(tree.query(0, n - 1), (long long)0) << endl;
    }
}