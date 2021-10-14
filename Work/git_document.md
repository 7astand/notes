# git

- git clone <https://gitee.com/xlastand/synchronization-note.git> 从远程仓库clone

## git config

git 配置

- 设置用户名和邮箱
`git config --global user.name "xxx"`
`git config --global user.email "xxx@XX.com"`
- 设置代理
  - global 设置全局代理
  `git config --global https.proxy https://127.0.0.1:7890`
  `git config --global http.proxy http://127.0.0.1:7890`
  - 取消代理
  `git config --global --unset https.proxy`
  `git config --global --unset http.proxy`
  - 查看全局配置信息
  `git config --global -l`
- 查看已关联分支信息
`git branch -vv`
`git remote show origin`
`cat .git/config`
- 查看远程版本库分支列表
`git branch -r`
- git push 推送远程仓库
`git push <远程主机名> <本地分支名>:<远程分支名>`
`git push origin master` 如果远程分支被省略,则表示将本地分支推送到与它存在追踪关系的远程分支 (通常同名) ,如果该远程分支不存在,则会被新建
`git push origin :master` 如果省略了本地分支名,则表示要删除远程分支,这样等同于推送了一个空的本地分支到远程分支,等同于 `git push origin --delete master`
`git push origin` 如果当前分支和远程的分支存在追踪关系,则本地分支和远程分支都可以省略,将当前分支推送到 origin 主机的对应追踪分支
`git push` 如果当前分支只有一个远程分支,那么主机名都可以省略
`git push -u origin master` 如果当前分支与多个主机存在追踪关系,则可以使用 -u 参数来指定一个默认主机,这样后边可以不加任何参数使用 `git push`
- git rebase
  总的原则是,只对尚未推送或者没有分享给别人的本地修改执行变基操作清理历史
  从不对已推送到别处的代码执行变基操作
  将当前分支变基到目标基底分支.接在目标基底分支后面
`git rebase <目标基底分支>`
  rebase 过程中出现冲突后 解决完冲突后 用 `git add` 命令告诉 git 冲突已解决
  再使用 `git rebase --continue`
  - 将目标分支变基到基分支上
  `git rebase <basebranch> <topicbranch>`
  - 将本地未推送到远程的多次提交合并成一个提交
  `git rebase -i HEAD~4` 命令后
  会进入 vi 模式
  如果因异常退出了vi 窗口 使用 `git rebase --edit-todo`
  修改完保存后 使用 `git rebase --continue`
  想要取消这次 rebase 使用 `git rebase --abort`
- git reset
  `git pull` 后想要回退版本
使用 `git reflog`
  查看一下git的 log,这个命令查看的是最近对`HEAD`指针有变化的操作记录
  找到想要回退到的那一次commit
  `git reset --hard HEAD@{n}`
- 在指定远程分支创建同名分支并切换过去
`git checkout -t origin/feature`
- 删除本地分支
  分支中有一些未 merge 的提交会删除失败,把 -d 换成 -D 可以强制删除分支
  `git branch -d` 分支名
- 给分支重命名
`git branch -m oldname newname`
- 解决冲突后需要使用 `git add` 告诉 git 冲突已解决
- merge 合并其他分支
  将 othername 分支合并到当前分支上
  `git merge othername`
- git 本地仓库关联多个远程仓库
  - 查看远程关联仓库
  `git remote -v`
  - 关联添加另一个远程仓库
  name 就像当与默认的 origin
  `git remote add name <url>`
  `git remote -v` 再次查看关联的远程仓库已经关联了两个不同地址的远程仓库
  `git push` 和 `git pull` 需要指定远程仓库名字了
  `git push origin feature:feature`
  `git push name feature:master`
  - 另一种方法(未尝试)
  `git remote -v`
  不添加新的远程仓库,而是给现在已有的远程仓库添加额外的url
  给已有的名为 name 的远程仓库 添加新的 url
  `git remote set-url --add <name> <url>`
  `git remote set-url --add origin 新的url`
- 删除暂存区和工作区的文件
`git rm filename`
  只删除暂存区的文件，不会删除工作区的文件
  可以用来更改文件名大小写
`git rm --cached filename`
  更改工作区或者暂存区的名字
`git mv oldname newname`

## git 撤销操作

git revert 撤销一次提交 A (commit) 生成一个新的 提交 B (commit) 将提交 A 的变动撤销
`git revert < commitr-harsh>`
