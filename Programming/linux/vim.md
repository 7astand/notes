# vi/vim

- 普通用户编辑只读文件

    使用 vim 编辑完一个文件后,运行 `:wq` 保存退出,会出现一个错误:
    提示文件是只读的,提示 加上 `!` 强制保存,发现还不行
    vim 在非管理员身份打开并编辑文件后,保存后会提示 "Can't open file for writing Press ENTER or type command to continue"
    这个文件需要 root 权限才能够编辑,而当前编辑该文件的只是个普通用户,解决办法是在编辑文件前记得使用 `sudo` 命令来启动 vim 编辑文件
    如果忘了在启动时使用 root 权限或者没有使用 `sudo` 启动并且已经编辑了很多内容,这时并不想让修改撤销丢失,这时要把它保存文另外的一个临时文件,再推出 vim ,再用 mv 命令去覆盖原文件
    这样的解决方案有些麻烦!有更好的方法来解决问题,再不退出 vim 的情况获得 root 权限保存这个文件
    执行一条命令
    > :w !sudo tee %

    分析一下上面的一条命令 查看文档 `:help :w`
    > :       w               !sudo tee %
    > |       |               |  |
    > :[range]w[rite] [++opt] !{cmd}

    这个命令中没有指定 `range` ,看文档后,未指定 `range` 时,默认是整个文件

    **vim执行外部命令**

    下边是一个 `!` ,表示后边的是外部命令,即 `sudo tee %` 文档中说这个和直接执行 `:!{cmd}` 是一个效果. 作用是打开 shell 执行一个命令,如运行 `:!ls` ,会显示当前工作目录下的所有文件,任何在 shell 中执行的命令都可以在不退出 vim 的状态下执行,并且可以将结果读入 vim 中.如果你要在Vim中插入当前工作路径或者当前工作路径下的所有文件名，你可以运行:
    > :r !pwd或:r !ls

    实际上这个 `:w` 并未真的保存当前文件，就像执行 `:w new-file-name` 时，它将当前文件的内容保存到另外一个 `new-file-name` 的文件中，在这里它相当于一个另存为，而不是保存。它将当前文档的内容写到后面 cmd 的标准输入中，再来执行 cmd ，所以整个命令可以转换为一个具有相同功能的普通 shell 命令：
    > $ cat readonly-file-name | sudo tee %

    这样看起来”正常”些了。其中 `sudo` 很好理解，意为切换至root执行后面的命令，`tee` 和 `%` 是什么呢?

    **%的意义**

    我们先来看 `%` ，执行 `:help cmdline-special` 可以看到文档解释
    在执行外部命令时，`%` 会扩展成当前文件名，所以上述的 cmd 也就成了 `sudo tee readonly-file-name` .此时整个命令即:
    > $ cat readonly-file-name | sudo tee readonly-file-name

    **注意：**在另外一个地方我们也经常用到 `%` ，没错，替换。但是那里 `%` 的作用不一样，执行 `:help :%` 查看文档:
    在替换中，`%` 的意义是代表整个文件，而不是文件名。所以对于命令 `:%s/old/new/g` ，它表示的是替换整篇文档中的 old 为 new ，而不是把文件名中的 old 换成 new .

    **tee**的作用

    参考[tee wiki](https://en.wikipedia.org/wiki/Tee_%28command%29 "tee wiki")
    tee将其标准输入中的内容写到了 readonly-file-name 中，从而达到了更新只读文件的目的。当然这里其实还有另外一半数据：`tee`的标准输出，但因为后面没有跟其它的命令，所以这份输出相当于被抛弃。当然也可以在后面补上 `> /dev/null` ，以显式的丢弃标准输出，但是这对整个操作没有影响，而且会增加输入的字符数，因此只需上述命令即可。
    **命令执行后**
    Vim 提示文件更新，询问是确认还是重新加载文件。建议直接输入O，因为这样可以保留 Vim 的工作状态，比如编辑历史， buffer 等，撤消等操作仍然可以继续。而如果选择L，文件会以全新的文件打开，所有的工作状态便丢失了，此时无法执行撤消， buffer 中的内容也被清空。
    **此文档大量参考 [blog](https://feihu.me/blog/2014/vim-write-read-only-file/ "vim write readonly file") **
