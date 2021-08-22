#include <bits/stdc++.h>
using namespace std;
int mod;

struct mat {
public:
    long long a, b, c, d;
    mat(long long val = 0)
    {
        a = val;
        b = val;
        c = val;
        d = val;
    }
};
mat multiply (mat f, mat s ) {
    mat ans;
    ans.a = (f.a * s.a + f.b * s.c) % mod;
    ans.b = (f.a * s.b + f.b * s.d) % mod;
    ans.c = (f.c * s.a + f.d * s.c) % mod;
    ans.d = (f.c * s.b + f.d * s.d) % mod;
    return ans;
}

class segmentTree {
    mat tree[800005];
    int left, right, siz;
public:
    segmentTree(vector<mat> &arr)
    {
        siz = arr.size() - 1;
        left = 0, right = siz;
        buildTree(0, siz, 0, arr);
    }

    void buildTree(int l, int r, int index, vector<mat> &arr)
    {
        if (l == r)
        {
            tree[index] = arr[l];
            return;
        }
        int mid = (l + r) / 2;

        buildTree(l, mid, 2 * index + 1, arr);
        buildTree(mid + 1, r, 2 * index + 2, arr);
        tree[index] = multiply(tree[2 * index + 1], tree[2 * index + 2]);
    }

    mat queryHelper(int l, int r, int index, int le, int re)
    {
        mat identity(0);
        identity.a = 1;
        identity.d = 1;
        if (le >= l and re <= r)
            return tree[index];
        if (l > re or r < le)
            return identity;
        int mid = (le + re) / 2;
        return multiply(queryHelper(l, r, 2 * index + 1, le, mid), queryHelper(l, r, 2 * index + 2, mid + 1, re));
    }

    mat query(int l, int r)
    {
        return queryHelper(l, r, 0, 0, siz);
    }
};

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, q;
    cin >> mod >> n >> q;
    vector<mat> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].a;
        cin >> arr[i].b;
        cin >> arr[i].c;
        cin >> arr[i].d;
    }
    segmentTree tree(arr);
    while (q--)
    {

        int l, r;
        cin >> l >> r;
        l--, r--;
        mat ans;
        ans = tree.query(l, r);
        cout << ans.a << " " << ans.b << "\n";
        cout << ans.c << " " << ans.d << "\n";
        cout << endl;
    }
}