# shell

- 用户配置读取顺序

    /etc/profile
    .bashprofile
    .bashrc
    /etc/bashrc

    每次切换用户后，会读取用户配置
    使用 su - user1 切换时会全部从头读取一遍; loginshell 切换用户后会进入到该用户的home目录
    使用 su user1 切换用户时，只会读取后两个; nologinshell 切换用户后当前目录不变
    可以在任意一个配置文件内增加PATH 环境变量
    export PATH=$PATH:/home/path
    这样会将PATH 环境变量导出到用户shell和用户的子shell的环境中去
    修改完不会立即生效，有两种方式
    1. 退出用户，终端再登陆
    2. source /etc/bashrc source + 修改的配置文件路径
    