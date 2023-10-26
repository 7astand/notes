# tcpip

客户端a
服务端b
初始化
aclose
b进入listen
a发送syn 进入 synsent
b收到a的syn 进入synrecvd 发送syn和ack
a收到b的 ack syn 进入establish
a发送b syn的ack 还是establish
b收到a的ack 进入establish

a发送fin 进入finwait
b收到fin 进入closewait
b发送ack 发送 fin
a收到 ack 进入 finwait2
a收到 fin 进入timewait
a发送ack
b收到ack 进入close

timewait 存在意义
timewait停留2msl 一般为2min
确保tcp关闭
保证没有迟来的数据被错误使用
a停留在timewait能收到b的关闭fin请求并重新发送 ack


小结
这个例子a端会进入timewait
哪端先发送fin结束哪端进入timewait
服务器端不要主动结束连接，服务端太多timewait会有太多端口被占用情况出现

rst 复位标志

socket 中solenger 会发送rst 
发送完rst后所有待发送数据会丢弃
半关闭状态关闭端收到数据也会发送rst

tcp 交互数据
telent 用到实时性
客户端比较慢 一个字符一个tcp数据报
ls
l 一个tcp
s换行回车 一个tcp
服务端快 一般等有数据发送时才将数据和ack一起发送出去

tcp 成块数据
ftp用到 文件传输

服务器
一次连续发送多个tcp数据报
根据syn时客户端窗口来决定的
客户端
收到多个tcp后发送一个ack

tcp 带外数据
比较紧急的数据

tcp头部有个urg标志和指针
标识最后一个紧急数据的下一个子节
紧急数据一般是1子节
客户端没有及时从紧急数据缓存区取走数据时，有可能会发生覆盖掉紧急数据的情况

tcp超时重传
linux 有参数控制
重传一般3～5次
超时一般 13～20min
/proc/sys/net/ip4/...

超过3～5次没有ack时，
每次重传比上次时间翻倍 0.2s 0.4s
会被ip arp 协议接管
会广播查找目的的新mac地址

tcp 拥塞控制

rwnd 接受窗口大小 reveive window 
cwnd 拥塞窗口
swnd 发送窗口

swnd 由 rwnd 和cwnd 决定 一般是min小的那个

慢启动 拥塞避免congestion avoid 快速重传 快速恢复

慢启动，指数级增长
拥塞避免，保证平稳增长

连续收到3个超时ack时，任务已经拥塞
进入快速重传和快速恢复
恢复正常进入拥塞避免


# pipe函数

int pipe(int fd[2])

fd[0] 读端口
fd[1] 写端口

使用了引用计数

引用计数为0时
读端 读到 0 endoffile eof
写端 写时 引发sigpipe错误信号

dup 和 dup2
dup会使用当前系统可用的最小的一个文件描述符
dup(b)
b会使用当前系统可用的最小的一个文件描述符

cgi原理

close(stdout_fileno)
dup(socketfd)
这样输出到标准输出上的内容会直接发送到socketfd上