# git

- git clone <https://gitee.com/xlastand/synchronization-note.git> 从远程仓库clone

## git config

git 配置

```shell
# 设置用户名和邮箱
git config --global user.name "xxx"
git config --global user.email "xxx@XX.com"
# 设置代理
# global 设置全局代理
git config --global https.proxy https://127.0.0.1:7890
git config --global http.proxy http://127.0.0.1:7890
# 取消代理
git config --global --unset https.proxy
git config --global --unset http.proxy
# 查看全局配置信息
git config --global -l
# 查看已关联分支信息
git branch -vv
git remote show origin
cat .git/config
# git push
git push <远程主机名> <本地分支名>:<远程分支名>
git push origin master
# git rebase
git rebase <目标分支>
# 将当前分支变基到目标分支.接在目标分支后面

# git reset
# git pull 后想要回退版本
git reflog 
# 查看一下git log
# 找到想要回退到的那一次commit
git reset --hard HEAD@{n}
```
