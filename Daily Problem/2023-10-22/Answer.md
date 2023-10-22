
这题我们也先整理需要满足的条件：

- 一组内的数字相同
- 任意两组的大小差别不超过 1


因此，我们可以发现，一个数是多少不重要，出现了多少次才重要。因此我们先统计每个数出现的频率。

同时，由于不同组大小的差别不超过 111，因此，假设其中较小的一组大小为 xxx ，较大的一组大小为 x+1x+1x+1，而某个数出现了 ggg 次，我们可以据此计算出该数字最少被分为多少组。这个问题可以通过贪心地分为 x+1x+1x+1 大小的组，如果最后一组的数量不足 x+1x+1x+1，则将前面的一些组别调整为 xxx 大小实现。而若无法这样实现，则无法实现分组。（具体逻辑可见代码）

而为了保证最低频率的一组是可以完成分组的，我们需要枚举的 xxx 满足其不超过最低频率。

最后，我们论证这样做法的时间复杂度是 O(n) 的。

我们枚举的频率是从 000 到最小频率，而第二层循环表示的是数组中出现的不同的数的个数。这两者的乘积相当于把每个数的出现频率低估到最小频率，因此两者的乘积小于每个数字出现的频率之和，也就小于数组长度。



```cpp
class Solution
{
public:
    int minGroupsForValidAssignment(const vector<int> &a)
    {
        map<int, int> mp;
        for (int i = 0; i < a.size(); ++i)
            mp[a[i]]++;
        int mi = max_element(mp.begin(),mp.end(),[](pair<int,int>a,pair<int,int>b){return a.second<b.second;})->second;

        function<bool(int)> check = [&](int m)
        {
            for (auto &x : mp)
            {
                int b = x.second % m;
                if(!b)continue;
                int c = x.second / m;
                if (b + c < m - 1)return false;
            }
            return true;
        };

        int mi1 = 1;
        for(int i = 1;i<=mi;++i)
            if(check(i)) mi1 = i;
        int ans = 0;
        for (auto &x : mp)ans += (x.second + mi1 - 1)/ mi1;
        return ans;
    }
};
```