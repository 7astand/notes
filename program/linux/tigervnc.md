# tigervnc

[fedora tigervnc 配置远程桌面]:(https://access.redhat.com/documentation/zh-cn/red_hat_enterprise_linux/8/html/using_the_desktop_environment_in_rhel_8/accessing-the-desktop-remotely_using-the-desktop-environment-in-rhel-8)

## fedora 配置远程桌面

[fedora tigervnc 配置远程桌面]

### 先决条件

之前使用过 `systemd` 配置过 vnc ,需要删除之前配置的 vnc

### 流程

- 安装 vnc 服务器

    ```shell
    yum install tigervnc-server
    ```

- 映射用户显示的端口号
在 `etc/tigervnc/vncserver.users` 配置文件中,为每个要导出 vnc 会话的服务器用户添加 `:user_number=user_name`
使用端口替换 user_number,并显示映射到所选现有用户的号码
使用所选现有用户的用户名替换 user_name
例如:

    ```shell
    :1=michael
    ```

- 在防火墙打开 TCP 端口 5900 到 5903

    ```shell
    firewall-cmd --permanent --add-service=vnc-server
    ```

- 重载防火墙规则

    ```shell
    firewall-cmd --reload
    ```

- 在 `etc/tigervnc/vncserver-config-defaults` 配置文件中添加配置

    ```shell
    session=gnome
    alwaysshared
    ```

    `session=gnome` 远程用户登录时启用 gnome 会话
    `alwaysshared` 多个用户可以同时连接到 vnc 服务器

- 为 vnc 用户设置 VNC 密码

    ```shell
    vncpasswd
    ```

- 启用并启动 vnc 服务

    ```shell
    systemctl enable --now vncserver@:user_number
    systemctl start vncserver@:user_number
    ```
