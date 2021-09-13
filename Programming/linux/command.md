# command

- ls
  查看当前文件列表, `-a` 参数可以查看隐藏文件

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
