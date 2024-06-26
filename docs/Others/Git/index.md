
## **拉取远端**

```bash
git log 
```

## **版本回退**

```bash
git reset [--soft | --mixed | --hard] [HEAD]
```

- --mixed 为默认选项，使⽤时可以不⽤带该参数。该参数将暂存区的内容退回为指定提交版本内容，⼯作区⽂件保持不变。

- --soft 参数对于⼯作区和暂存区的内容都不变，只是将版本库回退到某个指定版本。

- --hard 参数将暂存区与⼯作区都退回到指定版本。切记⼯作区有未提交的代码时不要⽤这个命令，因为⼯作区会回滚，你没有提交的代码就再也找不回了，所以使⽤该参数前⼀定要慎重。

HEAD 说明：

可直接写成 commit id，表示指定退回的版本

- HEAD 表示当前版本

- HEAD^ 上⼀个版本

- HEAD^^ 上上⼀个版本

也可以使⽤ ~数字 表示：

- HEAD~0 表示当前版本

- HEAD~1 上⼀个版本

- HEAD~2 上上⼀个版本


## **commit 日志**

显示 commit 的记录：

```bash
git log [<options>] [<revision-range>] [[--] <path>…​]
```

使用 --graph 可以更美观的显示提交记录。