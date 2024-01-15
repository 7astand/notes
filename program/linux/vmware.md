# vmware

## vmware fusion

    使用 fusion 来进行安装 fedora 36 前两项都不能安装，使用了三项 trouble 方案，似乎是启动了一个基本图形模式，启动成功了，我没尽兴分区，使用了默认的分区操作

    进入之后重启 linux 之后，会进入到设置界面，设置用户信息，用户名和密码
    设置完成后我使用本机的 vscode 连接 虚拟机里的 linux 
    首先需要先开启 sshd 服务
    `sudo systemctl start sshd`
    开启 ssh 服务
    同命令 stop 关闭服务
    `sudo systemctl enable sshd`
    开启开机自启 sshd 服务
    同命令 disable 关闭自启服务

    开启ssh服务后，本机使用vscode ssh 连接虚拟机的linux
    提供 ip 地址
    `ssh-copy-id -i ~/.ssh/id.pub username@ipaddress`
    随后输入需要连接的 linux 服务器的 密码
    会将指定的密钥 copy 到远程linux 服务器的 ~/.ssh/authorized_keys 文件内
    前提是目标服务器/远程服务器 的 /etc/ssh/sshd_config 中有如下配置项 AutnorizedKeysFile ~/.ssh/authorized_keys 

    之后使用 ssh 连接 linux 成功后就会自动在 linux 上下载并安装 vscode server 服务，之后可以使用 vscode 连接远程 linux 了。
    还可配置本机的 ssh config 使用 host 代替指定的 ip 地址，参考 git 配置 ssh 的章节