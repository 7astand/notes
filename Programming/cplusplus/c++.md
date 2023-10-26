# c++

## STL

- 对 vector 容器数据排序并去重
  1. 用 sort 方法先对容器进行排序
  2. 用 unique 方法去重, unique 方法返回容器中重复元素的迭代器首地址 iter
  3. 使用 erase 方法, 擦除指定区间的内容,首地址是 iter ,尾地址是 vectror 的尾迭代器,end

  ```cpp
  std::sort(offFilterIndexVector.begin(),offFilterIndexVector.end());
  auto iter = std::unique(offFilterIndexVector.begin(),offFilterIndexVector.end());
  offFilterIndexVector.erase(iter,offFilterIndexVector.end());
  ```

### vector

  是连续的内存区域

  - vector 内部
    内部维护了三个指针（存疑）

    一个指向堆上的内存数据
    一个指向了当前的 capacity 的大小
    一个指向了当前 data 数据元素的大小

### string 

  - string 内部
    维护了一个指针 basic_char * （存疑，还有别的东西吗）

    有些会有字节优化
    16字节优化或者8字节优化
    低于16字节的会存储在栈上，自己的内存区域内
    超过16字节的会在堆上分配内存。

### set

  set 是有序的不可重复的

  - set 内部
    维护了红黑树

    lowwer_bound 第一个小与等于value的位置
    upper_bound 大于value的位置

### 协程

```cpp
async await
能够暂停和恢复的函数
```
