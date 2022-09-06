# iptables

网络防火墙管理
和 firewall-cmd 是同一套，firewall-cmd 会转换为iptables，底部都是netfilter

## 查看规则

    iptables -nvL
    n 不使用域名反查
    v 显示详细信息
    L 查看列表

## 增删规则

    iptables -t filter -A INPUT -s 10.10.10.2 -j DROP
    -t 选择表，默认时filter表
    -A 将规则追加到最后
    INPUT 是分类，添加到哪个类，可选 OUTPUT，FORWARD
    -s 源地址
    -j 规则，可选DROP ACCEPT REJECT 等
    -d 目的地址

    -A 规则添加到最后一项
    -I 规则插入到第一项 还可以指定位置，
    -R 修改某一项的规则 比如修改 INPUT 下的第几条，先使用 -nL --line-number查看条数目
    -D 删除某一条规则 可以先查看规则条数目
    -P 修改默认策略 policy
    这些命令后一般跟 规则类型 INPUT FORWARD DROP

    -s 来源地址
    -d 目的地址
    -p 协议
    -i 进站网卡接口
    -o 出站往卡接口
    --dport 目标端口
    --sport 来源端口
    -j 动作，ACCEPT REJECT DROP 这些