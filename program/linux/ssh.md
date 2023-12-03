# ssh

- 参数

`-p` 指定端口号

`ssh name@ip -p port`

`-N` 只连接不打开shell

`-f` 后台运行，只能通过 `kill` 杀掉进程来结束

`-T` 部分配 tty

- 本地端口转发

ssh -L 本地端口号:目标ip:端口 中转ssh服务器

目标ip是相对于 中转ssh服务器的ip地址

`ssh -L 5999:localhost:5902 name@ssh服务器ip -p 端口号`