# qt develop

- 环境搭建
  一些发行版可能会遇到 `qDebug()` 不能输出信息，使用 `qWarning()` 则可以输出信息
  去 google 搜索了 fedora enable QT qDebug 后，得到了一些信息，有些发行版不希望
  用户能够看到 qDebug 的信息提示，所以默认把这个功能给关闭了，
  解决方法是，
  编辑 ~/.config/QtProject/qtlogging.ini 这个配置文件
  ```shell
  [Rules]
  *.debug=true
  qt.*.debug=false
  ```
  这样从终端运行的程序可以看到 qDebug() 信息了，但是在 QTCreator 中还是没显示
  在QTCreator 中进行
  Qt Creator > Tools > Options > Kits 选择自己的工具包,找到 Environment 单击更改并添加
  QT_ASSUME_STDERR_HAS_CONSOLE=1