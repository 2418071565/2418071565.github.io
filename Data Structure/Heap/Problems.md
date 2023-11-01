Exercise
=================
|题目|难度|AC代码|知识|
|:-:|:-:|:-:|:-:|
|[LC.1438](https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)|中等|LC.1438|二叉堆|
|[LC.2762](https://leetcode.cn/problems/continuous-subarrays/description/)|中等|LC.2762|二叉堆|
|[SP16254](https://www.luogu.com.cn/problem/SP16254)|普及+/提高|SP16254|维护两个堆|

### LC.1438
```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int ans=0,l=0,r=0;
        multiset<int> s;
        for(;r<nums.size();++r){
            s.insert(nums[r]);
            while(*s.rbegin()-*s.begin()>limit)
                s.erase(s.find(nums[l++]));
            ans=max(ans,r-l+1);
        }
        return ans;
    }
};
```

### LC.2762
```cpp
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        long long res=0;
        int l=0,r=0;
        multiset<int> s;
        for(;r<nums.size();++r){
            s.insert(nums[r]);
            while(*s.rbegin()-*s.begin()>2){
                s.erase(s.find(nums[l++]));
            }
            res+=r-l+1;
        }
        return res;
    }
};
```

### SP16254
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(2e6+7)
typedef long long ll;
//const int p = 998244353;
int T;
inline int input() {
    bool sym = false; int res = 0; char ch = getchar();
    while (!isdigit(ch))sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch))res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
void solve() {
    priority_queue<int>lef;
    priority_queue<int, vector<int>, greater<int> >righ;
    while (1) {
        int a = input();
        if (a == 0)break;
        if (a == -1) {
            if (lef.size() >= righ.size()) {
                cout << lef.top() << '\n';
                lef.pop();
            }
            else {
                cout << righ.top() << '\n';
                righ.pop();
            }
        }
        else {
            if (righ.empty() || a >= righ.top())
                righ.push(a);
            else
                lef.push(a);
            if (lef.size() >= righ.size() + 2)
                righ.push(lef.top()), lef.pop();
            else if (righ.size() >= lef.size() + 2)
                lef.push(righ.top()), righ.pop();
        }
    }

}



int main() {
    ios::sync_with_stdio(false);//int T;
    for (T=input(); T--;)
        solve();
    return 0;
}
```