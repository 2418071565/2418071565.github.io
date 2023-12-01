


首先我们知道，一个序列的最大字典序就是倒序；一个序列的最大字典序就是升序。也就是说一个序列如果已经是倒叙的话，那么就已经没有比它字典序更大的排列了。有了这个前提我们再往下看。

我们要找一个序列的下一个排列，也就是尽可能小的增加当前序列的字典序，那么就是要让增大数字的下标尽可能的大，也就是靠近数组的后面。

有了上面的前提，我们可以想一下，如果该数组的一段后缀，已经是倒叙的了，说明对于该后缀已经不能通过该边其元素的位置关系来增大其字典序了，那么我们就只能增大该后缀的前一个元素了。

如下例，红色部分就是已经完全倒序了，我们只能增大蓝色位置元素。
$$
14{\color{Blue}5 } {\color{Red}632}
$$
将其变成
$$
14{\color{Blue}6 } {\color{Red}532}
$$
这时我们发现红色部分的字典序是可以减小的，我们把它变成升序即可。
$$
14{\color{Blue}6 } {\color{Red}235}
$$
这样就可也保证尽可能小的增大字典序

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        for(int i=nums.size()-1;i>0;--i)
            if(nums[i]>nums[i-1]){
                sort(nums.begin()+i,nums.end());
                swap(*upper_bound(nums.begin()+i,nums.end(),nums[i-1]),nums[i-1]);return;
            }
        sort(nums.begin(),nums.end());
    }
};
```




