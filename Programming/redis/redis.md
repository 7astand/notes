# redis

- 数据结构

底层数据结构
5 种

双向链表
O(N)
不过双向链表记录了大小和偏移，向链表中首尾增删数据很快

整数数组
O(N)

哈希表
hash复杂度 O(1)
使用哈希表
哈希桶
存放对象 内容是 下一个对象指针，key指针，value指针

rehash
会在下一次redis对数据进行操作时copy那一个篮子的数据，防止大量数据copy卡顿

跳表
Olog(N)
增加了索引
一级索引
二级索引
索引使用了区间搜索增加搜索速度

压缩表
首尾字段记录了列表的长度
首
大小，每项的偏移，起始位置
尾
结束位置
首尾增删数据很快

- AOF RDB

  AOF 
  将redis每一次的数据操作记录下来
  redis先执行命令后写AOF
  这样AOF中的命令都是正确的
  set key value
  *3
  命令分为3个部分
  set
  key
  value

  三种策略
  always 总是写，实时的写AOF 可靠性最高
  everyses 每秒写日志 性能和可靠性之间的平衡
  no 系统决定何时写AOF日志 性能最高

  AOF重写
  AOF重写是讲重写时的内存fork出来，拱写日志线程读。
  重写后日志记录就会很少。因为很多是对同一个数据结构进行操作的
  重写后只会记录最终的结果，精简了AOF日志的记录

  一个拷贝两个日志
  redis重写AOF日志时，此时有写操作时，会将写操作同时写入两个地方
  一个是当前的AOF日志中，一个是新的AOF日志中，新的AOF日志就是重写线程
  正在重写的那份AOF日志。
  这样保证高可靠性。重写日志完成后，重写日志时的
  主线程redis的这些写操作也会写入新的AOF文件中

  RDB

  内存快照

  对内存的数据做全量快照，保证可靠性

  做快照时数据还能进行修改吗

  可以
  使用写时复制技术
  copy-On-write cow
  
  做内存快照会有一个子线程
  当redis主线程有数据需要写时，
  子线程会对要写修改的那份数据做个副本，主redis线程依然可以写成功
  子线程做的快照是写之前的那份数据

  可以频繁的做快照吗
  不可以
  内存，磁盘压力会比较大
  一直fork子线程内存压力大，频繁快照的话磁盘写压力也很大

  做一次快照后需要记录哪些信息被修改了。
  这种方式需要有元数据记录哪些数据被修改了
  磁盘开销比较大，元数据也要占磁盘数据

  解决方案是使用混合AOF方式
  做一次快照后，数据的变更使用AOF日志来记录
  这样就避免重写开销

- 主从库模式

  数据同步
  主数据库 处理读写
  从数据库 只处理读

  数据写到 主 主同步给从
  读写分离
  原因
  主 从 库都有可能同时被写数据，导致数据不一致
  如果非要这样做的话 加锁，协商开销大

  主从同步
  redis 5.0 之后
  使用 replicaof 
  之前使用 slaveof

  主 ip A
  从 ip B
  port 表示端口 6379
  从
  执行 replicaof A port

  从 发送 psync ？ -1 数据给主
  主 回复 +FUULRESYNC{runID}{offset}
  主 发送 RDB 二进制文件给 从 清空现有数据，使用RDB恢复 从
  主 发送 repl buffer 从 加载 repl buffer

  解释
  psync 和 主握手 建立连接
  runID 表示 主 运行的 id 从 第一次不知道 所以用 ?
  offset -1 表示 第一次复制
  FUULRESYNC 第一次响应时全量复制
  主 做完RDB 后还有写值操作，被记录到 repl buffer 中
  发送给 从 从执行后更新为和 主 相同状态

  主 从 从 模式

  从 A 执行 replicaof 从B port

  可以在 从 中选一个 和其他的 从 进行数据交互同步
  主 RDB 发送给一个 从A
  从A 选一个 从B 负责和 这个 从B 进行数据同步，分担 主 压力

  长连接命令模式

  网络断后

  repl buffer 起作用
  网络断后 会进行增量复制
  
  主 从 断连后 主在此期间的操作写入 repl buffer 同时会写入 repl_backlog_buffer 缓冲区中一份
  是 环形的
  主 记录自己写的位置 从 记录读的位置
  恢复连接后 
  从 发送 psync 给 主 把 从 当前的 slave_repl_offset 发送给 主
  主 判断 master_repl_offset 和 slave_repl_offset 之间的差距
  把之间差的部分 发送给 从 就可以

  风险
  有可能主 写的太快 从 复制的太慢被覆盖

  调整 repl_blacklog_size 大小
  缓冲区 = 主 写速度 * 数据大小 - 从 命令传输速度 * 数据大小
  一般是缓冲区 2倍

- 哨兵机制

  主 挂了 客户端往哪里写

  哨兵 
  监控 判断主 下线
  选主 通过机制选出新 主
  通知 从 执行 replicaof 与新主建立连接 通知客户端与新主连接

  主观下线
  哨兵自己 ping 主 得到结果判断
  检测到从ping 不到 直接标记主观下线
  客观下线
  误判
  通常使用 哨兵集群
  多数判断下线 才会 标记 客观下线
  一般最少 3台 哨兵 2台同意才行
  总数/2 +1 

  筛选主
  下线的从 筛选掉
  复制进度最快 选用 通过 repl_backlog_offset 判断

  判断网络连接状况
  有个值 从库连接 主 超过这个值 的次数多了也会被筛选掉

  id号小的当选

- 哨兵集群


  基于pub/sub 订阅发布机制 组建哨兵集群
  基于 INFO 命令获取 从库列表 哨兵 和从库建立连接
  给予 pub/sub 哨兵和客户端连接

  配置哨兵
  需要 主 ip 端口

  各哨兵 配置要相同
  sentinel monitor mastername ip port quorum

  哨兵订阅redis 同一频道进行通信
  __sentinel__:hello

  哨兵A
  A 发布自己 ip
  BC 收到Aip 
  BC 和 A 连接
  互相连接

  向主 发送 INFO 返回 slave列表
  建立连接

  客户端 哨兵
  事件通知
  客户端向哨兵订阅消息
  消息有很多种状态
  主库下线
  从库重新配置
  新主库切换

  哨兵选主 leader 决定切换 主 库
  
  主库下线投票 
  投 y 也向其他哨兵发布 自己要做leader的信息

  投 n 的 哨兵 根据收到信息的先后来决定
  先收到了A的leader会先同意 A，
  投过 y 的leader哨兵对于之后的leader 信息都会投 n

- 切片集群

  redis 需要扩展时
  横向扩展 增加机器的数量，使用多个实例
  纵向扩展 增加本台机器的配置

  横向扩展
  扩展后会使用 CRC16 算法 对key取hash值
  分为16384个插槽，平均分布在N个实例上
  也可以根据实例的配置水平自行分配每个实例上的插槽数量，但要保证插槽全部被分配

  自行分配插槽
  redis-cli -h ip -p port cluster addslots 0,1

  客户端定位插槽位置

  首先客户端也会根据crc16算法算key的插槽值
  redis实例会把自己的插槽信息发给其他实例
  客户连接redis客户端时，实例会把插槽信息发送给客户端
  客户端会存储在本地一份缓存

  redis上插槽改变时
  集群新增或删除 插槽改变
  负载均衡时 重新分布一遍插槽

  redis cluster 重定向机制
  客户端从缓存中查找到key的一个插槽对应的redis实例
  发送请求
  该实例上并没有对应的插槽
  返回给客户端 MOVED 命令
  告诉客户端请求的插槽在 新实例 ip 为xx
  客户端收到信息后回更新本地缓存信息

  另一种情况
  客户端在请求时，实例中的插槽正在迁移
  但数据没有迁移完全
  客户端向实例发送请求后会得到 ask 命令
  ask 命令把客户端请求的最新数据在哪个实例上发送给客户端
  客户端需要向最新的实例发送ASKING 命令，然后再发送操作指令
  ask 命令不会更改客户端的本地缓存
  只会让客户端能给新实例发送一次请求获得最新数据

- string 引发的大数据存储问题

  string存储数据时需要的字节数目很大
  string 数据结构
  string 使用 SDS 简单动态字符串 来保存
  simple dynamic string
  SDS
  len 4字节 表示buf的已用长度
  alloc 4字节 表示字符串的实际分配长度
  buf 保存实际数据，最后一子节是 '\0' 表示字节数组结束，导致比正常大小要多 1字节

  还有一个 redisobject 开销
  表示最近一次访问时间，被引用次数
  包含 
  元数据 8子节
  ptr 8子节
  ptr 指针一般只想SDS的地址
  对 数值做了优化 如果数值是 long 型整数会直接在ptr存这个数值
  保存的是 字符串时
  字符串大小小于44子节 
  元数据 ptr sds 在内存中是连续空间，避免碎片
  字符串大小大于44子节 
  ptr 指向 SDS 内存空间

  redis 会使用一个全局哈希表保存所有的键值对 
  每一项是 dictentry结构体，指向一个键值对
  dictentry结构体 
  key 8子节 
  vale 8子节
  next 8子节
  使用jemalloc 分配内存
  根据要用的字节数 N 使用比N大最接近 N的2次幂的值分配内存
  24 --> 32

  压缩列表

  数据部分
  prevlen 前一个entry长度 1-254 占1子节，否则占 5子节
  压缩列表中 zlen 结束位置 默认取值为 255 所以这里最大值是254
  encoding 编码方式 1子节
  len 自身长度 4子节
  key 数据

  hash-max-ziplist-entries 最大元素个数
  hash-max-ziplist-value 单元素最大长度


- 大数量 keys 存储

  聚合统计
  统计每天登陆的id数，求每天新增的用户
  用set
  每天的登陆用户放入当天的set中
  计算新增
  两天的取并集
  
  计算留存
  两天取交集

  排序统计

  商品的评论
  按时间分页统计
  使用 sortset 有序集合
  给定一个排序因子作为该项的权重，按照权重排序

  二值状态统计

  使用bitmap
  只保存了两种状态 0 和1
  统计连续登陆的人数
  每天的登陆状态作为一个bitmap

  把每个bitmap做交集
  为1的就是连续登陆的id

  基数统计

  使用hyperloglog
  会有误差，
  追求精确的话使用 hash set

- geo 自定义数据结构

  - 地图中存储经纬度信息

    打车，单车应用中使用
    key存储的车辆信息
    value 存储经纬度信息 作为权重因子
    使用 sortset 有序集合
    value 中需要一个值
    而经纬度是 两个值的组合 a，b 这样
    引出需要使用 geohash
    对经纬度进行N次二分
    一次二分后落在左区间就 取 0 ，右区间取 1
    经纬度 分别得到一个 N位二进制数
    将经纬度组合起来作为 sorted set 的value 权重因子
    具体做法
    从左到右 偶数位从0开始，奇数从1开始
    经度数据从 填充偶数位
    纬度数据从 填充奇数位
    经过geohash 后就可以就可以作为权重因子了

     | 01  | 10  |
     | --- | --- |
     | 00  | 11  |
    
    映射为1维空间
    00 01 10 11
    都是相邻的格子

    不过也有例外会有相聚很远的格子
    比如使用 N为 4来分割
    会有相邻很远的格子
    0111 和 1000就相差很远

    操作geo 类型
    GEOADD 添加一组经纬度信息和对应id记录到GEO类型集合中
    GEORADIUS 查询以给定经纬度为中心一定范围的其他元素

    集合是 cars：locaton
    GEOADD cars：location 116.03 39.03 33
    
    GEORADIUS cars：location 116.03 39.03 5 km ASC COUNT 10

    查询 给定经纬度 范围 5km 内的从近到远 的 10辆车
    ASC 从小到大
    COUNT 指定数量

  自定义数据类型

  RedisObjedct 数据结构
  包含
  type  值的类型 五大基本类型
  encoding  值编码方式 底层数据结构 SDS 跳表 压缩列表 哈希表
  lru  最近一次访问时间，用于淘汰过期键值对
  refcount  引用数量
  ptr  数据指针

  创建新的数据类型

  需要指定 type 和 encoding 

   1. 定义新数据类型的底层结构
   2. 在RedisObject 中添加新数据类型的定义
   3. 开发新类型的创建和释放函数
   4. 开发新类型的操作函数

  newtype.h 文件保存新类型的定义
  struct newtype{
    struct newtypenode* head;
    size_t len;
  }newtype;
  struct newtypenode{
    long value;
    struct newtypenode* next;
  };
  相当于一个单向链表，存储的数据是long 型

  在 redis type中添加类型定义
  server.h
  添加 OBJECT_NEWTYPE 宏

  添加创建释放函数
  robj* createnettypeobject(void){
    newtype* t = newtypenew();
    robj* o = createobject(OBJECT_NETTYPE,t);
    return o;
  }

  newtypeobject* newtypenew(void){
    newtpeojbect* n = zmalloc(sizeof (*n));
    n->head = null;
    n->len = 0;
    return n;  
  }

  这个函数是redis中创建redisobject对象的方法
  传入一个type
  robj* createobject(int type,void* ptr){
    robj* o = zmalloc(sizeof(*o));
    o->type = type;
    o->ptr = ptr;
    ...
    return o;
  }
  每个类型创建redis会为类型建一个新的文件
  t_string.c
  t_set.c
  t_list.c
  t_newtype.c

  开发新对象的操作函数

  t_newtype.c 中增加新的操作实现
  void ninsertcommand(client* c){

  }

  在 server.h中声明这个函数
  
  在server.c 中使用这个函数
  需要在 rediscommandtable struct中注册新函数
  struct rediscommand rediscommandtables[]{
    {"ninsert","ninsertcommand",2,...}
  }
  
- redis时间戳数据

  保存时间戳类型的数据
  查询多方式，写入快，一般不修改写入的数据

  key
   device：temperature
  value
  value 使用 sortedset 和 hash 

  sortedset 用时间戳做权重 score 类型作为 member
  hash 支持快速通过时间戳查找数据
  结合起来使用效果好
  需要原子一致性
  事务
  mutti
  exec
  之间的命令会一起执行，保证数据一致性

  如何对数据进行聚合计算，求一定范围的和，平均值等

  使用 sortedset 和hash 
  缺点
  占用内存数据大
  需要使用网络传输，将数据传输到客户端进行计算

  引出一个第三方的模块
  redistimeseris 模块

  提供了几种操作方法

  ts.create  创建时间数据集合
  ts.add  插入数据
  ts.get  获取数据
  ts.mget  按标签过滤获取数据
  ts.range  支持聚合范围计算

  ts.create device:temperature retention 600000 labels device_id 1
  600s 后数据就会自动删除，释放内存压力
  labels 为数据添加标签
  创建了一个key 为 device：temperature 的时间序列集合
  
- 消息队列

  redis 5.0 前用 list
  5.0 后用 stream
  list 使用 lpush 和 rpop 实现先进先出
  block 阻塞的
  使用内部一个备份链表保存数据
  在消费者读取数据时会把数据备份到一份到备份链表中

  stream 消息队列
  xread xwrite 
  xread block 阻塞读
  xpending xack 保证消息可靠
  消费者读取消息 xpending 保存已读取数据
  xack 消费者读取消息处理完会发送 xack 表示已处理完数据

  stream 支持 分组读取
  一个消息组内的数据只会被同组内其中一个消费者读取，读取完就为空了

- redis 异步任务

  影响redis 性能，会导致redis阻塞的操作
  客户端请求一次操作，需要redis服务端返回一个数据给客户端，客户端根据数据再进行操作，这时redis会阻塞

  - set集合的全量查询和聚合操作

    客户端查询后需要使用数据，这个操作不不能使用异步，子线程来操作
    解决办法，用scan一次读取少量元素，在客户端进行聚合计算

  - 从库和主库的数据同步，从库加载rdb文件
  
    rdb文件保持在2g-4g，不要太大

  - aof日志的写入

    使用异步子线程进行aof日志写入

  - 清空数据库

    使用异步操作
    lazy delete
    一次清除少量数据

  - 删除bigkey

    一次读取少量元素删除

  redis 会在启动创建实例时启动三个子线程
  主线程通过任务队列和三个子线程交互
  文件关闭
  键值对删除
  aof文件写

- cpu 对redis影响

  99% 尾延迟
  访问99个的数据时间都比x值小，x就是99%尾延迟

  cpu 物理核可能分为多个逻辑核
  L1L2级缓存
  L3级缓存
  内存

  速度依次降低

  多个cpu socket
  物理cpu数量多了，多个之间通过总线连接

  绑核和修改redis源码

  绑核
  绑一个物理核上 子线程操作时会更流畅，可以在一个物理核的逻辑核之间切换
  



  



