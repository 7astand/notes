# python note

使用 is 和 None 比较
使用 == 比较时需要对象实现 __eq__方法，该方法可以自定义重新实现，什么情况是相等的


- byte str

  b'abc'  是byte
  byte可以和byte相加，不能和str加
  byte可以和byte 比较不能和str比较

  repr 会将 b'abc' 输出 为 "b'abc'"

- f-string

  字符串格式化的集中方式优先使用 f-string

  f-string

  格式如下
  f'{key:<3} = {value:.3f}'

  {:<5} 长度小于 5
  {:.2f} 精度为小数点后2位
  {} 占位符，里边可以直接使用变量

- 用辅助函数代替一行复杂的表达式

  又重复代码就可以添加一个辅助函数
  少些重复部分

- unpacking

  a =[1,2]
  a[0],a[1] = a[1],a[0]
  // after
  a[0]  2
  a[1]  1

  unpacking 
  会先计算 = 号又边的值构建一个tuple
  然后unpacking 给左边俩个变量赋值

- enumerate

  把 iterator 封装成lazy generate
  每次给出本轮循环的序号

  enumerate(iterator ,i )
  i 表示开始的序号

- zip

  将来个iterator 封装成 lazy generator
  每次只取出一个tuple，列表很长也是一个个处理的
  zip 当其中一个iterator走完后就会停止
  确保zip后的两个容器长度相同

  长度不同的话使用
  itertools 模块中的
  zip_longest 方法
  会用指定值来填补空缺默认值是None

- := 海象操作符

  varabale := expres
  先给变量赋值，再判断变量的真假
  让这个变量的值成为表达式的结果

  赋值表达式是大表达式的一部分需要用 括号
  (var := expr)是一个整体

- pdb 调试

  import pdb
  pdb.set_trace()

  进入调试
  p a
  打印 a 变量
  n
  进入下一行
  l
  列出当前上下 11行代码
  s
  step in
  进入代码内部等
  出现 --call--
  退出后出现 --return--
  r
  step out
  继续执行，直到当前函数完成得到返回值退出
  b
  b 10
  在当前文件11行设置断点
  c
  继续运行到下一个断点
  