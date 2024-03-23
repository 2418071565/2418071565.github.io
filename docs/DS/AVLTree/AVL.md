## **基本概念**

**平衡二叉搜索树**：简称平衡二叉树。由前苏联的数学家 Adelse-Velskil 和 Landis 在 1962 年提出的高度平衡的二叉树，根据科学家的英文名也称为 AVL 树。

**性质：**

1. 平衡二叉树可以是空树。
2. 如果不是空树，任何一个节点的左右子树都是平衡二叉树，并且高度差的绝对值不超过 $1$。

**为什么要有平衡二叉树：**防止搜索二叉树退化为链表。

**平衡因子(Balance Factor)**，即左右两子树的高度差：

$$
BF=h_{left}-h_{right}
$$

平衡二叉树的任何一节点的平衡因子只有三个取值:$0,1,-1$，如果绝对值大于$1$，说明该树失衡，就需要进行调整。

## **实现**

## **节点结构**
```cpp
struct treenode
{
    int _val;//键值
    treenode* _parent;//父节点
    treenode* _l, * _r;//左右子树节点
    int _deepth;//树高度
    treenode(int val = 0) :_val(val), _deepth(1),_l(nullptr),_r(nullptr),_parent(nullptr) {}
}; 
```

## **基本接口**

```cpp
class AVLTree
{
    treenode* _root;//根节点
    void _insert(treenode*& , int );//插入
    treenode* _erase(treenode* , int);//删除
    treenode* get_lmax(treenode* );//获取左子树中的最大值
    treenode* LL_roate(treenode*);//左旋
    treenode* RR_roate(treenode*);//右旋
    treenode* LR_roate(treenode*);//左右旋
    treenode* RL_roate(treenode*);//右左旋
    treenode* _find(treenode* , int );//查找
    void _print(treenode* );//打印树节点
    
    void updata_deepth(treenode* root) { //更新树高度
    root ? root->_deepth = max(get_deepth(root->_l),get_deepth(root->_r)) + 1 : 0; 
    }
    
    int get_deepth(treenode* root){//获取树高度
    return root ? root->_deepth : 0; 
    }
    
    int get_balance_factor(treenode* root) { //获取平衡因子
    return root ? get_deepth(root->_l) - get_deepth(root->_r) : 0; 
    }
    
public:
    void insert(int data);//插入
    void erase(int data);//删除
    treenode* find(int data);//查找
    void print() { _print(_root); }//打印
};
```

## **失衡调整**

要调整失衡的 AVL 树，就要找到最小不平衡子树，通过调整不平衡子树，来调整失衡的AVL树。最小不平衡子树就是高度最小的失衡树，从插入点开始向上递归，第一个平衡因子绝对值大于 $1$ 的节点。

### **调整方法**

通过旋转调整不平衡子树，旋转的类型有四种情况：
$LL，LR，RR，RL$，分别对应失衡的四种情况。


1. 左子树深度高于右子树$(max \left \{ h_1,h_2\right \}-2=max\left \{ h_3,h_4\right \},即平衡因子等于2)$ 

    - 左子树的左子树深度高于左子树的右子树深度$(h_1>h_2,左子树平衡因子为1,RR)$
    - 左子树的右子树深度高于左子树的左子树深度$(h_2>h_1,左子树平衡因子为-1,LR)$
    
2. 右子树深度高于左子树$(max \left \{ h_3,h_4\right \}-2=max\left \{ h_1,h_2\right \},即平衡因子等于-2)$

    - 右子树的右子树深度高于右子树的左子树深度$(h_4>h_3,右子树平衡因子为-1,LL)$
    - 右子树的左子树深度高于右子树的右子树深度$(h_3>h_4,右子树平衡因子为1,RL)$

旋转的目的就是减少高度，通过降低整棵树的高度来平衡。哪边的树高，就把那边的树向上旋转。

#### 左旋 (LL)


 - 让其右子树代替该节点
 - 并将其右子树的左子树(如果有的话)代替其右子树
 - 让该节点成为右子树的左子树

就是让右儿子当爹。这样操作逻辑上相当于让整棵树向左旋转了。
代码实现时，注意要将父节点(如果有的话)的子树(左子树或右子树，要判断一下)改为该节点的右子树(右旋也同理)。

**代码实现**

```cpp
inline treenode* AVLTree::LL_roate(treenode* root)
{
    treenode* s = root->_r;//记录右子树
    
    //调整父节点
    s->_parent = root->_parent;//改变右子树的父节点
    if (root->_parent)    //如果该节点有父节点
    {
        if (root->_parent->_l == root)//判断该节点是父节点的左子树还是右子树
            root->_parent->_l = s;//将父节点的子树改为该节点的右子树
        else
            root->_parent->_r = s;
    }
    root->_parent = s;//将该节点的父节点改为右子树，这个一定要最后调整
    
    //调整子树
    if (s->_l)//如果右子树和有左子树
        s->_l->_parent = root;//就将右子树的左子树父节点改为该节点
    root->_r = s->_l;//将右子树的左子树给该节点的右子树
    s->_l = root;//将右子树的左子树改为该节点
    
    //跟更新树高度
    updata_deepth(root);//必须先更新该节点
    updata_deepth(s);
    
    return s;//返回该树的新的根节点
}
```

#### 右旋 (RR)
![](https://img-blog.csdnimg.cn/img_convert/366576bfdf92e7b8e0a85194768ba88f.gif)
 - 让其左子树代替该节点
 - 并将其左子树的右子树(如果有的话)代替其左子树
 - 让该节点成为左子树的右子树

就是让左儿子当爹。这样的操作在逻辑上相当于将整棵树向右旋转了。

```cpp
inline treenode* AVLTree::RR_roate(treenode* root)
{
    treenode* s = root->_l;//记录左子树
    
    //调整父节点
    s->_parent = root->_parent;//改变左子树的父节点
    if (root->_parent)//如果该节点有父节点
    {
        if (root->_parent->_l == root)//判断该节点是父节点的左子树还是右子树
            root->_parent->_l = s;//将父节点的子树改为该节点的左子树
        else
            root->_parent->_r = s;
    }
    root->_parent = s;//将该节点的父节点改为左子树
    
    //调整子树
    if (s->_r)//如果左子树有右子树
        s->_r->_parent = root;//就将左子树的右子树的父节点改为该节点
    root->_l = s->_r;//将该节点的左子树改为左子树的右子树
    s->_r = root;//将左子树的右子树改为该节点
    
    //更新树高度
    updata_deepth(root);
    updata_deepth(s);
    
    return s;//返回该树新的根节点
}
```

#### 左右旋 (LR)

当失衡是由于左子树的右子树引起时，单纯的右旋不能解决问题。如下图
![在这里插入图片描述](https://img-blog.csdnimg.cn/900160c18d74446ea025a607143bbe02.png)

如果直接进行右旋，结果如下,并没有使二叉树回复平衡。
![在这里插入图片描述](https://img-blog.csdnimg.cn/c9a4cabaf0ea4c57bd4eea2b5196224d.png)

这时，我就就要先对左子树进行左旋操作，让左子树的左子树变为引起失衡的子树，再进行右旋，就可以将二叉树恢复平衡。
![在这里插入图片描述](https://img-blog.csdnimg.cn/fe96fd92bbba4d6686d942506bc56899.png)

**代码实现**

```cpp
inline treenode* AVLTree::LR_roate(treenode* root)
{
    LL_roate(root->_l);//左旋左子树
    return RR_roate(root);//
}
```

#### 右左旋 (RL)

于左右旋同理，就不过多赘述，直接给出代码。

```cpp
inline treenode* AVLTree::RL_roate(treenode* root)
{
    RR_roate(root->_r);
    return LL_roate(root);
}
```

## **功能实现**

### **插入**

插入同搜索二叉树基本相同，但是在每次插入之后要更新树的高度，并且检查树是否失衡，这样就可以在递归回退时找到最小不平衡子树，并且旋转调整他。

**代码实现**
```cpp
inline void AVLTree::insert(int data)
{
    if (!_root)//为空树时，直接赋值改变根节点
    {
        _root = new treenode(data);
        return;
    }
    _insert(_root, data);//不为空就插入
}
inline void AVLTree::_insert(treenode*& root, int data)
{
    //插入
    //按照二叉搜索树进行插入
    if (root->_val < data)
    {
        if (root->_r)
            _insert(root->_r, data);
        else
        {
            root->_r = new treenode(data);
            root->_r->_parent = root;
        }
    }
    else
    {
        if (root->_l)
            _insert(root->_l, data);
        else
        {
            root->_l = new treenode(data);
            root->_l->_parent = root;
        }
    }
    //更新深度
    updata_deepth(root);
    //判断是否失衡
    if (get_balance_factor(root) == -2)
    {
        //LL型，左旋一次
        //右子树的右子树插入导致失衡
        if (get_balance_factor(root->_r) == -1)
            root = LL_roate(root);
        //RL型,先让右子树右旋再让根节点左旋
        //右子树的左子树插入导致失衡
        else if (get_balance_factor(root->_r) == 1)
            root = RL_roate(root);
    }
    else if (get_balance_factor(root) == 2)
    {
        //RR型，右旋一次
        //左子树的左子树插入导致失衡
        if (get_balance_factor(root->_l) == 1)
            root = RR_roate(root);
        //LR型，先让左子树左旋再让根节点右旋
        //左子树的右子树导致失衡
        else if (get_balance_factor(root->_l) == -1)
            root = LR_roate(root);
    }
}
```

### **删除**

对于删除，需要考虑三种情况:
1. 删除节点为叶子节点：直接将删除即可
2. 删除节点有一个子树：将该节点子树替代该节点的位置
3. 删除节点有两个子树：用中序遍历的前驱或后继代替该节点位置，用递归将该种情况转化为前两种情况(细节见代码)

#### **前驱和后继**

删除有两个子树的节点时，让左子树的最大值(前驱)或是右子树的最小值(后继)替代该节点位置，依然满足搜索二叉树。
实现时，将该节点的值直接改为前驱(后继)，然后要删除节点就变为前驱(后继)，再递归找到前驱(后继)，最后都会转化成前两种情况。

**寻找前驱代码的实现(后继类似)**

```cpp
inline treenode* AVLTree::get_lmax(treenode* lroot)
{
    while (lroot->_r)
        lroot = lroot->_r;
    return lroot;
}
```

**代码实现**
```cpp
inline void AVLTree::erase(int data)
{
    if (!_root)//空树不能进行删除
        return;
    _root = _erase(_root, data);
}
inline treenode* AVLTree::_erase(treenode* root, int data)
{
    //1.删除节点
    if (root->_val < data)
        if (root->_r)
            _erase(root->_r, data);
        else if (root->_val > data)
            if (root->_l)
                _erase(root->_l, data);
            else
            {
                //删除有三种情况
                //1.删除节点为叶子节点 
                //直接删除
                if (!root->_l && !root->_r)
                {
                    if (root->_parent)
                    {
                        if (root->_parent->_l == root)
                            root->_parent->_l = nullptr;
                        else
                            root->_parent->_r = nullptr;
                    }
                    delete root;
                    root = nullptr;
                }
                //2.删除节点有一个子树
                //将该子树代替掉删除节点的位置
                else if (!root->_l || !root->_r)
                {
                    if (root->_parent)
                    {
                        if (root->_parent->_l == root)
                            root->_parent->_l = root->_l ? root->_l : root->_r;
                        else
                            root->_parent->_r = root->_l ? root->_l : root->_r;
                    }
                    treenode* s = root->_l ? root->_l : root->_r;
                    s->_parent = root->_parent;
                    delete root;
                    root = s;
                }
                // 3.删除节点有两个子树
                //用中序遍历的前驱或后继代替该节点
                else
                {
                    treenode* lmax = get_lmax(root->_l);
                    root->_val = lmax->_val;
                    _erase(root->_l, lmax->_val);
                }
            }
    //2.调整高度
    updata_deepth(root);
    //3.调整最小不平衡子树
    if (get_balance_factor(root) == 2)
    {
        if (get_balance_factor(root->_l) == 1)
            root = RR_roate(root);
        else
            root = LR_roate(root);
    }
    else if (get_balance_factor(root) == -2)
    {
        if (get_balance_factor(root) == -1)
            root = LL_roate(root);
        else
            root = RL_roate(root);
    }
    return root;
}
```

### **查找**

很简单，这里只给出代码
```cpp
inline treenode* AVLTree::find(int data)
{
    if (!_root)
        return nullptr;
    return _find(_root, data);
}
inline treenode* AVLTree::_find(treenode* root, int data)
{
    if (!root)
        return nullptr;
    if (data < root->_val)
        return _find(root->_l, data);
    else if (data > root->_val)
        return _find(root->_r, data);
    else
        return root;
}
```

## 总结
平衡二叉树旋转时，交换的变量很多，要时刻记着哪些变量已经交换，哪些还没有，实现时要仔细不然很容易出现问题。

