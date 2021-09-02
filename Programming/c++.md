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
