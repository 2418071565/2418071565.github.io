Exercise
=================
|题目|难度|AC代码|知识|
|:-:|:-:|:-:|:-:|
|[LC.187](https://leetcode.cn/problems/repeated-dna-sequences/description/)|中等|LC.187|哈希表|
|[LC.1](https://leetcode.cn/problems/two-sum/description/)|简单|LC.1|哈希表优化枚举|


#### LC.187
python的哈希表是字典
```python
class Solution:
    def findRepeatedDnaSequences(self, s: str) -> List[str]:
        n = len(s)
        mp = {}
        for i in range(n - 9):
            now = s[i:i + 10]
            if mp.get(now) == None:
                mp[now] = 0
            mp[now] += 1
        ans = []
        for key,val in mp.items():
            if val > 1:
               ans.append(key)
        return ans 
```


#### LC.1
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> hash;
        vector<int> res;
        for(int i=0;i<nums.size();++i)
            hash[nums[i]]++;
        for(int i=0;i<nums.size();++i)
        {
            hash[nums[i]]--;
            if(hash[target-nums[i]]!=0)
                res.push_back(i);
            hash[nums[i]]++;
        }
        return res;
    }
};
```