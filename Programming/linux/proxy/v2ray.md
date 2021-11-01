# v2ray

[Project V 项目官网]: <https://www.v2fly.org/> "Project V 项目官网"
[v2ray 官方配置文档]: <https://guide.v2fly.org/> "v2ray 官方配置文档"
[v2ray 官方安装脚本]: <https://github.com/v2fly/fhs-install-v2ray> "v2ray 官方安装脚本"
[v2ray github 仓库]: <https://github.com/v2fly> "v2ray github 仓库"
[v2ray core github 仓库]: <https://github.com/v2fly/v2ray-core> "v2ray core github 仓库"

[v2rayN github 仓库]: <https://github.com/2dust/v2rayN> "v2rayN github 仓库"

## 参考资料

[Project V 项目官网]
[v2ray 官方配置文档]
[v2ray 官方安装脚本]
[v2ray github 仓库]
[v2ray core github 仓库]

[v2rayN github 仓库]

## 配置

参考的[v2ray 官方配置文档],自己尝试了一遍,已经在 ubuntu20.04 LTS 实验成功!

- 安装
  校验时间,服务器时间和本地客户端时间要去相差不能超过90s
  - 安装依赖
    需要安装 curl
    debian/ubuntu:
    `$ apt install curl`
    fedora:
    `$ dnf install curl`
  - 下载安装脚本
    `$ curl -O https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh`
    **注意**
    这一步有可能因为网络问题导致下载不成功或者下载特别慢,后续脚本中还需要在 [v2ray core github 仓库] 上下载 v2raycore 内核文件,选择 linux 版本文件 v2ray-linux-64.zip
    `$ bash install-release.sh -h` 查看脚本的安装帮助文档
    发现该脚本支持本地安装,因此我们把安装脚本文件和 v2ray 内核都在网络通畅处提前下载好,然后使用 ftp sftp scp 等工具传到要安装的机器上,推荐使用 filezilla 客户端可以图形化操作
    上传完成后,使用命令:
    `$ bash install-release.sh -l ./v2ray-linux-64.zip`
    使用本地安装,指定 v2ray core 文件进行本地安装
- 运行
  安装完成后,使用以下命令启动 v2ray
  `$ systemctl start v2ray`
  使用以下命令让 v2ray 开机自启
  `$ systemctl enable v2ray`
  查看一下 v2ray 的运行状态,看看是否真正启动成功
  `$ systemctl status v2ray`
  看输出的信息中的 active: 项是否是 running 状态,running 状态说明启动成功
  这时的 v2ray 还未配置完成,因此选择先暂时关闭 v2ray, 使用以下命令
  `$ systemctl stop v2ray`
- 配置文件
  这里已经安装完成了软件,现在需要配置 config.json 文件
  这个文件是本地与远程服务器通信的配置文件,约定了一些 协议, ip, 端口等信息
  config.json 配置文件我安装的版本默认安装在 /usr/local/etc/v2ray/config.json
  v2ray 程序默认安装在了 /usr/local/bin/v2ray
  v2ray 日志默认在 /var/log/v2ray/
  这个信息在使用脚本安装时会输出在 terminal
  config.json 配置文件我是通过订阅链接,然后通过 windows 下的 v2rayN 导出的配置文件,导出的单个节点的信息,导出的文件命名为 config.json
  使用 v2ray 官方提供的校验方式,校验一下文件的格式内容信息是否正确,使用以下命令
  `$ /usr/local/bin/v2ray -test -config /usr/local/etc/v2ray/config.json`
  配置没问题,就使用命令运行 v2ray 就 OK 了
- 配置浏览器代理
  需要手动为浏览器设置代理,v2ray 在本地使用的是 socks 协议
  在 socks host 中填写 127.0.0.1 端口号填写 1080 再勾选使用 socks 时代理 DNS
  这里 的 127.0.0.1 是本地地址,端口号需要从 自己的 config.json 文件中查看,一般默认是 1080

## v2rayN

  v2rayN 是 windows 下的一个有界面的 v2ray 软件,它的 github 仓库地址是 [v2rayN github 仓库]
  查看 REAMME.md 文件,首次安装的话,需要下载带 v2ray Core 的版本 v2rayM-Core.zip
  下载完成后解压,运行 v2rayN.exe
