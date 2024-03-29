# command

- ls 命令

    通过 `man` 命令查看 ls 会发现它是 `ls --color=auto` 的别名
    `ls` 命令默认查看当前路径的文件信息。

  - 参数

    ```shell
    ls -a
    ```

    查看当前的隐藏文件列表，linux 中隐藏文件一般默认都是以 `.` 开头的，linux 中一切皆文件

    ```shell
    ls -l
    ```

    查看文件的具体信息。以列表形式展示出
    会展示出 文件的类型和不同用户，用户组对该文件的权限（文件所有者，文件所属组，其他用户），文件内包含其他文件的数目，该文件的所有者，该文件所属用户组，该文件的大小，文件的最后访问时间，文件名

    `ls -l` 以列表形式查看文件的详细信息可以添加别的参数

    ```shell
    ls -lr
    ls -lt
    ls -lR
    ls -lrtR
    ```
    
    `r` 参数是反转查看，也就是倒序查看。
    `t` 参数是以时间的顺序查看。
    `R` 参数是递归查看，将目录下的所有文件递归查看
    
- cd 命令

  cd 命令更改当前工作目录

  - 参数

    ```shell
    cd path
    ```
    
    cd 后跟路径信息，会更改当前工作目录为所给的 path 的目录

    ```shell
    cd -
    ```

    会进入更改前的工作目录

- mkdir 命令

  创建文件夹
  *不能创建重复目录*

  - 参数

    ```shell
    mkdir -p a/b/c/d
    ```

    创建多级目录

  删除空文件夹使用 `rmdir` 命令,*该命令只能删除空目录*
  删除多级目录使用 `rm -rf /a` 
  

- lsof -i

- useradd
  添加用户
  `-m` 自动创建用户的家目录,并将 `/etc/skel` 文件复制到家目录中
  `-s` 指定用户登录后的shell

  ```shell
  useradd -m -s /bin/bash newname
  ```

  对新建的用户设置密码

  ```shell
  passwd newname
  ```

  `-d` 目录 指定用户主目录，如果此目录不存在，则同时使用-m选项，可以创建主目录

  ```shell
  useradd –d  /home/sam -m sam
  ```

- 使用权限执行上次的命令
  一般用在敲了很长命令但是没有使用 sudo 权限
  
  ```shell
  sudo !!
  ```

- find

  查找
  find path -iname "expression"
  * path

    表示路径
  * iname 

    表示查找 expression 的名字，i 表示不区分大小写
    expression 可以包含正则表达式