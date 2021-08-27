#include<bits/stdc++.h>
using namespace std;

class segTree {
    vector<long long> Tree, lazy;
    int siz;
public:
    segTree(vector<long long> &arr)
    {
        siz = arr.size() - 1;
        Tree.resize(4 * siz + 10);
        lazy.resize(4 * siz + 10);
        buildTree(arr, 0, 0, siz);
    }

    void buildTree(vector<long long> &arr, int index, int l, int r)
    {
        if (l == r)
        {
            Tree[index] = 0;
            return;
        }
        int mid = (l + r) / 2;
        buildTree(arr, 2 * index + 1, l, mid);
        buildTree(arr, 2 * index + 2, mid + 1, r);
        Tree[index] = Tree[2 * index + 1] + Tree[2 * index + 2];
    }

    void UpdateHelper(int l, int r, int val, int index, int le, int re)
    {
        Tree[index] += lazy[index] * (re - le + 1);
        if (le != re)
        {
            lazy[2 * index + 1] += lazy[index];
            lazy[2 * index + 2] += lazy[index];
        }
        lazy[index] = 0;
        if (l <= le and r >= re)
        {
            Tree[index] += 1LL * val * (re - le + 1);
            if (le != re)
            {
                lazy[2 * index + 1] += val;
                lazy[2 * index + 2] += val;
            }
            return;
        }
        if (l > re or r < le)
            return;
        int mid = (le + re) / 2;
        UpdateHelper(l, r, val, 2 * index + 1, le, mid);
        UpdateHelper(l, r, val, 2 * index + 2, mid + 1, re);
        Tree[index] = Tree[2 * index + 1] + Tree[2 * index + 2];
    }

    void update(int l, int r, int val)
    {
        UpdateHelper(l, r, val, 0, 0, siz);
    }

    long long queryHelper(int l, int r, int index, int le, int re)
    {
        Tree[index] += lazy[index] * (re - le + 1);
        if (le != re)
        {
            lazy[2 * index + 1] += lazy[index];
            lazy[2 * index + 2] += lazy[index];
        }
        lazy[index] = 0;
        if (l <= le and re <= r)
        {
            return Tree[index];
        }
        if (l > re or r < le)
            return 0;
        int mid = (le + re) / 2;
        return (queryHelper(l, r, 2 * index + 1, le, mid) + queryHelper(l, r, 2 * index + 2, mid + 1, re));
    }

    long long query(int l, int r)
    {
        return queryHelper(l, r, 0 , 0, siz);
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
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r, val;
            cin >> l >> r >> val;
            r--;
            tree.update(l, r, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            r--;
            cout << tree.query(l, r) << endl;
        }

    }
}