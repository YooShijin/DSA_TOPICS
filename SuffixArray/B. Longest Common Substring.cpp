#include <bits/stdc++.h>
using namespace std;
using std::cout;
using std::endl;
using std::pair;
using std::vector;

void radix_sort(vector<pair<pair<int, int>, int>> &arr)
{
    // with radix sort, we actually have to sort by the second element first
    for (int i : vector<int>{2, 1})
    {
        auto key = [&](const pair<pair<int, int>, int> &x)
        {
            return i == 1 ? x.first.first : x.first.second;
        };
        int max = 0;
        for (const auto &i : arr)
        {
            max = std::max(max, key(i));
        }
        vector<int> occs(max + 1);
        for (const auto &i : arr)
        {
            occs[key(i)]++;
        }
        vector<int> start(max + 1);
        for (int i = 1; i <= max; i++)
        {
            start[i] = start[i - 1] + occs[i - 1];
        }

        vector<pair<pair<int, int>, int>> new_arr(arr.size());
        for (const auto &i : arr)
        {
            new_arr[start[key(i)]] = i;
            start[key(i)]++;
        }
        arr = new_arr;
    }
}

vector<int> build_lcp(const string &s, const vector<int> &p)
{
    int n = s.size();
    vector<int> r(n), l(n);
    for (int i = 0; i < n; i++)
        r[p[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (r[i] == 0)
            continue;
        int j = p[r[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        l[r[i]] = k;
        if (k)
            k--;
    }
    return l;
}

void solve()
{
    std::string str;
    std::cin >> str;
    int cl = str.size();
    str += '#';
    std::string t;
    std::cin >> t;
    str += t;
    str += '$';
    const int n = str.size(); // just a shorthand

    vector<pair<pair<int, int>, int>> suffs(n);
    for (int i = 0; i < n; i++)
    {
        suffs[i] = {{str[i], str[i]}, i};
    }
    std::sort(suffs.begin(), suffs.end());
    vector<int> equiv(n);
    for (int i = 1; i < n; i++)
    {
        auto [c_val, cs] = suffs[i];
        auto [p_val, ps] = suffs[i - 1];
        equiv[cs] = equiv[ps] + (c_val > p_val);
    }

    for (int cmp_amt = 1; cmp_amt < n; cmp_amt *= 2)
    {
        for (auto &[val, s] : suffs)
        {
            // the order numbers for the left half and right half respectively
            val = {equiv[s], equiv[(s + cmp_amt) % n]};
        }
        // without the radix sort optimization, we would use `std::sort`
        radix_sort(suffs);

        // assign numbers to the newly sorted suffixes
        for (int i = 1; i < n; i++)
        {
            auto [c_val, cs] = suffs[i];
            auto [p_val, ps] = suffs[i - 1];
            equiv[cs] = equiv[ps] + (c_val > p_val);
        }
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++)
    {
        p[i] = suffs[i].second;
    }

    auto lcp = build_lcp(str, p);
    int ans = 0;
    int a = 0;
    int b = n - 1;
    for (int i = 1; i < n; i++)
    {
        if (((cl - p[i - 1]) * (cl - p[i])) < 0)
        {
            if (ans < lcp[i])
            {
                a = p[i - 1];
                b = p[i];
                ans = lcp[i];
            }
        }
    }
    std::string hue = "";
    if (ans)
    {
        while (a < n && b < n && str[a] == str[b])
        {
            hue += str[a];
            a++;
            b++;
        }
    }
    cout << hue << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
