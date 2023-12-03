# SQL

- 创建连接sql

    首先需要将mysql服务开启
    sudo systemctl start mysqld

    mysql -u root -p

    mysql -h 127.0.0.1 -u root -p
    mysql -h localhost -u root -p

    进入mysql交互界面

    https://dev.mysql.com/doc/refman/8.0/en/database-use.html
    

## 主从复制

  读写分离

  主数据库处理写
  从数据库处理 读

  通过binlog进行数据同步

  binlog 是二进制数据，存的是数据库的更新事件
  从数据库连接时，主发送给从 binlog
  从 io线程 从主读 binlog文件，写入从的binlog文件中
  从 sql线程 读binlog文件，执行文件中的事件 重放

  同步方法

  异步复制
  主 提交 commit 后不需要等库返回结果
  将结果直接给客户端
  不影响主的性能
  主 可能会宕机，导致主从数据不一致

  半同步复制
  主 写数据后，至少有一个从库接收到了binlog后，并写入到中继日志中，再返回数据给客户端
  增加了一些网络延迟，提高了数据一致性

  组复制 MGR 复制 基于Paxos协议进行

  主写数据后，需要经过一个 consensus 一致性协议层统一后，经过大多数同意后才能提交
  事物想要提交（N/2+1）数量同意才行
  只读事物可以直接提交

- 恢复数据

  .idb mysql 数据格式
  使用 binlog 恢复，记录了事务记录根据记录回滚
  延迟备份

  共享表空间
  多个数据表会共用一个表空间
  好处
  能存储很大数据
  坏处
  不容易恢复数据，数据，索引在一个文件中，共享表文件大小很大

  恢复 .idb 格式文件

  设置参数 innodb_force_recovery 设置为1 ，默认是0
  值为 0时 数据损坏时不能读取。1时数据损坏可以读取，为恢复模式，只读，不能写
  有 0 - 6 取值，大值包括小值的功能
  使用select读数据
  为 1时只读模式，不能使用where order by 
  使用二分查找定位损坏数据位置
  备份出旧表数据，换一种数据引擎，以为上个引擎只能读不能写
  新表数据格式要和旧表一致
  删除旧表，改名新表
  关闭参数 innodb_force_recovery 设置为 0
  重启数据库

  - 使用redis

  乐观锁
  watch  监视一个多个键，键变动事务被打断，只能在 multi之前使用
  multi  开启一个事务
  discard  取消事务
  exec  执行事务，一次性执行事务里所有命令
  unwatch  取消监视键

  
