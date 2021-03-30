# import dxf

## 读取文件

- 文件不能正确读取，打开

  使用`QString` 字符串来进行文件名字的传递，需要引入`#include<QString>`
  
  dxflib 中读取文件使用 `DL_Dxf` 类的 `in(const std::string &file, DL_CreationInterface *creationInterface)` 方法，该方法有个重载方法注意识别。
  
  进入`in()`方法后会自动添加调用 `addLayer()`等接口。
  
  需要在`addLayer()`方法中添加自定义内容实现将dxf文件中数据构造为各种item。
  
  Debug时一定要注意函数的参数列表，调用了哪个方法。
## 构造item

- 使用数据进行构造item

  构造item需要传入一个`board`

### 遇到问题

- 导入 Polyline
  导入 Polyline 和 Vertex 是分开导入的，但是 Polyline 属性又包括了 Vertex,所以需要设计一个类来将 vertex 信息加入到 polyline 的属性中
